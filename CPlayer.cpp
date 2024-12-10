#include "framework.h"
#include "CPlayer.h"

#include "CInputManager.h"
#include "CTimeManager.h"
#include "CRenderManager.h"
#include "CEventManager.h"

CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
}

void CPlayer::Init()
{
	SetScale(m_vecSize);
	SetPosition(m_vecPos);
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
	if (m_vecPos.x > 200)
	{
		DELETEOBJECT(this);
	}
}

void CPlayer::Render()
{
	RENDER->Rect(
		m_vecPos.x - m_vecSize.x, 
		m_vecPos.y - m_vecSize.y, 
		m_vecPos.x + m_vecSize.x, 
		m_vecPos.y + m_vecSize.y);
}

