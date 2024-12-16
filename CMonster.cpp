#include "framework.h"
#include "CMonster.h"

#include "CRenderManager.h"
#include "CTimeManager.h"

#include "CPlayer.h"
#include "CCollider.h"

CMonster::CMonster():
	m_pTarget(nullptr)
{
	m_layer = Layer::Monster;
}

CMonster::~CMonster()
{
}

void CMonster::SetTarget(CPlayer* pTargetPlayer)
{
	m_pTarget = pTargetPlayer;
}

void CMonster::Init()
{
	SetScale(Vector{ 20,10 });
	SetPosition(Vector{ WINSIZEX * 0.5f, WINSIZEY * 0.5f });
	AddCollider(ColliderType::Rect, 0, Vector(20, 50), Vector(0,0));

}

void CMonster::Release()
{
}

void CMonster::Update()
{
	return;
	Trace();
}

void CMonster::Render()
{
	return;

	//RENDER->Rect(
	//	m_vecPos.x - m_vecScale.x,
	//	m_vecPos.y - m_vecScale.y,
	//	m_vecPos.x + m_vecScale.x,
	//	m_vecPos.y + m_vecScale.y);
}

void CMonster::Trace()
{
	float speed = 30;

	bool dirX = (m_pTarget->GetPosition().x > m_vecPos.x) ? true : false;
	bool dirY = (m_pTarget->GetPosition().y > m_vecPos.y) ? true : false;

	if (dirX)
	{
		m_vecPos.x += speed * DeltaTime;
	}
	else
	{
		m_vecPos.x -= speed * DeltaTime;
	}

	if (dirY)
	{
		m_vecPos.y += speed * DeltaTime;
	}
	else
	{
		m_vecPos.y -= speed * DeltaTime;
	}
}
