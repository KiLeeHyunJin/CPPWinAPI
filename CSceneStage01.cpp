#include "framework.h"
#include "CPPWinAPI.h"
#include "CSceneStage01.h"

#include "CRenderManager.h"
#include "CInputManager.h"
#include "CSceneManager.h"

#include "CPlayer.h"
void CSceneStage01::Init()
{
	AddGameObject(new CPlayer());
}

void CSceneStage01::Release()
{
}

void CSceneStage01::Update()
{
	if (BUTTONDOWN(VK_ESCAPE))
	{
		SCENE->ChangeScene(GroupScene::Title);
	}

}

void CSceneStage01::Render()
{
	RENDER->SetText(TextType::Middle);
	RENDER->Text(WINSIZEX * 0.5f, WINSIZEY * 0.5f, L"Press Ctl + Esc");

}

void CSceneStage01::Enter()
{
}

void CSceneStage01::Exit()
{
}
