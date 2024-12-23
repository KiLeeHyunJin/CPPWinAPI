#include "framework.h"
#include "CScene.h"
#include "CGameObject.h"
#include "CCameraManager.h"
#include "CTile.h"

CScene::CScene():
	m_iTileSizeX(0), m_iTileSizeY(0)
{	}

CScene::~CScene()
{	}

void CScene::AddGameObject(CGameObject * pObj)
{
	m_listObj[(int)pObj->GetLayer()].push_back(pObj);
	pObj->Init();
}

void CScene::DeleteLayerObject(Layer deleteLayer)
{
	list<CGameObject*>& listObj = m_listObj[(int)deleteLayer];
	for (CGameObject* obj : listObj)
	{
		delete obj;
		obj = nullptr;
	}
	listObj.clear();
}

list<CGameObject*> CScene::GetLayerObject(Layer getLayer)
{
	return m_listObj[(int)getLayer];
}

void CScene::DeleteAll()
{
	for (list<CGameObject*>& listObjArr : m_listObj)
	{
		for (CGameObject* obj : listObjArr)
		{
			delete obj;
			obj = nullptr;
		}
		listObjArr.clear();
	}
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

void CScene::TileRender()
{
	Vector vecCamLook = CAMERA->GetLookAt();
	Vector vecLeftTop = vecCamLook - (Vector(WINSIZEX, WINSIZEY) * 0.5f);
	int iLTX = (int)vecLeftTop.x / CTile::TILESIZE;
	int iLTY = (int)vecLeftTop.y / CTile::TILESIZE;
	int iRBX = (int)WINSIZEX / CTile::TILESIZE;
	int iRBY = (int)WINSIZEY / CTile::TILESIZE;

	for (CGameObject* pObj : m_listObj[(int)Layer::Tile])
	{
		CTile* pTile = dynamic_cast<CTile*>(pObj);
		if (pTile != nullptr)
		{
			if (pTile->GetTilePosX() > iLTX - 5 && pTile->GetTilePosX() < iLTX + iRBX + 5 &&
				pTile->GetTilePosY() > iLTY - 5 && pTile->GetTilePosY() < iLTY + iRBY + 5)
			{
				pTile->Render();
			}
		}
	}
}

void CScene::LoadTile(const wstring& strPath)
{
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strPath.c_str(), L"rb");
	assert(pFile);
	UINT xCount = 0;
	UINT yCount = 0;
	fread(&xCount, sizeof(UINT), 1, pFile);
	fread(&yCount, sizeof(UINT), 1, pFile);
	CreateTiles(xCount, yCount);
	for (CGameObject* pObj : m_listObj[(int)Layer::Tile])
	{
		CTile* pTile = dynamic_cast<CTile*>(pObj);
		if (pTile != nullptr)
		{
			pTile->Load(pFile);
		}
	}
	fclose(pFile);
}

void CScene::CreateTiles(UINT sizeX, UINT sizeY)
{
	DeleteLayerObject(Layer::Tile);
	m_iTileSizeX = sizeX;
	m_iTileSizeY = sizeY;
	for (UINT y = 0; y < sizeY; y++)
	{
		for (UINT x = 0; x < sizeX; x++)
		{
			CTile* pTile = new CTile();
			pTile->SetTilePos(x, y);
			//pTile->SetLineRender(true);
			AddGameObject(pTile);
		}
	}
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


