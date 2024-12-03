#include "framework.h"
#include "CRenderManager.h"
#include "CPPWinAPI.h"


CRenderManager::CRenderManager():
	m_hBmp(0), m_hdc(0), m_hMemDC(0), 
	m_hPen(0), m_hBrush(0)
{
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

	m_hBmp = 0; 
	m_hdc = 0;
	m_hMemDC = 0;
}
/// <summary>
/// 백버퍼 화면 초기화
/// </summary>
void CRenderManager::BeginDraw()
{
	PatBlt(m_hMemDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS); 
}

/// 프론트 버퍼에 복사
void CRenderManager::EndDraw()
{
	BitBlt(
		m_hdc, 0, 0, WINSIZEX, WINSIZEY, 
		m_hMemDC, 0, 0, SRCCOPY);
}



void CRenderManager::Rect(float startX, float startY, float endX, float endY) const
{
	Rectangle(m_hMemDC, (int)startX, (int)startY, (int)endX, (int)endY);
}

void CRenderManager::Circle(float x, float y, float radius) const
{
	Ellipse(m_hMemDC, (int)(x - radius), (int)(y - radius), (int)(x + radius), (int)(y + radius));
}

void CRenderManager::Text(float x, float y, wstring str) const
{
	TextOut(m_hMemDC, x, y, str.c_str(), str.size());
}



void CRenderManager::Line(float startX, float startY, float endX, float endY) const
{
	MoveToEx(m_hMemDC, (int)startX, (int)startY, NULL);
	LineTo(m_hMemDC, (int)endX, (int)endY);
}

void CRenderManager::SetPen(PenType penType, COLORREF color, int width)
{
	if (m_typePen == penType && m_colorPen == color && m_iPenWidth == width)
	{
		return;
	}
	else
	{
		if (m_hPen != nullptr)
		{
			DeleteObject(m_hPen);
		}
	}

	int penStyle;
	switch (penType)
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
	m_hPen = CreatePen(penStyle, width, color);
}

void CRenderManager::SetBrush(BrushType brushType, COLORREF color)
{

}
