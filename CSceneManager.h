#pragma once
#include "CPPWinAPI.h"

class CCore;
class CScene;
class CEventManager;
class CCollisionManager;
class CUIManager;

class CSceneManager : 
	public SingleTon<CSceneManager>
{
public :
	CScene* GetCurScene();

	friend CCore;
	friend SingleTon<CSceneManager>;
	friend CCollisionManager;
	friend CEventManager;
	friend CUIManager;
private :
	CSceneManager();
	virtual ~CSceneManager();

	void Init();
	void Release();

	void Update();
	void Render();

	void ChangeScene(GroupScene changeScene);

	void AddScene(CScene* pScene, GroupScene sceneName);
	/// Scene
	map<GroupScene, CScene*>	m_mapScene;
	CScene*						m_pCurScene;
};
#define SCENE	CSceneManager::GetInstance()
