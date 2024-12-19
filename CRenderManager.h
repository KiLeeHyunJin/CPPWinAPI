#pragma once
#pragma comment(lib, "Msimg32.lib")

class CCore;
class CImage;

enum class PenType
{	Solid, Dot, Dash, Null,	};

enum class BrushType
{	Solid, Null, };

enum class TextType
{	Left, Middle, Right,};

enum class TextHeightType
{	Top, Middle, Bottom,};

class CRenderManager : 
	public SingleTon<CRenderManager>
{
public :
	void SetPen		(PenType penType = PenType::Solid, COLORREF color = RGB(0,0,0), int width = 1);
	void SetBrush	(BrushType brushType = BrushType::Solid, COLORREF color = RGB(255, 255, 255));
	void SetText	(TextType textType);
	HDC GetMemDC();


	void Line		(float startX, float startY, float endX, float endY)	const;	
	void Rect		(float startX, float startY, float endX, float endY)	const;	
	void Circle		(float x, float y, float radius)						const;	
	void Text		(float x, float y, wstring str)							const;	

	void BitImage(CImage* pImg, float startXPos, float startYPos, float endXPos, float endYPos);
	void BitImage(CImage* pImg, Vector vecPos, Vector vecScale);

	void StrectchImage(CImage* pImg, float startXPos, float startYPos, float endXPos, float endYPos);
	void StrectchImage(CImage* pImg, Vector vecPos, Vector vecScale);

	void TransparentImage(CImage* pImg, float startXPos, float startYPos, float endXPos, float endYPos, COLORREF transparent = RGB(255, 0, 255));
	void TransparentImage(CImage* pImg, Vector vecPos, Vector vecScale, COLORREF transparent = RGB(255, 0, 255));

	friend CCore;
	friend SingleTon<CRenderManager>;
private :
	CRenderManager();
	virtual ~CRenderManager();

	void Init();
	void Release();

	void BeginDraw();
	void EndDraw();

	void SelectPenNBruchObject(HPEN prevPen, HBRUSH prevBrush) const;
	
	void SetCurBrush(const Color& color);
	void SetCurFontSize(float fontSize);

	/// Buffer
	HDC			m_hdc;		// 게임 화면 DC , 프론트 버퍼 (결과화면 그릴 DC)
	HDC			m_hMemDC;	// 백버퍼 DC (임시 화면 DC)
	HBITMAP		m_hBmp;		// 백버퍼 비트맵 (임시 화면 그림)

	/// Pen
	HPEN		m_hPen;	
	COLORREF	m_colorPen;
	PenType		m_typePen;
	int			m_iPenWidth;

	/// Brush
	HBRUSH		m_hBrush;	
	COLORREF	m_colorBrush;
	BrushType	m_typeBrush;

	/// Text
	TextType	m_typeText;


	ID2D1Factory* m_pFactory;					//d2d팩토리
	ID2D1HwndRenderTarget* m_pRenderTarget;		//그려야하는 화면
	IWICImagingFactory* m_pImageFactory;		//이미지
	IDWriteFactory* m_pWriteFactory;			//그리기

	ID2D1SolidColorBrush* m_pDefaultBrush;		//도형 그리기 위한 브러시
	IDWriteTextFormat* m_pDefaultTextFormat;	//텍스트  그리기 위한

	ID2D1SolidColorBrush* m_pCurBrush;			//현재 브러시
	IDWriteTextFormat* m_pCurTextFormat;		//현재 포맷

public :
	void SetBrush(Color color);
	void SetTextFormat(
		wstring fontName,
		DWRITE_FONT_WEIGHT fontWeight,
		DWRITE_FONT_STYLE fontstyle,
		DWRITE_FONT_STRETCH fontStretch,
		FLOAT fontSize,
		wstring localName = L"ko");

	void SetTextAlignment(DWRITE_TEXT_ALIGNMENT textAlignment);
	void SetTextParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT paragraphAlignment);

	void Text(const wstring& str, const Vector& startPoint, const Vector& endPoint);
	void Text(const wstring& str, const Vector& startPoint, const Vector& endPoint, const Color& color, float fontSize);

	void Text(const wstring& str, float dstX, float dstY, float dstW, float dstH);
	void Text(const wstring& str, float dstX, float dstY, float dstW, float dstH, const Color& color, float fontSize);

	void Line(const Vector& startPoint, const Vector& endPoint);
	void Line(const Vector& startPoint, const Vector& endPoint, const Color& color, float strokeWidth = 1.f);

	void FrameRect(const Vector& startPoint, const Vector& endPoint, float strokeWidth = 1.f);
	void FrameRect(const Vector& startPoint, const Vector& endPoint, const Color& color, float strokeWidth = 1.f);

	void FillRect(const Vector& startPoint, const Vector& endPoint);
	void FillRect(const Vector& startPoint, const Vector& endPoint, const Color& color);

	void FrameEllipse(const Vector& startPoint,  float radius, float strokeWidth = 1.f);
	void FrameEllipse(const Vector& startPoint,  float radius, const Color& color, float strokeWidth = 1.f);

	void FillEllipse(const Vector& startPoint, float radius);
	void FillEllipse(const Vector& startPoint, float radius, const Color& color);

	void FrameCircle(const Vector& startPoint,  float radius);
	void FrameCircle(const Vector& startPoint,  float radius, const Color& color, float strokeWidth = 1.f);

	void FillCircle(const Vector& startPoint, float radius);
	void FillCircle(const Vector& startPoint, float radius, const Color& color);

	void Image(CImage* pImg, const Vector& startPoint, const Vector& endPoint, float alpha = 1.f);
	void FrameImage(CImage* pImg, 
		const Vector& drawStartPoint,	const Vector& drawEndPoint, 
		const Vector& sliceStartPoint,	const Vector& sliceEndPoint, float alpha = 1.f);

	IWICImagingFactory* GetImageFactory();
	ID2D1HwndRenderTarget* GetRenderTarget();
};
#define RENDER CRenderManager::GetInstance()
#define GETMEMDC CRenderManager::GetInstance()->GetMemDC()
