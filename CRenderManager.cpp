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
	m_hMemDC = CreateCompatibleDC(m_hdc); //������ �Ӽ��� �� �ٸ� DC�� ����
	m_hBmp = CreateCompatibleBitmap(m_hdc, WINSIZEX, WINSIZEY); //ȭ�� ũ���� ��Ʈ�� ����

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
/// ����� ȭ�� �ʱ�ȭ
/// </summary>
void CRenderManager::BeginDraw()
{
	PatBlt(m_hMemDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS); 
}

/// ����Ʈ ���ۿ� ����
void CRenderManager::EndDraw()
{
	BitBlt(
		m_hdc, 0, 0, WINSIZEX, WINSIZEY, 
		m_hMemDC, 0, 0, SRCCOPY);
}



void CRenderManager::Rect(float startX, float startY, float endX, float endY) const
{
	const HPEN prevPen = static_cast<HPEN>(SelectObject(m_hMemDC, m_hPen));
	const HBRUSH prevBrush = static_cast<HBRUSH>(SelectObject(m_hMemDC, m_hBrush));

	Rectangle(m_hMemDC, (int)startX, (int)startY, (int)endX, (int)endY);

	SelectObject(m_hMemDC, prevPen);
	SelectObject(m_hMemDC, prevBrush);
}

void CRenderManager::Circle(float x, float y, float radius) const
{
	const HPEN prevPen = static_cast<HPEN>(SelectObject(m_hMemDC, m_hPen));
	const HBRUSH prevBrush = static_cast<HBRUSH>(SelectObject(m_hMemDC, m_hBrush));

	Ellipse(m_hMemDC, (int)(x - radius), (int)(y - radius), (int)(x + radius), (int)(y + radius));

	SelectObject(m_hMemDC, prevPen);
	SelectObject(m_hMemDC, prevBrush);
}

void CRenderManager::Line(float startX, float startY, float endX, float endY) const
{
	const HPEN prevPen = static_cast<HPEN>(SelectObject(m_hMemDC, m_hPen));
	const HBRUSH prevBrush = static_cast<HBRUSH>(SelectObject(m_hMemDC, m_hBrush));


	MoveToEx(m_hMemDC, (int)startX, (int)startY, NULL);
	LineTo(m_hMemDC, (int)endX, (int)endY);

	SelectObject(m_hMemDC, prevPen);
	SelectObject(m_hMemDC, prevBrush);
}

void CRenderManager::Text(float x, float y, wstring str) const
{
	//���� ����� �� ��¿ �� ���� �귯�ÿ� ���� ����Ǳ⿡ ��¿ �� ���� 

	const HPEN prevPen = static_cast<HPEN>(SelectObject(m_hMemDC, m_hPen));
	const HBRUSH prevBrush = static_cast<HBRUSH>(SelectObject(m_hMemDC, m_hBrush));

	TextOutW(m_hMemDC, x, y, str.c_str(), str.size());

	SelectObject(m_hMemDC, prevPen);
	SelectObject(m_hMemDC, prevBrush);
}

void CRenderManager::SetText(TextType textType)
{
	if (textType == m_typeText)
	{
		return;
	}

	switch (textType)
	{
	case TextType::Left:
		m_typeText = TextType::Left;
		SetTextAlign(m_hMemDC, TA_LEFT);
		break;
	case TextType::Middle:
		m_typeText = TextType::Middle;
		SetTextAlign(m_hMemDC, TA_CENTER);
		break;
	case TextType::Right:
		m_typeText = TextType::Right;
		SetTextAlign(m_hMemDC, TA_RIGHT);
		break;
	default:
		m_typeText = TextType::Left;
		SetTextAlign(m_hMemDC, TA_LEFT);
		break;
	}

}



void CRenderManager::SetPen(PenType penType, COLORREF color, int width)
{
	if (m_typePen == penType && 
		m_colorPen == color && 
		m_iPenWidth == width)
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
	m_typePen = (PenType)penStyle;
	m_colorPen = color;
	m_iPenWidth = width;

	m_hPen = CreatePen(penStyle, width, color);
}

void CRenderManager::SetBrush(BrushType brushType, COLORREF color)
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
	case BrushType::Null: //�������� �ʴ� �ȱ׸��� �귯�� ���
		m_hBrush = static_cast<HBRUSH>(GetStockObject(NULL_BRUSH));
		break;
	default:
		m_hBrush = CreateSolidBrush(color);
		break;
	}

	m_typeBrush = brushType;
	m_colorBrush = color;
}

