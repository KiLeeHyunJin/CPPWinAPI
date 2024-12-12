#include "framework.h"
#include "CRenderManager.h"
#include "CPPWinAPI.h"


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
}


/// <summary>
/// 백버퍼 화면 초기화
/// </summary>
void CRenderManager::BeginDraw()
{	
	PatBlt(
		m_hMemDC, 0, 0, WINSIZEX, WINSIZEY, 
		WHITENESS);	
}

/// 프론트 버퍼에 복사
void CRenderManager::EndDraw()
{
	BitBlt(
		m_hdc, 0, 0, WINSIZEX, WINSIZEY, 
		m_hMemDC, 0, 0, SRCCOPY);
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

