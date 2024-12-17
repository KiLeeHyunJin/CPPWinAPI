#include "framework.h"
#include "CCameraManager.h"
#include "CTimeManager.h"
#include "CRenderManager.h"


#include "CGameObject.h"

CCameraManager::CCameraManager():
	m_pTarget(nullptr),
	m_fScale(0),
	m_fTimeToTarget(0),
	m_fTargetBright(1),
	m_fCurBright(1),
	m_fTimeToBright(0)
{
}

CCameraManager::~CCameraManager()
{
}

void CCameraManager::Init()
{
}

void CCameraManager::Release()
{
}

void CCameraManager::Update()
{
	if (nullptr != m_pTarget)
	{
		if (m_pTarget->GetReserveDelete())
		{
			m_pTarget = nullptr;
		}
		else
		{
			SetTargetPosition(m_pTarget->GetPosition());
		}
	}
	MoveToTarget();
	RenderEffect();
}

void CCameraManager::Render()
{
	Vector screenPos = ScreenToWorldPoint(Vector(0, 0));
	RENDER->FillRect(
		screenPos, 
		screenPos + Vector(WINSIZEX, WINSIZEY), 
		Color(0, 0, 0, 1 - m_fCurBright));
}

void CCameraManager::RenderEffect()
{
	m_fTimeToBright -= DeltaTime;
	if (m_fTimeToBright <= 0)
	{
		m_fCurBright = m_fTargetBright;
	}
	else
	{
		m_fCurBright += ((m_fTargetBright - m_fCurBright) / m_fTimeToBright) * DeltaTime;
	}
}

void CCameraManager::MoveToTarget()
{
	m_fTimeToTarget -= DeltaTime;
	if (m_fTimeToTarget <= 0)
	{
		m_vecLookAt = m_vecTargetPos;
	}
	else
	{
		m_vecLookAt = m_vecLookAt + ((m_vecTargetPos - m_vecLookAt) / m_fTimeToTarget) * DeltaTime;
	}
}

CGameObject* CCameraManager::GetTargetObject()
{
	return m_pTarget;
}

Vector CCameraManager::GetLookAt()
{
	return m_vecLookAt;
}

Vector CCameraManager::GetTargetPos()
{
	return m_vecTargetPos;
}
float CCameraManager::GetScale()
{
	return m_fScale;
}
//화면상의 좌표로 반환
Vector CCameraManager::WorldToScreenPoint(Vector vecWorld)
{
	return vecWorld - (m_vecLookAt - Vector(WINSIZEX * 0.5f , WINSIZEY * 0.5f));
}
//월드상의 좌표로 반환
Vector CCameraManager::ScreenToWorldPoint(Vector vecScreen)
{
	return vecScreen + (m_vecLookAt - Vector(WINSIZEX * 0.5f, WINSIZEY * 0.5f));
}

void CCameraManager::SetTargetPosition(Vector targetPos, float timeToTarget)
{
	m_vecTargetPos = targetPos;
	memcpy(&m_fTimeToTarget, &timeToTarget, sizeof(float));
}

void CCameraManager::SetTargetObject(CGameObject* targetObject)
{
	m_pTarget = targetObject;
}

void CCameraManager::SetScale(float scale)
{
	m_fScale = scale;
}

void CCameraManager::FadeIn(float duration)
{
	//m_fCurBright = 0;
	m_fTargetBright = 1;
	m_fTimeToBright = duration;

}

void CCameraManager::FadeOut(float duration)
{
	//m_fCurBright = 1;
	m_fTargetBright = 0;
	m_fTimeToBright = duration;
}

void CCameraManager::Scroll(Vector dir, float velocity)
{
	if (dir.SqrMagnitude() <= 0)
	{
		return;
	}

	m_vecTargetPos = m_vecLookAt + ((dir.Normalized() * velocity) * DeltaTime);
	memset(&m_fTimeToTarget, 0, sizeof(float));
}

