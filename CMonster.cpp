#include "framework.h"
#include "CMonster.h"

#include "CRenderManager.h"
#include "CTimeManager.h"

#include "CPlayer.h"

CMonster::CMonster():
	m_pTarget(nullptr)
{
	SetScale(Vector{10,10});
	SetPosition(Vector{ 0,0 });
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
}

void CMonster::Release()
{
}

void CMonster::Update()
{
	float speed = 10;

	bool dirX	= (m_pTarget->GetPosition().x > m_vecPos.x) ? true : false;
	bool dirY	= (m_pTarget->GetPosition().y > m_vecPos.y) ? true : false;
	
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

void CMonster::Render()
{
	RENDER->Rect(
		m_vecPos.x - m_vecScale.x,
		m_vecPos.y - m_vecScale.y,
		m_vecPos.x + m_vecScale.x,
		m_vecPos.y + m_vecScale.y);
}

void CMonster::Trace()
{
}
