#include "framework.h"
#include "CGroundTile.h"
#include "CCollider.h"

CGroundTile::CGroundTile()
{
	m_tileType = TileType::Ground;
}

CGroundTile::~CGroundTile()
{
}

void CGroundTile::Init()
{
	CTile::Init();
	const int tileSize = CTile::TILESIZE;
	const float halfSize = tileSize * 0.5f;
	AddCollider(ColliderType::Rect, 0, Vector(tileSize, tileSize), Vector(halfSize, halfSize));
}

void CGroundTile::Release()
{
}

void CGroundTile::Update()
{
	CTile::Update();
}

void CGroundTile::Render()
{
}

void CGroundTile::OnCollisionEnter(CCollider* pOther)
{
}

void CGroundTile::OnCollisionExit(CCollider* pOther)
{
}

void CGroundTile::OnCollisionStay(CCollider* pOther)
{
}
