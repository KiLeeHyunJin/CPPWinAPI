#pragma once
#include "CResource.h"

class CResourceManager;
class CRenderManager;
struct ID2D1Bitmap;

class CImage : public CResource
{
public : 
	CImage();
	virtual ~CImage();

	HDC GetImgDC() const;
	BITMAP GetBmpInfo() const;
	float GetBmpWidth() const;
	float GetBmpHeight() const;

	friend CResourceManager;
	friend CRenderManager;
private :
	void Load(const wstring& filePath);
	ID2D1Bitmap* GetImage();

	HDC m_hdc;
	HBITMAP m_hBmp;
	BITMAP m_bmpInfo;

	ID2D1Bitmap* m_pBitmap;
};

