#include "framework.h"
#include "CPlayer.h"

#include "CInputManager.h"
#include "CTimeManager.h"
#include "CRenderManager.h"

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
}

void CPlayer::Render()
{
	RENDER->Rect(m_vecPos.x - m_vecSize.x, m_vecPos.y - m_vecSize.y, m_vecPos.x + m_vecSize.x, m_vecPos.y + m_vecSize.y);
}

void CPlayer::Release()
{
}
