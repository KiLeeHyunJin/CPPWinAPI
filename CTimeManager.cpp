#include "framework.h"
#include "CTimeManager.h"

UINT CTimeManager::GetFPS()
{
	return m_uiFPS;
}

float CTimeManager::GetDeltaTime()
{
	return m_fDeltaTime;
}

void CTimeManager::Init()
{
	//prevTime = chrono::high_resolution_clock::now();
	m_uiFPS = 1;
	QueryPerformanceFrequency(&m_liCpuFrequency);
	QueryPerformanceCounter(&m_liPrevFrequency);
}

void CTimeManager::Update()
{
	QueryPerformanceCounter(&m_liCurrentFrequency);
	float differenceFrequency = static_cast<float>(m_liCurrentFrequency.QuadPart - m_liPrevFrequency.QuadPart);
	m_fDeltaTime = differenceFrequency / static_cast<float>(m_liCurrentFrequency.QuadPart);
	m_liPrevFrequency.QuadPart = m_liCurrentFrequency.QuadPart;

	//curTime = chrono::high_resolution_clock::now();

	//chrono::duration<float> elapsed = curTime - prevTime; // ���� �������̶� ���� �ð� ���
	//m_fDeltaTime = elapsed.count();

	////������ ���� �����̵� ������ ����
	//if (m_fDeltaTime > 0.1f)
	//{	m_fDeltaTime = 0.1f;	}

	//prevTime = curTime;

	//m_uiUpdateCount++;
	//m_fUpdateOnSecond += m_fDeltaTime;

	//if (m_fUpdateOnSecond >= 1.0f) // 1�ʰ� ������ ���
	//{
	//	m_uiFPS = m_uiUpdateCount; //������ ����

	//	m_uiUpdateCount = 0; // �ʱ�ȭ
	//	m_fUpdateOnSecond = 0;
	//}
}


