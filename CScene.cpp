#include "framework.h"
#include "CScene.h"
#include "CGameObject.h"

CScene::CScene()
{	}

CScene::~CScene()
{	}

void CScene::AddGameObject(CGameObject * pObj)
{
	m_listObj.push_back(pObj);
	pObj->Init();
}

void CScene::SceneInit()
{
	Init();
	for (CGameObject* pGameObject : m_listObj)
	{	pGameObject->Init();	}
}

void CScene::SceneRelease()
{
	for (CGameObject* pGameObject : m_listObj)
	{
		pGameObject->Release();
		delete pGameObject;
	}
	Release();
}

void CScene::SceneUpdate()
{
	for (CGameObject* pGameObject : m_listObj)
	{	
		if (pGameObject->GetReserveDelete() == false)
		{
			pGameObject->Update();
		}
		else
		{
			pGameObject->SetSafeToDelete();
		}
	}

	Update();

	m_listObj.remove_if([](CGameObject* target)
		{
			if (target->GetSafeToDelete())
			{
				delete target;
				return true;
			}
			else
			{
				return false;
			}
		});
}

void CScene::SceneRender()
{
	for (CGameObject* pGameObject : m_listObj)
	{	pGameObject->Render();	}
	Render();
}


void CScene::SceneEnter()
{
	Enter();
}

void CScene::SceneExit()
{
	Exit();
}
