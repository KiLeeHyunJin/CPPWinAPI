#pragma once
class CCore;

enum class PenType
{	Solid, Dot, Dash, Null,	};

enum class BrushType
{	Solid, Null, };

enum class TextType
{	Left, Middle, Right,};

class CRenderManager : public SingleTon<CRenderManager>
{
public :
	void SetPen(PenType penType, COLORREF color = RGB(0,0,0), int width = 1);
	void SetBrush(BrushType brushType, COLORREF color = RGB(255, 255, 255));
	void SetText(TextType textType);


	void Line(float startX, float startY, float endX, float endY)	const;
	void Rect(float startX, float startY, float endX, float endY)	const;
	void Circle(float x, float y, float radius)						const;
	void Text(float x, float y, wstring str)						const;



	friend CCore;
	friend SingleTon<CRenderManager>;
private :
	CRenderManager();
	virtual ~CRenderManager();

	void Init();
	void Release();

	void BeginDraw();
	void EndDraw();
	
	HDC			m_hdc;		// ���� ȭ�� DC , ����Ʈ ���� (���ȭ�� �׸� DC)
	HDC			m_hMemDC;	// ����� DC (�ӽ� ȭ�� DC)
	HBITMAP		m_hBmp;		// ����� ��Ʈ�� (�ӽ� ȭ�� �׸�)

	HPEN		m_hPen;	
	COLORREF	m_colorPen;
	PenType		m_typePen;
	int			m_iPenWidth;

	HBRUSH		m_hBrush;	
	COLORREF	m_colorBrush;
	BrushType	m_typeBrush;

	TextType	m_typeText;
};
#define RENDER CRenderManager::GetInstance()

