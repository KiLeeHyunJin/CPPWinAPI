#include "framework.h"
#include "CImage.h"

#include "CRenderManager.h"

CImage::CImage():
	m_hdc(0),
	m_hBmp(0),
	m_bmpInfo({}),
	m_pBitmap(nullptr)
{
}

CImage::~CImage()
{
	if (m_pBitmap != nullptr)
	{
		m_pBitmap->Release();
		m_pBitmap = nullptr;
	}
}

HDC CImage::GetImgDC() const
{
	return m_hdc;
}

BITMAP CImage::GetBmpInfo() const
{
	return m_bmpInfo;
}

float CImage::GetBmpWidth() const
{
	return (float)m_bmpInfo.bmWidth;
}

float CImage::GetBmpHeight() const
{
	return (float)m_bmpInfo.bmHeight;
}

void CImage::Load(const wstring& filePath)
{
	//m_hBmp = (HBITMAP)LoadImage(
	//	nullptr,						// ���α׷� �ν��Ͻ� ���̵�
	//	filePath.c_str(),				// c ���ڿ� ���
	//	IMAGE_BITMAP,					// ���� ����
	//	0, 0,							//�ҷ��� ������
	//	LR_CREATEDIBSECTION | LR_LOADFROMFILE);	// �ε� Ÿ��

	//assert(m_hBmp && L"�̹��� �ε� ����");

	//m_hdc = CreateCompatibleDC(GETMEMDC);
	//SelectObject(m_hdc, m_hBmp);
	//GetObject(m_hBmp, sizeof(BITMAP), &m_bmpInfo);

	IWICBitmapDecoder* p_decoder;
	IWICBitmapFrameDecode* p_frame;
	IWICFormatConverter* p_converter;

	HRESULT hResult;
	hResult = RENDER->GetImageFactory()->CreateDecoderFromFilename(filePath.c_str(), NULL, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &p_decoder);
	assert(m_hBmp && L"DecoderFromFilename Faild");

	hResult = p_decoder->GetFrame(0, &p_frame);
	assert(m_hBmp && L"GetFrame Faild");

	hResult = RENDER->GetImageFactory()->CreateFormatConverter(&p_converter);
	assert(m_hBmp && L"CreateFormatConverter Faild");

	hResult = p_converter->Initialize(p_frame, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0, WICBitmapPaletteTypeCustom);
	assert(m_hBmp && L"converter Initialize Faild");

	hResult = RENDER->GetRenderTarget()->CreateBitmapFromWicBitmap(p_converter, NULL, &m_pBitmap);
	assert(m_hBmp && L"CreateBitmap Faild");

	p_converter->Release();
	p_frame->Release();
	p_decoder->Release();

}

ID2D1Bitmap* CImage::GetImage()
{
	return m_pBitmap;
}
