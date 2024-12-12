#include "framework.h"
#include "CSceneManager.h"
#include "CPPWinAPI.h"

#include "CScene.h"
#include "CSceneTitle.h"
#include "CSceneStage01.h"

CSceneManager::CSceneManager() :
	m_pCurScene(nullptr)
{	}

CSceneManager::~CSceneManager()
{	
}

void CSceneManager::Init()
{

#pragma region  AddScene

	CScene* pSceneTitle = new CSceneTitle;
	m_mapScene.insert(make_pair(GroupScene::Title, pSceneTitle));

	CScene* pStatge01 = new CSceneStage01;
	m_mapScene.insert(make_pair(GroupScene::Stage01, pStatge01));

#pragma endregion

	for (pair<GroupScene, CScene*> scene : m_mapScene)
	{
		scene.second->SceneInit();
	}

	m_pCurScene = pSceneTitle;
	m_pCurScene->SceneEnter();
}

/// Release And Delete Scene
void CSceneManager::Release()			
{
	for (pair<GroupScene, CScene*> scene : m_mapScene)
	{
		scene.second->SceneRelease();
		delete scene.second;
	}
	m_mapScene.clear();
}

void CSceneManager::Update()			
{ 
	m_pCurScene->SceneUpdate();
	m_pCurScene->ScenePhysicsUpdate();
}

void CSceneManager::Render()			{ m_pCurScene->SceneRender();	}

CScene* CSceneManager::GetCurScene()	{ return m_pCurScene;			}

void CSceneManager::ChangeScene(GroupScene changeScene)
{
	m_pCurScene->SceneExit();
	m_pCurScene = m_mapScene[changeScene];
	m_pCurScene->SceneEnter();
}



