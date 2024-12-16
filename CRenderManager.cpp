#include "framework.h"
#include "CRenderManager.h"
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
	{
		return;
	}
	else
	{
		if (m_hBrush != nullptr)
		{
			DeleteObject(m_hPen);
		}
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



void CRenderManager::Image(CImage* pImg, Vector startPoint, Vector endPoint, float alph)
{
	D2D1_RECT_F imgRect = { startPoint.x, startPoint.y, endPoint.x, endPoint.y };
	m_pRenderTarget->DrawBitmap(pImg->GetImage(), imgRect);
}

void CRenderManager::FrameImage(CImage* pImg, float dstX, float dstY, float dstW, float dstH, float srcX, float srcY, float srcW, float srcH, float alph)
{
	D2D1_RECT_F imgRect = { dstX,dstY, dstW,dstH };
	D2D1_RECT_F srcRect = { srcX,srcY, srcW,srcH };
	m_pRenderTarget->DrawBitmap(pImg->GetImage(), imgRect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, srcRect);
}

IWICImagingFactory* CRenderManager::GetImageFactory()
{
	return m_pImageFactory;
}

ID2D1HwndRenderTarget* CRenderManager::GetRenderTarget()
{
	return m_pRenderTarget;
}

void CRenderManager::FillEllipse(Vector startPoint, float radius)
{
	D2D1_ELLIPSE ellipse = { startPoint.x, startPoint.y ,radius , radius };
	m_pRenderTarget->FillEllipse(ellipse, m_pDefaultBrush);
}

void CRenderManager::FillEllipse(Vector startPoint, float radius, Color color, float strokeWidth)
{
	D2D1_ELLIPSE ellipse = { startPoint.x, startPoint.y ,radius , radius };
	m_pCurBrush->SetColor(D2D1::ColorF(
		(FLOAT)color.r / 255.f,
		(FLOAT)color.g / 255.f,
		(FLOAT)color.b / 255.f,
		color.a));
	m_pRenderTarget->FillEllipse(ellipse, m_pCurBrush);
}

void CRenderManager::FrameCircle(Vector startPoint, float radius)
{
	D2D1_ELLIPSE ellipse = { startPoint.x, startPoint.y ,radius , radius };
	m_pRenderTarget->DrawEllipse(ellipse, m_pDefaultBrush);
}

void CRenderManager::FrameCircle(Vector startPoint, float radius, Color color, float strokeWidth)
{
	D2D1_ELLIPSE ellipse = { startPoint.x, startPoint.y , radius , radius };
	m_pCurBrush->SetColor(D2D1::ColorF(
		(FLOAT)color.r / 255.f,
		(FLOAT)color.g / 255.f,
		(FLOAT)color.b / 255.f,
		color.a));
	m_pRenderTarget->DrawEllipse(ellipse, m_pCurBrush, strokeWidth);
}

void CRenderManager::FillCircle(Vector startPoint, float radius)
{
	D2D1_ELLIPSE ellipse = { startPoint.x, startPoint.y ,radius , radius };
	m_pRenderTarget->FillEllipse(ellipse, m_pDefaultBrush);
}

void CRenderManager::FillCircle(Vector startPoint, float radius, Color color, float strokeWidth)
{
	D2D1_ELLIPSE ellipse = { startPoint.x, startPoint.y ,radius , radius };
	m_pCurBrush->SetColor(D2D1::ColorF(
		(FLOAT)color.r / 255.f,
		(FLOAT)color.g / 255.f,
		(FLOAT)color.b / 255.f,
		color.a));
	m_pRenderTarget->FillEllipse(ellipse, m_pCurBrush);
}
