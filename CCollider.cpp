#include "framework.h"
#include "CCollider.h"
#include "CRenderManager.h"

#include "CGameObject.h"

UINT CCollider::s_uiID = 0;

CCollider::CCollider():
	m_uiCollisionCount(0)
{
	m_component = Component::Collider;
	m_cmatrixTransform.pos		= Vector(0, 0);
	m_cmatrixTransform.scale	= Vector(0, 0);
	m_cmatrixTransform.offset	= Vector(0, 0);
	m_uiID = s_uiID++;
}

CCollider::~CCollider()
{
}

UINT CCollider::GetID()
{
	return m_uiID;
}


Vector CCollider::GetPos()
{
	return m_cmatrixTransform.pos;
}

Vector CCollider::GetOffset()
{
	return m_cmatrixTransform.offset;
}

Vector CCollider::GetScale()
{
	return m_cmatrixTransform.scale;
}

const wstring* CCollider::GetName()
{
	return GetOwner()->GetName();;
}

void CCollider::Init()
{
}

void CCollider::Release()
{
}

void CCollider::Update()
{
}

void CCollider::PhysicsUpdate()
{
	m_cmatrixTransform.pos = GetOwner()->GetPosition() + m_cmatrixTransform.offset;
}

void CCollider::Render()
{
#ifdef _DEBUG
	RENDER->SetPen(PenType::Solid, RGB(255, 0, 0));
	RENDER->SetBrush(BrushType::Solid);
	RENDER->Rect(
		m_cmatrixTransform.pos.x - (m_cmatrixTransform.scale.x * 0.5f),
		m_cmatrixTransform.pos.y - (m_cmatrixTransform.scale.y * 0.5f),
		m_cmatrixTransform.pos.x + (m_cmatrixTransform.scale.x * 0.5f),
		m_cmatrixTransform.pos.y + (m_cmatrixTransform.scale.y * 0.5f)
	);
#endif
}

void CCollider::OnCollisionEnter(CCollider* pOtherCollider)
{
	m_uiCollisionCount++;
	GetOwner()->OnCollisionEnter(pOtherCollider);
}

void CCollider::OnCollisionStay(CCollider* pOtherCollider)
{
	GetOwner()->OnCollisionStay(pOtherCollider);
}

void CCollider::OnCollisionExit(CCollider* pOtherCollider)
{
	m_uiCollisionCount--;
	GetOwner()->OnCollisionExit(pOtherCollider);
}

void CCollider::SetPos(Vector pos)
{
	m_cmatrixTransform.pos = pos;
}

void CCollider::SetOffset(Vector offset)
{
	m_cmatrixTransform.offset = offset;
}

void CCollider::SetScale(Vector scale)
{
	m_cmatrixTransform.scale = scale;
}
