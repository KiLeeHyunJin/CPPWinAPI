#pragma once
#include "CPPWinAPI.h"

class CCore;
class CScene;

class CSceneManager : 
	public SingleTon<CSceneManager>
{
public :
	CScene* GetCurScene();
	void ChangeScene(GroupScene changeScene);

	friend CCore;
	friend SingleTon<CSceneManager>;
private :
	CSceneManager();
	virtual ~CSceneManager();

	void Init();
	void Release();

	void Update();
	void Render();

	/// Scene
	map<GroupScene, CScene*>	m_mapScene;
	CScene*						m_pCurScene;
};
#define SCENE	CSceneManager::GetInstance()
