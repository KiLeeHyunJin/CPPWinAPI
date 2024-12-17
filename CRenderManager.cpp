#include "framework.h"
#include "CRenderManager.h"
#include "CCameraManager.h"
#include "CPPWinAPI.h"
#include "CImage.h"

CRenderManager::CRenderManager():
	m_hBmp(0), m_hdc(0), m_hMemDC(0), 
	m_hPen(0), m_hBrush(0)
{
	SetPen	(PenType::Solid);
	SetBrush(BrushType::Solid);
	SetText	(TextType::Left);
}

CRenderManager::~CRenderManager()
{	
}

void CRenderManager::Init()
{

	m_hdc = GetDC(hWnd);
	m_hMemDC = CreateCompatibleDC(m_hdc); //동일한 속성의 또 다른 DC를 생성
	m_hBmp = CreateCompatibleBitmap(m_hdc, WINSIZEX, WINSIZEY); //화면 크기의 비트맵 생성

	HBITMAP oldBitMap = static_cast<HBITMAP>(SelectObject(m_hMemDC, m_hBmp));
	DeleteObject(oldBitMap);


	HRESULT hResult;

	hResult = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pFactory); //D2D 팩토리 생성
	assert(S_OK == hResult && L"D2D1CreateFactory Create Failed");

	hResult = m_pFactory->CreateHwndRenderTarget	//윈도우 클라이언트 영역을 그리기 위한 RenderTarget생성
	(
		RenderTargetProperties(),
		HwndRenderTargetProperties
		(
			hWnd,
			SizeU(WINSIZEX, WINSIZEY),
			D2D1_PRESENT_OPTIONS_IMMEDIATELY
		),
		&m_pRenderTarget
	);
	assert(S_OK == hResult && L"HwnRenderTarget Create Failed");


	hResult = CoInitialize(nullptr);	//WICImagingFactory 생성
	assert(S_OK == hResult && L"CoInitialize Failed");

	hResult = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&m_pImageFactory)); //
	assert(S_OK == hResult && L"ImageFactory Create Failed");

	hResult = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(m_pWriteFactory), reinterpret_cast<IUnknown**>(&m_pWriteFactory));
	assert(S_OK == hResult && L"WriteFactory Create Failed");

	//텍스트 포맷 생성
	hResult = m_pWriteFactory->CreateTextFormat(
		L"굴림"
		,NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL,
		10,
		L"ko", &m_pDefaultTextFormat);
	assert(S_OK == hResult && L"TextFormat Create Failed");

	hResult = m_pDefaultTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	assert(S_OK == hResult && L"TextFormat Set Alignment Failed");

	hResult = m_pDefaultTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	assert(S_OK == hResult && L"TextFormat SetParagraphAlignment Failed");

	//브러시 생성
	hResult = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(.0f, .0f, .0f), &m_pDefaultBrush);
	assert(S_OK == hResult && L"SolidColorBrush Create Failed");

	//텍스트 포맷 생성
	hResult = m_pWriteFactory->CreateTextFormat(
		L"굴림"
		, NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL,
		10,
		L"ko", &m_pCurTextFormat);
	assert(S_OK == hResult && L"TextFormat Create Failed");

	hResult = m_pCurTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	assert(S_OK == hResult && L"TextFormat Set Alignment Failed");

	hResult = m_pCurTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	assert(S_OK == hResult && L"TextFormat SetParagraphAlignment Failed");

	//브러시 생성
	hResult = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(.0f, .0f, .0f), &m_pCurBrush);
	assert(S_OK == hResult && L"SolidColorBrush Create Failed");





}

void CRenderManager::Release()
{
	DeleteObject(m_hMemDC);
	DeleteObject(m_hBmp);

	ReleaseDC(hWnd, m_hdc);

	DeleteObject(m_hPen);
	DeleteObject(m_hBrush);

	m_hBmp = 0; 
	m_hdc = 0;
	m_hMemDC = 0;

	m_typeBrush = BrushType::Solid;
	m_colorBrush = RGB(255, 255, 255);

	m_typePen = PenType::Solid;
	m_colorPen = RGB(0, 0, 0);
	m_iPenWidth = 1;

	
	if (m_pCurBrush != nullptr)
	{
		m_pCurBrush->Release();
		m_pCurBrush = nullptr;
	}

	if (m_pCurTextFormat != nullptr)
	{
		m_pCurTextFormat->Release();
		m_pCurTextFormat = nullptr;
	}

	if (m_pDefaultBrush != nullptr)
	{
		m_pDefaultBrush->Release();
		m_pDefaultBrush = nullptr;
	}

	if (m_pDefaultTextFormat != nullptr)
	{
		m_pDefaultTextFormat->Release();
		m_pDefaultTextFormat = nullptr;
	}

	if (m_pWriteFactory != nullptr)
	{
		m_pWriteFactory->Release();
		m_pWriteFactory = nullptr;
	}

	if (m_pImageFactory != nullptr)
	{
		m_pImageFactory->Release();
		m_pImageFactory = nullptr;
	}

	if (m_pRenderTarget != nullptr)
	{
		m_pRenderTarget->Release();
		m_pRenderTarget = nullptr;
	}

	if (m_pFactory != nullptr)
	{
		m_pFactory->Release();
		m_pFactory = nullptr;
	}
}


/// <summary>
/// 백버퍼 화면 초기화
/// </summary>
void CRenderManager::BeginDraw()
{	
	//PatBlt(
	//	m_hMemDC, 0, 0, WINSIZEX, WINSIZEY, 
	//	WHITENESS);	
	m_pRenderTarget->BeginDraw();
	FillRect(CAMERA->ScreenToWorldPoint(Vector(0, 0)), CAMERA->ScreenToWorldPoint(Vector(WINSIZEX, WINSIZEY)), Color(255, 255, 255, 1));
}

/// 프론트 버퍼에 복사
void CRenderManager::EndDraw()
{
	//BitBlt(
	//	m_hdc, 0, 0, WINSIZEX, WINSIZEY, 
	//	m_hMemDC, 0, 0, SRCCOPY);
	m_pRenderTarget->EndDraw();
}

void CRenderManager::SelectPenNBruchObject(HPEN prevPen, HBRUSH prevBrush) const
{
	SelectObject(m_hMemDC, prevPen);
	SelectObject(m_hMemDC, prevBrush);
}

void CRenderManager::Rect(float startX, float startY, float endX, float endY) const
{
	const HPEN prevPen = static_cast<HPEN>(SelectObject(m_hMemDC, m_hPen));
	const HBRUSH prevBrush = static_cast<HBRUSH>(SelectObject(m_hMemDC, m_hBrush));

	Rectangle(m_hMemDC, (int)startX, (int)startY, (int)endX, (int)endY);

	SelectPenNBruchObject(prevPen, prevBrush);
}

void CRenderManager::Circle(float x, float y, float radius) const
{
	const HPEN prevPen = static_cast<HPEN>(SelectObject(m_hMemDC, m_hPen));
	const HBRUSH prevBrush = static_cast<HBRUSH>(SelectObject(m_hMemDC, m_hBrush));

	Ellipse(m_hMemDC, (int)(x - radius), (int)(y - radius), (int)(x + radius), (int)(y + radius));

	SelectPenNBruchObject(prevPen, prevBrush);
}

void CRenderManager::Line(float startX, float startY, float endX, float endY) const
{
	const HPEN prevPen = static_cast<HPEN>(SelectObject(m_hMemDC, m_hPen));
	const HBRUSH prevBrush = static_cast<HBRUSH>(SelectObject(m_hMemDC, m_hBrush));


	MoveToEx(m_hMemDC, (int)startX, (int)startY, NULL);
	LineTo(m_hMemDC, (int)endX, (int)endY);

	SelectPenNBruchObject(prevPen, prevBrush);
}

void CRenderManager::Text(float x, float y, wstring str) const
{
	//글을 사용할 시 어쩔 수 없이 브러시와 펜이 변경되기에 어쩔 수 없이 

	const HPEN prevPen = static_cast<HPEN>(SelectObject(m_hMemDC, m_hPen));
	const HBRUSH prevBrush = static_cast<HBRUSH>(SelectObject(m_hMemDC, m_hBrush));

	TextOutW(m_hMemDC, (int)x, (int)y, str.c_str(), (int)str.size());

	SelectPenNBruchObject(prevPen, prevBrush);
}

#pragma region  BitImage

void CRenderManager::BitImage(CImage* pImg, float startXPos, float startYPos, float endXPos, float endYPos)
{
	BitBlt(m_hMemDC,
		(int)startXPos,
		(int)startYPos,
		(int)endXPos,
		(int)endYPos,
		pImg->GetImgDC(), 0, 0, SRCCOPY);
}

void CRenderManager::BitImage(CImage* pImg, Vector vecPos, Vector vecScale)
{
	BitBlt(m_hMemDC,
		(int)vecPos.x - (int)vecScale.x,
		(int)vecPos.y - (int)vecScale.y,
		(int)vecPos.x + (int)vecScale.x,
		(int)vecPos.y + (int)vecScale.y,
		pImg->GetImgDC(), 0, 0, SRCCOPY);
}

#pragma endregion

#pragma region  StrectchImage

void CRenderManager::StrectchImage(CImage* pImg, float startXPos, float startYPos, float endXPos, float endYPos)
{
	StretchBlt(m_hMemDC,
		(int)startXPos,
		(int)startYPos,
		(int)endXPos - (int)startXPos,
		(int)endYPos - (int)startYPos,
		pImg->GetImgDC(), 0, 0, (int)pImg->GetBmpWidth(), (int)pImg->GetBmpHeight(), SRCCOPY);
}

void CRenderManager::StrectchImage(CImage* pImg, Vector vecPos, Vector vecScale)
{
	StretchBlt(m_hMemDC,
		(int)vecPos.x - (int)vecScale.x,
		(int)vecPos.y - (int)vecScale.y,
		((int)vecPos.x + (int)vecScale.x) - ((int)vecPos.x - (int)vecScale.x),
		((int)vecPos.y + (int)vecScale.y) - ((int)vecPos.y - (int)vecScale.y),
		pImg->GetImgDC(), 0, 0, (int)pImg->GetBmpWidth(), (int)pImg->GetBmpHeight(), SRCCOPY);
}

#pragma endregion

#pragma region TransparentImage

void CRenderManager::TransparentImage(CImage* pImg, float startXPos, float startYPos, float endXPos, float endYPos, COLORREF transparent)
{
	TransparentBlt(m_hMemDC,
		(int)startXPos,
		(int)startYPos,
		(int)endXPos - (int)startXPos,
		(int)endYPos - (int)startYPos,
		pImg->GetImgDC(), 0, 0, (int)pImg->GetBmpWidth(), (int)pImg->GetBmpHeight(), (UINT)transparent);
}

void CRenderManager::TransparentImage(CImage* pImg, Vector vecPos, Vector vecScale, COLORREF transparent)
{
	TransparentBlt(m_hMemDC,
		(int)vecPos.x - (int)vecScale.x,
		(int)vecPos.y - (int)vecScale.y,
		((int)vecPos.x + (int)vecScale.x) - ((int)vecPos.x - (int)vecScale.x),
		((int)vecPos.y + (int)vecScale.y) - ((int)vecPos.y - (int)vecScale.y),
		pImg->GetImgDC(), 0, 0, (int)pImg->GetBmpWidth(), (int)pImg->GetBmpHeight(), (UINT)transparent);
}

#pragma endregion


HDC CRenderManager::GetMemDC()
{
	return m_hMemDC;
}

void CRenderManager::SetText(TextType textType)
{
	if (textType == m_typeText)
	{
		return;
	}

	int align;
	switch (textType)
	{
	case TextType::Left:
		m_typeText = TextType::Left;
		align = TA_LEFT;
		break;
	case TextType::Middle:
		m_typeText = TextType::Middle;
		align = TA_CENTER;
		break;
	case TextType::Right:
		m_typeText = TextType::Right;
		align = TA_RIGHT;
		break;
	default:
		m_typeText = TextType::Left;
		align = TA_LEFT;
		break;
	}
	SetTextAlign(m_hMemDC, align);

}

void CRenderManager::SetPen(PenType penType , COLORREF color, int width)
{
	if (m_typePen	== penType && 
		m_colorPen	== color && 
		m_iPenWidth == width)
	{
		return;
	}

	m_typePen = penType;
	m_colorPen = color;
	m_iPenWidth = width;

	DeleteObject(m_hPen);

	int penStyle;

	switch (m_typePen)
	{
	case PenType::Solid:
		penStyle = PS_SOLID;
		break;
	case PenType::Dot:
		penStyle = PS_DOT;
		break;
	case PenType::Dash:
		penStyle = PS_DASH;
		break;
	case PenType::Null:
		penStyle = PS_NULL;
		break;
	default:
		penStyle = PS_SOLID;
		break;
	}

	m_hPen = CreatePen(penStyle, m_iPenWidth, m_colorPen);
}

void CRenderManager::SetBrush(BrushType brushType , COLORREF color )
{
	if (m_typeBrush == brushType && 
		m_colorBrush == color )
	{	return;		}
	else
	{
		if (m_hBrush != nullptr)	
		{	DeleteObject(m_hPen);	}
	}
	switch (brushType)
	{
	case BrushType::Solid:
		m_hBrush = CreateSolidBrush(color);
		break;
	case BrushType::Null: //존재하지 않는 안그리는 브러시 사용
		m_hBrush = static_cast<HBRUSH>(GetStockObject(NULL_BRUSH));
		break;
	default:
		m_hBrush = CreateSolidBrush(color);
		break;
	}

	m_typeBrush = brushType;
	m_colorBrush = color;
}

void CRenderManager::SetBrush(Color color)
{
	m_pDefaultBrush->SetColor(
		D2D1::ColorF(
			(FLOAT)	color.r / 255.f,
			(FLOAT)	color.g / 255.f,
			(FLOAT)	color.b / 255.f,
					color.a / 255.f)
	);
}

void CRenderManager::SetTextFormat(wstring fontName, DWRITE_FONT_WEIGHT fontWeight, DWRITE_FONT_STYLE fontstyle, DWRITE_FONT_STRETCH fontStretch, FLOAT fontSize, wstring localName)
{
	DWRITE_TEXT_ALIGNMENT textAlignment = m_pDefaultTextFormat->GetTextAlignment();
	DWRITE_PARAGRAPH_ALIGNMENT paragraphAlignment = m_pDefaultTextFormat->GetParagraphAlignment();

	if (m_pDefaultTextFormat != nullptr)
	{
		m_pDefaultTextFormat = nullptr;
		m_pDefaultTextFormat->Release();
	}
	HRESULT hResult = m_pWriteFactory->CreateTextFormat(
		fontName.c_str(),
		NULL,
		fontWeight,
		fontstyle,
		fontStretch,
		fontSize,
		localName.c_str(),
		&m_pDefaultTextFormat
	);
	assert(S_OK == hResult && L"TextFormat Create Failed");
}

void CRenderManager::SetTextAlignment(DWRITE_TEXT_ALIGNMENT textAlignment)
{
	HRESULT hResult = m_pDefaultTextFormat->SetTextAlignment(textAlignment);
	assert(S_OK == hResult && L"TextFormat Set Alignment Failed");
}

void CRenderManager::SetTextParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT paragraphAlignment)
{
	HRESULT hResult = m_pDefaultTextFormat->SetParagraphAlignment(paragraphAlignment);
	assert(S_OK == hResult && L"TextFormat SetParagraphAlignment Failed");
}



#pragma region  Image

void CRenderManager::Image(CImage* pImg, const Vector& startPoint, const Vector& endPoint, float alpha)
{
	Vector start = CAMERA->WorldToScreenPoint(startPoint);
	Vector end = CAMERA->WorldToScreenPoint(endPoint);
	D2D1_RECT_F imgRect = { start.x, start.y, end.x, end.y };
	m_pRenderTarget->DrawBitmap(pImg->GetImage(), imgRect);
}

void CRenderManager::FrameImage(CImage* pImg, const Vector& drawStartPoint, const Vector& drawEndPoint, const Vector& sliceStartPoint, const Vector& sliceEndPoint, float alpha)
{
	Vector start = CAMERA->WorldToScreenPoint(drawStartPoint);
	Vector end = CAMERA->WorldToScreenPoint(drawEndPoint);
	D2D1_RECT_F pointRect = { start.x,	start.y,	end.x,		end.y };
	D2D1_RECT_F srcImgRect = { sliceStartPoint.x,	sliceStartPoint.y,	sliceEndPoint.x,	sliceEndPoint.y };
	m_pRenderTarget->DrawBitmap(pImg->GetImage(), pointRect, alpha, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, srcImgRect);
}

#pragma endregion

#pragma region  Text

void CRenderManager::Text(const wstring& str, const Vector& startPoint, const Vector& endPoint)
{
	Vector start = CAMERA->WorldToScreenPoint(startPoint);
	Vector end = CAMERA->WorldToScreenPoint(endPoint);
	D2D1_RECT_F rect = { start.x, start.y, end.x, end.x};
	m_pRenderTarget->DrawTextW(str.c_str(), (UINT32)str.size(), m_pDefaultTextFormat, rect, m_pDefaultBrush);
}

void CRenderManager::Text(const wstring& str, const Vector& startPoint, const Vector& endPoint, const Color& color, float fontSize)
{
	Vector start = CAMERA->WorldToScreenPoint(startPoint);
	Vector end = CAMERA->WorldToScreenPoint(endPoint);
	D2D1_RECT_F rect = { start.x, start.y, end.x, end.y };

	SetCurFontSize(fontSize);
	SetCurBrush(color);
	m_pRenderTarget->DrawTextW(str.c_str(), (UINT32)str.size(), m_pCurTextFormat, rect, m_pCurBrush);
}

void CRenderManager::Text(const wstring& str, float dstX, float dstY, float dstW, float dstH)
{
	Vector start = CAMERA->WorldToScreenPoint(Vector(dstX, dstY));
	D2D1_RECT_F rect = { start.x, start.y, start.x + dstW, start.x + dstH };
	m_pRenderTarget->DrawTextW(str.c_str(), (UINT32)str.size(), m_pDefaultTextFormat, rect, m_pDefaultBrush);
}

void CRenderManager::Text(const wstring& str, float dstX, float dstY, float dstW, float dstH, const Color& color, float fontSize)
{
	Vector start = CAMERA->WorldToScreenPoint(Vector(dstX, dstY));
	D2D1_RECT_F rect = { start.x, start.y, start.x + dstW, start.x + dstH };

	SetCurFontSize(fontSize);
	SetCurBrush(color);
	m_pRenderTarget->DrawTextW(str.c_str(), (UINT32)str.size(), m_pCurTextFormat, rect, m_pCurBrush);
}
#pragma endregion

#pragma region  Line

void CRenderManager::Line(const Vector& startPoint, const Vector& endPoint)
{
	Vector vecStart = CAMERA->WorldToScreenPoint(startPoint);
	Vector vecEnd = CAMERA->WorldToScreenPoint(startPoint);

	D2D1_POINT_2F start = { vecStart.x , vecStart.y };
	D2D1_POINT_2F end = { vecEnd.x , vecEnd.y };
	m_pRenderTarget->DrawLine(start, end, m_pDefaultBrush);
}

void CRenderManager::Line(const Vector& startPoint, const Vector& endPoint, const Color& color, float strokeWidth)
{
	Vector vecStart = CAMERA->WorldToScreenPoint(startPoint);
	Vector vecEnd = CAMERA->WorldToScreenPoint(startPoint);

	D2D1_POINT_2F start = { vecStart.x , vecStart.y };
	D2D1_POINT_2F end = { vecEnd.x , vecEnd.y };
	SetCurBrush(color);
	m_pRenderTarget->DrawLine(start, end, m_pCurBrush);
}
#pragma endregion

#pragma region  Frame

void CRenderManager::FrameRect(const Vector& startPoint, const Vector& endPoint, float strokeWidth)
{
	Vector start = CAMERA->WorldToScreenPoint(startPoint);
	Vector end = CAMERA->WorldToScreenPoint(endPoint);
	D2D1_RECT_F rect = { start.x, start.y, end.x , end.y };
	m_pRenderTarget->DrawRectangle(rect, m_pDefaultBrush, strokeWidth);
}

void CRenderManager::FrameRect(const Vector& startPoint, const Vector& endPoint, const Color& color, float strokeWidth)
{
	Vector start = CAMERA->WorldToScreenPoint(startPoint);
	Vector end = CAMERA->WorldToScreenPoint(endPoint);
	D2D1_RECT_F rect = { start.x, start.y, end.x , end.y };
	SetCurBrush(color);
	m_pRenderTarget->DrawRectangle(rect, m_pCurBrush, strokeWidth);
}

void CRenderManager::FrameEllipse(const Vector& startPoint, float radius, float strokeWidth)
{
	Vector start = CAMERA->WorldToScreenPoint(startPoint);
	D2D1_ELLIPSE ellipse = { start.x, start.y ,radius , radius };
	m_pRenderTarget->DrawEllipse(ellipse, m_pDefaultBrush, strokeWidth);
}

void CRenderManager::FrameEllipse(const Vector& startPoint, float radius, const Color& color, float strokeWidth)
{
	Vector start = CAMERA->WorldToScreenPoint(startPoint);
	D2D1_ELLIPSE ellipse = { start.x, start.y ,radius , radius };
	SetCurBrush(color);
	m_pRenderTarget->DrawEllipse(ellipse, m_pCurBrush, strokeWidth);
}

void CRenderManager::FrameCircle(const Vector& startPoint, float radius)
{
	Vector start = CAMERA->WorldToScreenPoint(startPoint);
	D2D1_ELLIPSE ellipse = { start.x, start.y ,radius , radius };
	m_pRenderTarget->DrawEllipse(ellipse, m_pDefaultBrush);
}

void CRenderManager::FrameCircle(const Vector& startPoint, float radius, const Color& color, float strokeWidth)
{
	Vector start = CAMERA->WorldToScreenPoint(startPoint);
	D2D1_ELLIPSE ellipse = { start.x, start.y , radius , radius };
	SetCurBrush(color);
	m_pRenderTarget->DrawEllipse(ellipse, m_pCurBrush, strokeWidth);
}
#pragma endregion

#pragma region  Fill

void CRenderManager::FillRect(const Vector& startPoint, const Vector& endPoint)
{
	Vector start = CAMERA->WorldToScreenPoint(startPoint);
	Vector end = CAMERA->WorldToScreenPoint(endPoint);
	D2D1_RECT_F rect = { start.x, start.y, end.x , end.y };
	m_pRenderTarget->FillRectangle(rect, m_pDefaultBrush);
}

void CRenderManager::FillRect(const Vector& startPoint, const Vector& endPoint, const Color& color)
{
	Vector start = CAMERA->WorldToScreenPoint(startPoint);
	Vector end = CAMERA->WorldToScreenPoint(endPoint);
	D2D1_RECT_F rect = { start.x, start.y, end.x , end.y };
	SetCurBrush(color);
	m_pRenderTarget->FillRectangle(rect, m_pCurBrush);
}

void CRenderManager::FillEllipse(const Vector& startPoint, float radius)
{
	Vector start = CAMERA->WorldToScreenPoint(startPoint);
	D2D1_ELLIPSE ellipse = { start.x, start.y ,radius , radius };
	m_pRenderTarget->FillEllipse(ellipse, m_pDefaultBrush);
}

void CRenderManager::FillEllipse(const Vector& startPoint, float radius, const Color& color)
{
	Vector start = CAMERA->WorldToScreenPoint(startPoint);
	D2D1_ELLIPSE ellipse = { start.x, start.y ,radius , radius };
	SetCurBrush(color);
	m_pRenderTarget->FillEllipse(ellipse, m_pCurBrush);
}

void CRenderManager::FillCircle(const Vector& startPoint, float radius)
{
	Vector start = CAMERA->WorldToScreenPoint(startPoint);
	D2D1_ELLIPSE ellipse = { start.x, start.y ,radius , radius };
	m_pRenderTarget->FillEllipse(ellipse, m_pDefaultBrush);
}

void CRenderManager::FillCircle(const Vector& startPoint, float radius, const Color& color)
{
	Vector start = CAMERA->WorldToScreenPoint(startPoint);
	D2D1_ELLIPSE ellipse = { start.x, start.y ,radius , radius };
	SetCurBrush(color);
	m_pRenderTarget->FillEllipse(ellipse, m_pCurBrush);
}
#pragma endregion

void CRenderManager::SetCurBrush(const Color& color)
{
	m_pCurBrush->SetColor(D2D1::ColorF(
		(FLOAT)color.r / 255.f,
		(FLOAT)color.g / 255.f,
		(FLOAT)color.b / 255.f,
		color.a));
}

void CRenderManager::SetCurFontSize(float fontSize)
{
	if (m_pCurTextFormat->GetFontSize() != fontSize)
	{
		WCHAR fontFamilyName[255];
		WCHAR localName[255];

		m_pDefaultTextFormat->GetFontFamilyName(fontFamilyName, 255);
		m_pDefaultTextFormat->GetLocaleName(localName, 255);
		m_pCurTextFormat->Release();

		HRESULT hResult = m_pWriteFactory->CreateTextFormat(
			fontFamilyName,
			NULL,
			m_pDefaultTextFormat->GetFontWeight(),
			m_pDefaultTextFormat->GetFontStyle(),
			m_pDefaultTextFormat->GetFontStretch(),
			fontSize,
			localName,
			&m_pCurTextFormat
		);
	}
}

IWICImagingFactory* CRenderManager::GetImageFactory()			{	return m_pImageFactory;		}

ID2D1HwndRenderTarget* CRenderManager::GetRenderTarget()		{	return m_pRenderTarget;		}
