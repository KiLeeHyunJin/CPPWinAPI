#include "framework.h"
#include "CSceneManager.h"
#include "CPPWinAPI.h"

#include "CScene.h"
#include "CSceneTitle.h"
#include "CSceneStage01.h"
#include "CTileToolScene.h"

CSceneManager::CSceneManager() :
	m_pCurScene(nullptr)
{	}

CSceneManager::~CSceneManager()
{	
}

void CSceneManager::Init()
{
	CScene* pSceneTitle = new CSceneTitle;

#pragma region  AddScene


	AddScene(pSceneTitle, GroupScene::Title);
	AddScene(new CSceneStage01, GroupScene::Stage01);
	AddScene(new CTileToolScene, GroupScene::EditScene);


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

void CSceneManager::AddScene(CScene* pScene, GroupScene sceneName)
{
	m_mapScene.insert(make_pair(sceneName, pScene));
}



