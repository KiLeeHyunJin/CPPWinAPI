#include "framework.h"
#include "CTimeManager.h"


CTimeManager::CTimeManager():
	m_fDeltaTime(1), m_uiFPS(1), 
	m_fUpdateOnSecond(0), m_uiUpdateCount(0)
{
	prevTime = {};
	curTime = {};
}

CTimeManager::~CTimeManager()
{
}

void CTimeManager::Init()
{
	prevTime = chrono::high_resolution_clock::now();
}

void CTimeManager::Release()
{

}

UINT CTimeManager::GetFPS() const
{
	return m_uiFPS;
}

float CTimeManager::GetDeltaTime() const
{
	return m_fDeltaTime;
}

void CTimeManager::Update()
{
	curTime = chrono::high_resolution_clock::now();

	chrono::duration<float> elapsed = curTime - prevTime; // 이전 프레임이랑 차이 시간 계산
	m_fDeltaTime = elapsed.count();

	//지연에 의한 순간이동 현상을 억제
	if (m_fDeltaTime > 0.1f)
	{	m_fDeltaTime = 0.1f;	}

	prevTime = curTime;

	m_uiUpdateCount++;
	m_fUpdateOnSecond += m_fDeltaTime;

	if (m_fUpdateOnSecond >= 1.0f) // 1초간 프레임 계산
	{
		m_uiFPS = m_uiUpdateCount; //프레임 갱신

		m_uiUpdateCount = 0; // 초기화
		m_fUpdateOnSecond = 0;
	}
}

