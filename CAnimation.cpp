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
	AnimationFrame frame = m_vecAnimFrame[m_uiCurFrame];
	RENDER->FrameImage(m_pImg, 
		Vector(pos - (frame.slice * 0.5f)), 
		Vector(pos + (frame.slice * 0.5f)),
		frame.leftTop, 
		frame.leftTop + frame.slice);
}

void CAnimation::Update()
{
	m_fAccTime += DeltaTime;
	if (m_vecAnimFrame[m_uiCurFrame].duration <= m_fAccTime)
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
	for (UINT i = 0; i < count; i++)
	{
		AnimationFrame frame;
		frame.slice = slice;
		frame.duration = duration;
		frame.leftTop = leftTop + (step * i);
		m_vecAnimFrame.push_back(frame);
	}
}

void CAnimation::Replay()
{
	memset(&m_uiCurFrame, 0, sizeof(UINT));
	memset(&m_fAccTime, 0, sizeof(float));
}
