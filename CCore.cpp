#include "framework.h"
#include "CCore.h"
#include "CPPWinAPI.h"
#include "CTimeManager.h"
#include "CRenderManager.h"
#include "CInputManager.h"
#include "CSceneManager.h"

#include "CScene.h"
#include "CSceneStage01.h"
#include "CSceneTitle.h"

CCore::CCore():	
	m_pCurScene		(nullptr),
	m_pSceneTitle	(nullptr),
	m_pSceneStage01	(nullptr)
{
}

CCore::~CCore()
{
}

void CCore::Init()
{
	TIME->Init();
	INPUT->Init();
	RENDER->Init();

	m_pSceneTitle = new CSceneTitle;
	m_pSceneStage01 = new CSceneStage01;
	
	m_pSceneTitle->Init();
	m_pSceneStage01->Init();

	m_pCurScene = m_pSceneTitle;
	m_pCurScene->Enter();
}

void CCore::Release()
{
	TIME->Release();
	INPUT->Release();
	RENDER->Release();

	m_pCurScene->Exit();

	m_pSceneTitle->Release();
	m_pSceneStage01->Release();

	delete m_pSceneTitle;
	delete m_pSceneStage01;
}

void CCore::Update()
{
	TIME->Update();
	INPUT->Update();

	float speed = 20 * TIME->GetDeltaTime();
	m_pCurScene->Update();

	if (BUTTONDOWN(VK_SPACE))
	{
		m_pCurScene->Exit();
		m_pCurScene = m_pSceneStage01;
		m_pCurScene->Enter();
	}
	if (BUTTONDOWN(VK_ESCAPE))
	{
		m_pCurScene->Exit();
		m_pCurScene = m_pSceneTitle;
		m_pCurScene->Enter();
	}
}

void CCore::Render() const
{
	RENDER->BeginDraw();

	m_pCurScene->Render();

#pragma region FPS
	RENDER->SetText(TextType::Right);
	wstring str = L"FPS : " + to_wstring(FPS);
	RENDER->Text(WINSIZEX - 30, 0, str);
#pragma endregion
#pragma region MousePos
	RENDER->SetText(TextType::Left);
	POINT point = INPUT->GetMousePos();
	wstring pointStr = L"X : " + to_wstring(point.x) + L", Y : " + to_wstring(point.y);
	RENDER->Text(point.x, point.y, pointStr);
#pragma endregion




	RENDER->EndDraw();
}





