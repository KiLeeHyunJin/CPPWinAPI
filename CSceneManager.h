#pragma once
#include "CPPWinAPI.h"

class CCore;
class CScene;
class CEventManager;

class CSceneManager : 
	public SingleTon<CSceneManager>
{
public :
	CScene* GetCurScene();

	friend CCore;
	friend SingleTon<CSceneManager>;
	friend CEventManager;
private :
	CSceneManager();
	virtual ~CSceneManager();

	void Init();
	void Release();

	void Update();
	void Render();

	void ChangeScene(GroupScene changeScene);

	/// Scene
	map<GroupScene, CScene*>	m_mapScene;
	CScene*						m_pCurScene;
};
#define SCENE	CSceneManager::GetInstance()
