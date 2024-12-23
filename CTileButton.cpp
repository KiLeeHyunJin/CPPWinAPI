#include "framework.h"
#include "CTileButton.h"

CTileButton::CTileButton():
	m_iCountX(0), m_iCountY(0),
	m_uiTileIndex(0)
{
}

CTileButton::~CTileButton()
{
}

CImage* CTileButton::GetImage()
{
	return m_pImage;
}

void CTileButton::SetImage(CImage* pimg)
{
	m_pImage = pimg;
}

UINT CTileButton::GetTileIndex()
{
	return m_uiTileIndex;
}

void CTileButton::SetTileIndex(UINT index)
{
	m_uiTileIndex = index;
}
