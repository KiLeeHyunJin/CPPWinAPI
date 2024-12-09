#include "framework.h"
#include "CSceneManager.h"
#include "CPPWinAPI.h"

#include "CScene.h"
#include "CSceneTitle.h"
#include "CSceneStage01.h"

CSceneManager::CSceneManager():
	m_pCurScene(nullptr)
{	}

CSceneManager::~CSceneManager()
{	}

void CSceneManager::Init()
{

#pragma region  AddScene
	CScene* pSceneTitle = new CSceneTitle;
	m_mapScene.insert(make_pair(GroupScene::Title, pSceneTitle));

	CScene* pStatge01 = new CSceneStage01;
	m_mapScene.insert(make_pair(GroupScene::Stage01, pStatge01));
#pragma endregion

#pragma region  InitScene
	map<GroupScene, CScene*>::iterator iter;
	for (iter = m_mapScene.begin();
		iter != m_mapScene.end();
		iter++)
	{
		iter->second->Init();
	}
#pragma endregion

	m_pCurScene = pSceneTitle;
	m_pCurScene->Enter();
}

/// Release And Delete Scene
void CSceneManager::Release()			
{
	map<GroupScene, CScene*>::iterator iter;
	CScene* pScene;
	for (iter = m_mapScene.begin();
		iter != m_mapScene.end();
		iter++)
	{
		pScene = iter->second;

		pScene->Release();
		delete pScene;
	}

	m_mapScene.clear();
}

void CSceneManager::Update()			{ m_pCurScene->Update();	}

void CSceneManager::Render()			{ m_pCurScene->Render();	}

CScene* CSceneManager::GetCurScene()	{ return m_pCurScene;	}

void CSceneManager::ChangeScene(GroupScene changeScene)
{
	m_pCurScene->Exit();
	m_pCurScene = m_mapScene[changeScene];
	m_pCurScene->Enter();
}



