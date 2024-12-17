#include "framework.h"
#include "CSceneTitle.h"
#include "CPPWinAPI.h"

#include "CRenderManager.h"
#include "CInputManager.h"
#include "CEventManager.h"
#include "CCameraManager.h"


void CSceneTitle::Init()
{
}

void CSceneTitle::Release()
{
}

void CSceneTitle::Update()
{
	if (BUTTONDOWN(VK_SPACE))
	{
		CAMERA->FadeOut(1);
		DELAYCHANGESCENE(GroupScene::Stage01, 1);
	}
}

void CSceneTitle::Render()
{
	RENDER->SetText(TextType::Middle);
	RENDER->Text(WINSIZEX * 0.5f, WINSIZEY * 0.5f, L"Press Space");
}

void CSceneTitle::Enter()
{
	CAMERA->FadeIn(1);
}

void CSceneTitle::Exit()
{
}
