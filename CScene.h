#pragma once
#include "CPPWinAPI.h"


class CSceneManager;
class CGameObject;
class CCollisionManager;
class CUIManager;
class CTileToolScene;

class CScene
{
public:
	CScene();
	virtual ~CScene();

	void AddGameObject(CGameObject* pObj);

protected:
	void DeleteLayerObject(Layer deleteLayer);
	list<CGameObject*> GetLayerObject(Layer getLayer);
	void DeleteAll();
	void CreateTiles(UINT sizeX, UINT sizeY);


	friend CSceneManager;
	friend CCollisionManager;
	friend CUIManager;
	friend CTileToolScene;
private:
	//코어에서 호출  // 게임오브젝트 호출 및 virtual 메소드 호출
	void SceneInit();
	void SceneRelease();

	void SceneUpdate();
	void ScenePhysicsUpdate();
	void SceneRender();

	void SceneEnter();
	void SceneExit();

	void TileRender();

	void LoadTile(const wstring& strPath);


	//수정해서 사용
	virtual void Init()		= 0;
	virtual void Release()	= 0;

	virtual void Update()	= 0;
	virtual void Render()	= 0;
	
	virtual void Enter()	= 0;
	virtual void Exit()		= 0;

	int m_iTileSizeX;
	int	m_iTileSizeY;

	list<CGameObject*> m_listObj[(int)Layer::Size];
	
};

