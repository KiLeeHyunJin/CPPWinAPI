#include "framework.h"
#include "CCollider.h"
#include "CRenderManager.h"

#include "CGameObject.h"
#include "Logger.h"

CCollider::CCollider()
{
	m_vecPos = Vector(0, 0);
	m_vecOffset = Vector(0, 0);
	m_vecScale = Vector(0, 0);
}

CCollider::~CCollider()
{
}

Vector CCollider::GetPos()
{
	return m_vecPos;
}

Vector CCollider::GetOffset()
{
	return m_vecOffset;
}

Vector CCollider::GetScale()
{
	return m_vecScale;
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
	m_vecPos = GetOwner()->GetPosition() + m_vecOffset;
}

void CCollider::Render()
{
#ifdef _DEBUG
	RENDER->SetPen(PenType::Solid, RGB(255, 0, 0));
	RENDER->SetBrush(BrushType::Solid);
	RENDER->Rect(
		m_vecPos.x + m_vecOffset.x - m_vecScale.x,
		m_vecPos.y + m_vecOffset.y - m_vecScale.y,
		m_vecPos.x + m_vecOffset.x + m_vecScale.x,
		m_vecPos.y + m_vecOffset.y + m_vecScale.y
	);
#endif
}

void CCollider::OnCollision(CCollider* pOtherCollider)
{
	Logger::Debug(L"충돌 감지");
}

void CCollider::SetPos(Vector pos)
{
	m_vecPos = pos;
}

void CCollider::SetOffset(Vector offset)
{
	m_vecOffset = offset;
}

void CCollider::SetScale(Vector scale)
{
	m_vecScale = scale;
}
