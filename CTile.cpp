#include "framework.h"
#include "CTile.h"
#include "CResourceManager.h"
#include "CImage.h"
#include "CRenderManager.h"


CTile::CTile() :
	m_bLineRender(false), m_uiImgXCount(0), m_uiImgYCount(0),
	m_uiTileIndex(0), m_uiTilePosX(0), m_uiTilePosY(0)
{
	m_pImg = nullptr;
	m_strName = L"";
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
	m_uiImgXCount = (UINT)(m_pImg->GetBmpWidth()  / TILESIZE);
	m_uiImgYCount = (UINT)(m_pImg->GetBmpHeight() / TILESIZE);
}

void CTile::Release()
{
}

void CTile::Update()
{
}

void CTile::Render()
{
	int tileIndexX = 0;
	int tileIndexY = 0;
	if (m_uiImgXCount != 0)
	{
		tileIndexX = (m_uiTileIndex % m_uiImgXCount);
	}
	if (m_uiImgYCount != 0)
	{
		tileIndexY = (m_uiTileIndex / m_uiImgYCount);
	}

	RENDER->FrameImage(m_pImg, 
		m_vecPos, 
		m_vecPos + m_vecScale, 
		Vector(tileIndexX		* TILESIZE,	tileIndexY		* TILESIZE),
		Vector((tileIndexX + 1) * TILESIZE, (tileIndexY + 1) * TILESIZE));
}


