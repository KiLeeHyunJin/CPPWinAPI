#include "framework.h"
#include "CCollider.h"
#include "CRenderManager.h"

#include "CGameObject.h"

UINT CCollider::s_uiID = 0;

CCollider::CCollider():
	m_uiCollisionCount(0)
{
	m_component = ComponentType::Collider;
	m_vecPos		= Vector(0, 0);
	m_uiID = s_uiID++;
}

CCollider::~CCollider()
{	}

void CCollider::Init()
{	}

void CCollider::Release()
{	}

UINT CCollider::GetID()
{
	return m_uiID;
}


Vector CCollider::GetPos()
{
	return m_vecPos;
}

Vector CCollider::GetOffset(SHORT offsetId)
{
	map<SHORT, ColliderMatrix>::iterator iter = m_mapColliderTransform.find(offsetId);
	if (iter == m_mapColliderTransform.end())
	{	return Vector(0, 0);	}
	return iter->second.offset;
}

Vector CCollider::GetScale(SHORT scaleId)
{
	map<SHORT, ColliderMatrix>::iterator iter = m_mapColliderTransform.find(scaleId);
	if (iter == m_mapColliderTransform.end())
	{	return Vector(0, 0);	}
	return iter->second.scale;
}

Size CCollider::GetBaseSize()
{
	return m_sizeBase + m_vecPos;
}

const wstring* CCollider::GetName()
{
	return GetOwner()->GetName();;
}

void CCollider::Update()
{

}

void CCollider::PhysicsUpdate()
{
	m_vecPos = GetOwner()->GetPosition();
}

void CCollider::Render()
{
#ifdef _DEBUG
	RENDER->SetPen(PenType::Solid, RGB(255, 0, 0));
	RENDER->SetBrush(BrushType::Solid);


	for (const pair<SHORT,ColliderMatrix>& matrix : m_mapColliderTransform)
	{
		const Vector scale = matrix.second.scale;
		const Vector offset = matrix.second.offset;
		const ColliderType type = matrix.second.type;
		if (type == ColliderType::Rect)
		{
			RENDER->Rect(
				m_vecPos.x + (offset.x) - (scale.x),
				m_vecPos.y + (offset.y) - (scale.y),
				m_vecPos.x + (offset.x) + (scale.x),
				m_vecPos.y + (offset.y) + (scale.y)
			);
		}
		else if (type == ColliderType::Circle)
		{
			RENDER->Circle(
				m_vecPos.x + (offset.x), 
				m_vecPos.y + (offset.y),
				scale.x);
		}
	}
	
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

void CCollider::SetCollider(ColliderType type, SHORT colliderId, Vector offset, Vector scale)
{
	scale = scale * 0.5f;
	if (m_mapColliderTransform.size() == 0)
	{
		m_sizeBase.left			= offset.x - scale.x;
		m_sizeBase.right		= offset.x + scale.x;
		m_sizeBase.top			= offset.y - scale.y;
		m_sizeBase.bottom		= offset.y + scale.y;
	}
	else
	{
		if (m_sizeBase.left		> offset.x - scale.x)
		{
			m_sizeBase.left		= offset.x - scale.x;
		}
		if (m_sizeBase.right	< offset.x + scale.x)
		{
			m_sizeBase.right	= offset.x + scale.x;
		}
		if (m_sizeBase.top		> offset.y - scale.y)
		{
			m_sizeBase.top		= offset.y - scale.y;
		}
		if (m_sizeBase.bottom	< offset.y - scale.y)
		{
			m_sizeBase.bottom	= offset.y - scale.y;
		}
	}
	m_mapColliderTransform.insert(
		pair<SHORT, ColliderMatrix> (colliderId, ColliderMatrix(type, offset, scale))
	);
}

void CCollider::SetPos(Vector pos)
{
	m_vecPos = pos;
}
