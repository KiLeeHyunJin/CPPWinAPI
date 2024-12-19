#include "framework.h"
#include "CAnimation.h"
#include "CAnimator.h"

#include "CTimeManager.h"
#include "CRenderManager.h"

#include "CGameObject.h"

CAnimation::CAnimation() :
	m_fAccTime(0),
	m_uiCurFrame(0),
	m_pAnimator(nullptr),
	m_pImg(nullptr),
	m_bRepeat(false),
	m_strKey(L"")
{
}

CAnimation::~CAnimation()
{
}

const wstring& CAnimation::GetKey()
{
	return m_strKey;
}

void CAnimation::Init()
{
}

void CAnimation::Release()
{
}

void CAnimation::Render()
{
	Vector pos = m_pAnimator->GetOwner()->GetPosition();
	Vector vecLeftTop;
	memcpy(&vecLeftTop, &m_vecAnimFrame[m_uiCurFrame], sizeof(Vector));
	RENDER->FrameImage(m_pImg, 
		Vector(pos - (m_vecSliceScale * 0.5f)), 
		Vector(pos + (m_vecSliceScale * 0.5f)),
		vecLeftTop,
		vecLeftTop + m_vecSliceScale);
}

void CAnimation::Update()
{
	m_fAccTime += DeltaTime;
	if (m_fduration <= m_fAccTime)
	{
		m_uiCurFrame++;
		memset(&m_fAccTime, 0, sizeof(float));
		if (m_uiCurFrame == m_vecAnimFrame.size())
		{
			if (m_bRepeat)
			{
				memset(&m_uiCurFrame, 0, sizeof(UINT));
			}
			else
			{
				m_uiCurFrame--;
			}
		}
	}
}

void CAnimation::SetKey(const wstring& strKey)
{
	m_strKey = strKey;
}

void CAnimation::Create(CImage* pImg, Vector leftTop, Vector slice, Vector step, float duration, UINT count, bool repeat)
{
	m_pImg = pImg;
	m_bRepeat = repeat;
	m_fduration = duration;
	m_vecSliceScale = slice;
	for (UINT i = 0; i < count; i++)
	{
		m_vecAnimFrame.push_back(leftTop + (step * i));
	}
}

void CAnimation::Replay()
{
	memset(&m_uiCurFrame,	0, sizeof(UINT));
	memset(&m_fAccTime,		0, sizeof(float));
}
