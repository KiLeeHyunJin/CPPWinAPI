#include "framework.h"
#include "CCore.h"
#include "CPPWinAPI.h"

#include "CTimeManager.h"
#include "CRenderManager.h"
#include "CInputManager.h"
#include "CSceneManager.h"
#include "CEventManager.h"
#include "CCollisionManager.h"
#include "CPathManager.h"
#include "CResourceManager.h"
#include "CCameraManager.h"
#include "CUIManager.h"
#include "CSoundManager.h"

#pragma region Scene Header
#include "CScene.h"
#include "CSceneStage01.h"
#include "CSceneTitle.h"
#pragma endregion

CCore::CCore()
{	}

CCore::~CCore()
{	}

void CCore::Init()
{
	PATH->Init();
	RESOURCE->Init();

	EVENT->Init();
	//TIME::Init();

	INPUT->Init();
	RENDER->Init();

	COLLISION->Init();
	SCENE->Init();
	CAMERA->Init();
	UI->Init();
	SOUND->Init();
}

void CCore::Release()
{
	EVENT->Release();

	INPUT->Release();
	RENDER->Release();

	SCENE->Release();
	COLLISION->Release();

	PATH->Release();
	RESOURCE->Release();
	CAMERA->Release();
	UI->Release();
	SOUND->Release();
}

void CCore::Update()
{
	EVENT->Update();
	//TIME::Update();

	INPUT->Update();
	SCENE->Update();
	CAMERA->Update();

	COLLISION->PhysicsUpdate();
	UI->Update();
	SOUND->Update();
}

void CCore::Render() const
{
	RENDER->BeginDraw();

	SCENE->Render();
	CAMERA->Render();

#pragma region FPS
	//RENDER->SetText(TextType::Right);
	//wstring str = L"FPS : " + to_wstring(FPS);
	//RENDER->Text(WINSIZEX - 30, 0, str);
	Vector start	= CAMERA->ScreenToWorldPoint(Vector(WINSIZEX - 80, 0));
	Vector end		= CAMERA->ScreenToWorldPoint(Vector(WINSIZEX, 50));

	//RENDER->Text(str, start, end, Color(0, 0, 0, 1), 12);

#pragma endregion

#pragma region MousePos
	//RENDER->SetText(TextType::Left);
	Vector point = MOUSESCREENPOSITION;
	wstring pointStr = L"X : " + to_wstring((int)point.x) + L", Y : " + to_wstring((int)point.y);
	//RENDER->Text((float)point.x, (float)point.y, pointStr);
	start	= CAMERA->ScreenToWorldPoint(Vector(point.x, point.y - 5));
	end		= CAMERA->ScreenToWorldPoint(Vector(point.x + 80, point.y + 10));
	RENDER->Text(pointStr, start, end, Color(0, 0, 0, 1), 10);
#pragma endregion

	RENDER->EndDraw();
}





