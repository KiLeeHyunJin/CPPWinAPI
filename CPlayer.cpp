#include "framework.h"
#include "CPlayer.h"

#include "CInputManager.h"
#include "CTimeManager.h"
#include "CRenderManager.h"
#include "CEventManager.h"

#include "Logger.h"
#include "CCollider.h"

CPlayer::CPlayer()
{
	m_layer = Layer::Character;
}

CPlayer::~CPlayer()
{
}

void CPlayer::Init()
{
	SetScale(m_vecSize);
	SetPosition(m_vecPos);

	AddCollider(ColliderType::Rect,		0, Vector(20, 20), Vector(0, 0));
	AddCollider(ColliderType::Circle,	1, Vector(20, 20), Vector(20, 0));
}

void CPlayer::Release()
{
}

void CPlayer::Update()
{
	if (BUTTONSTAY(VK_RIGHT))
	{
		m_vecPos.x += m_fSpeed * DeltaTime;
	}
	if (BUTTONSTAY(VK_LEFT))
	{
		m_vecPos.x -= m_fSpeed * DeltaTime;
	}
	if (BUTTONSTAY(VK_UP))
	{
		m_vecPos.y -= m_fSpeed * DeltaTime;
	}
	if (BUTTONSTAY(VK_DOWN))
	{
		m_vecPos.y += m_fSpeed * DeltaTime;
	}
}

void CPlayer::Render()
{
	return;

	RENDER->SetPen(PenType::Solid, RGB(0, 255, 0), 1);
	RENDER->Rect(
		m_vecPos.x - m_vecScale.x, 
		m_vecPos.y - m_vecScale.y,
		m_vecPos.x + m_vecScale.x,
		m_vecPos.y + m_vecScale.y);
}

void CPlayer::OnCollisionStay(CCollider* pOtherCollider)
{
	Logger::Debug(L"�浹 ����");
}

