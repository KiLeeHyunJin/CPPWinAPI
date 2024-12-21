#include "framework.h"
#include "CTile.h"

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
