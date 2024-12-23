#include "framework.h"
#include "CTile.h"
#include "CResourceManager.h"
#include "CImage.h"
#include "CRenderManager.h"

CTile::CTile()
{

}

CTile::~CTile()
{
}

void CTile::SetTilePosX(UINT x)
{
	m_uiTilePosX = x;
}

void CTile::SetTilePosY(UINT y)
{
	m_uiTilePosY = y;
}

void CTile::SetTilePos(UINT x, UINT y)
{
	m_uiTilePosX = x;
	m_uiTilePosY = y;
}

void CTile::SetTileIndex(UINT index)
{
	m_uiTileIndex = index;
}

int CTile::GetTilePosX()
{
	return m_uiTilePosX;
}

int CTile::GetTilePosY()
{
	return m_uiTilePosY;
}

int CTile::GetTileIndex()
{
	return m_uiTileIndex;
}

bool CTile::GetLineRender()
{
	return m_bLineRender;
}

void CTile::Load(FILE* pFile)
{
	fread(&m_uiTileIndex, sizeof(UINT), 1, pFile);
}

void CTile::Save(FILE* pFile)
{
	fwrite(&m_uiTileIndex, sizeof(UINT), 1, pFile);
}

void CTile::Init()
{
	m_pImg = RESOURCE->LoadImg(L"Tile", L"Image\\Tile.png");
	m_uiImgXCount = m_pImg->GetBmpWidth() / TILESIZE;
	m_uiImgYCount = m_pImg->GetBmpHeight() / TILESIZE;
}

void CTile::Release()
{
}

void CTile::Update()
{
}

void CTile::Render()
{
	int tileIndexX = (m_uiTileIndex % m_uiImgXCount);
	int tileIndexY = (m_uiTileIndex / m_uiImgYCount);

	RENDER->FrameImage(m_pImg, 
		m_vecPos, 
		m_vecPos + m_vecScale, 
		Vector(tileIndexX		* TILESIZE,	tileIndexY		* TILESIZE),
		Vector((tileIndexX + 1) * TILESIZE, (tileIndexY + 1) * TILESIZE));
}


