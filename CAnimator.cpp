#include "framework.h"
#include "CAnimator.h"
#include "CAnimation.h"

CAnimator::CAnimator() :
	m_pCurAnim(nullptr)
{
	m_component = ComponentType::Animator;
	m_mapAnim.clear();
}

CAnimator::~CAnimator()	{	}

void CAnimator::Init()
{
	if (m_pCurAnim == nullptr)	{	return;		}
	m_pCurAnim->Init();
}

void CAnimator::Release()
{
	for (const pair<wstring, CAnimation*>& animPair : m_mapAnim)
	{
		m_pCurAnim->Release();
		delete animPair.second;
	}
	m_mapAnim.clear();
}

void CAnimator::Update()
{
	if (m_pCurAnim == nullptr)	{	return;		}

	m_pCurAnim->Update();
}

void CAnimator::Render()
{
	if (m_pCurAnim == nullptr)	{	return;		}

	m_pCurAnim->Render();
}


void CAnimator::Play(const wstring& animKey, bool trigger)
{
	if (m_pCurAnim	!=	nullptr && 
		animKey		==	m_pCurAnim->GetKey() && 
		trigger		==	false)
	{		return;		}

	CAnimation* pAnim = FindAnimation(animKey);
	assert(pAnim != nullptr && L"Animation no exist");

	if (trigger || m_pCurAnim != pAnim)
	{		pAnim->Replay();	}

	m_pCurAnim = pAnim;
}

void CAnimator::Stop()
{
	m_pCurAnim = nullptr;
}

void CAnimator::CreateAnimation(const wstring& animKey, CImage* pImg, Vector leftTop, Vector slice, Vector step, float duration, UINT count, bool repeat)
{
	CAnimation* pAnim = FindAnimation(animKey);
	assert(pAnim == nullptr && L"Animation already exist");

	pAnim = new CAnimation();
	pAnim->m_pAnimator = this;

	pAnim->Create(pImg, leftTop, slice, step, duration, count, repeat);
	pAnim->SetKey(animKey);
	pAnim->Init();

	m_mapAnim.insert(make_pair(animKey, pAnim));
}

void CAnimator::RemoveAnimation(const wstring& animKey)
{
	CAnimation* pAnim = FindAnimation(animKey);
	if (pAnim != nullptr)
	{
		m_mapAnim.erase(animKey);
		delete pAnim;
	}
}

CAnimation* CAnimator::FindAnimation(const wstring& animKey)
{
	map<wstring, CAnimation*>::iterator iter = m_mapAnim.find(animKey);
	return  iter == m_mapAnim.end() ? nullptr : iter->second ;
}







