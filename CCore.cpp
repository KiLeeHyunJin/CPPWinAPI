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

CCore::CCore()
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
	SCENE->Init();
}

void CCore::Release()
{
	TIME->Release();
	INPUT->Release();
	RENDER->Release();
	SCENE->Release();
}

void CCore::Update()
{
	TIME->Update();
	INPUT->Update();
	SCENE->Update();

	float speed = 20 * TIME->GetDeltaTime();



}

void CCore::Render() const
{
	RENDER->BeginDraw();
	SCENE->Render();

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





