#include "framework.h"
#include "CScene.h"
#include "CGameObject.h"
#include "CCameraManager.h"


CScene::CScene()
{	}

CScene::~CScene()
{	}

void CScene::AddGameObject(CGameObject * pObj)
{
	m_listObj[(int)pObj->GetLayer()].push_back(pObj);
	pObj->Init();
}


void CScene::SceneEnter()
{
	CAMERA->SetTargetObject(nullptr);
	CAMERA->SetTargetPosition(Vector(WINSIZEX * 0.5f, WINSIZEY * 0.5f));
	Enter();
}

void CScene::SceneExit()
{
	Exit();
}

void CScene::SceneInit()
{
	Init();
	//for (int i = 0; i < (int)Layer::Size; i++)
	//{
	//	for (CGameObject* pGameObject : m_listObj[i])
	//	{
	//		pGameObject->GameObjectInit();
	//	}
	//}
}

void CScene::SceneRelease()
{
	for (int i = 0; i < (int)Layer::Size; i++)
	{
		for (CGameObject* pGameObject : m_listObj[i])
		{
			pGameObject->GameObjectRelease();
			delete pGameObject;
		}
	}

	Release();
}

void CScene::SceneUpdate()
{
	for (int i = 0; i < (int)Layer::Size; i++)
	{
		m_listObj[i].remove_if([](CGameObject* target)
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

	for (int i = 0; i < (int)Layer::Size; i++)
	{
		for (CGameObject* pGameObject : m_listObj[i])
		{
			if (pGameObject->GetReserveDelete())
			{
				pGameObject->SetSafeToDelete();
			}
			else
			{
				pGameObject->GameObjectUpdate();
			}
		}
	}

	Update();
}

void CScene::ScenePhysicsUpdate()
{
	for (int i = 0; i < (int)Layer::Size; i++)
	{
		for (CGameObject* pGameObject : m_listObj[i])
		{
			pGameObject->GameObjectPhysicsUpdate();
		}
	}
}

void CScene::SceneRender()
{
	for (list<CGameObject*> listGameObject : m_listObj)
	{
		for (CGameObject* pGameObject : listGameObject)
		{
			pGameObject->GameObjectRender();
		}
	}
	Render();
}


