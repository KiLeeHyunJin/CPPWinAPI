#include "framework.h"
#include "CSceneStage01.h"
#include "CRenderManager.h"
#include "CPPWinAPI.h"

void CSceneStage01::Init()
{
}

void CSceneStage01::Release()
{
}

void CSceneStage01::Update()
{
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
