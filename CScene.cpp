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
	{	pGameObject->GameObjectInit();	}
}

void CScene::SceneRelease()
{
	for (CGameObject* pGameObject : m_listObj)
	{
		pGameObject->GameObjectRelease();
		delete pGameObject;
	}
	Release();
}

void CScene::SceneUpdate()
{
	for (CGameObject* pGameObject : m_listObj)
	{	
		if (pGameObject->GetReserveDelete() == false)
		{	pGameObject->GameObjectUpdate();	}
		else
		{	pGameObject->SetSafeToDelete();		}
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
	{	pGameObject->GameObjectRender();	}
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
