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

	chrono::duration<float> elapsed = curTime - prevTime; // ���� �������̶� ���� �ð� ���
	m_fDeltaTime = elapsed.count();
	prevTime = curTime;

	m_uiUpdateCount++;
	m_fUpdateOnSecond += m_fDeltaTime;

	if (m_fUpdateOnSecond >= 1.0f) // 1�ʰ� ������ ���
	{
		m_uiFPS = m_uiUpdateCount; //������ ����

		m_uiUpdateCount = 0; // �ʱ�ȭ
		m_fUpdateOnSecond = 0;
	}
}

