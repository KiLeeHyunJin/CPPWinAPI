#include "framework.h"
#include "CEventManager.h"
#include "CSceneManager.h"
#include "CScene.h"
#include "CGameObject.h"
CEventManager::CEventManager()		{	}

CEventManager::~CEventManager()		{	}

void CEventManager::Init()			{	}

void CEventManager::Release()
{

}

void CEventManager::EventAddObject(CGameObject* pGameObj)
{
	m_quequeAddObject.push(pGameObj);
}

void CEventManager::EventDeleteObject(CGameObject* pGameObj)
{
	m_quequeDeleteObject.push(pGameObj);
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

void CEventManager::Update()
{
	ProgressAddObject();
	ProgressDeleteObject();
}


