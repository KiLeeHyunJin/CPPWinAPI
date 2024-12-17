#include "framework.h"
#include "CEventManager.h"
#include "CSceneManager.h"
#include "CTimeManager.h"

#include "CScene.h"
#include "CGameObject.h"

CEventManager::CEventManager():
	m_pChangeScene(nullptr)
{	}

CEventManager::~CEventManager()		{	}

void CEventManager::Init()			{	}

void CEventManager::Release()		{	}

void CEventManager::EventAddObject(CGameObject* pGameObj)
{
	m_quequeAddObject.push(pGameObj);
}

void CEventManager::EventDeleteObject(CGameObject* pGameObj)
{
	m_quequeDeleteObject.push(pGameObj);
}

void CEventManager::EventChangerScene(GroupScene eScene, float delay)
{
	if (m_pChangeScene == nullptr)
	{
		m_pChangeScene = new pair<GroupScene, float>(eScene, delay);
	}
	else if (m_pChangeScene->second > delay)
	{
		delete m_pChangeScene;
		m_pChangeScene = new pair<GroupScene, float>(eScene, delay);
	}
}

void CEventManager::ProgressAddObject()
{
	while (m_quequeAddObject.empty() == false)
	{
		CGameObject* obj = m_quequeAddObject.front();
		m_quequeDeleteObject.pop();
		SCENE->GetCurScene()->AddGameObject(obj);
	}
}

void CEventManager::ProgressDeleteObject()
{
	while (m_quequeDeleteObject.empty() == false)
	{
		CGameObject* obj = m_quequeDeleteObject.front();
		m_quequeDeleteObject.pop();
		obj->SetReserveDelete();
	}
}

void CEventManager::ProgressChangeScene()
{
	if (nullptr == m_pChangeScene)
	{
		return;
	}
	m_pChangeScene->second -= DeltaTime;
	if (m_pChangeScene->second <= 0)
	{
		GroupScene scene = m_pChangeScene->first;
		delete m_pChangeScene;
		m_pChangeScene = nullptr;

		SCENE->ChangeScene(scene);
	}
}

void CEventManager::Update()
{
	ProgressAddObject();
	ProgressDeleteObject();
	ProgressChangeScene();
}


