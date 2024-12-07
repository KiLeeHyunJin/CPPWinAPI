#include "framework.h"
#include "CSceneTitle.h"
#include "CRenderManager.h"
#include "CPPWinAPI.h"

void CSceneTitle::Init()
{
}

void CSceneTitle::Release()
{
}

void CSceneTitle::Update()
{
}

void CSceneTitle::Render()
{
	RENDER->SetText(TextType::Middle);
	RENDER->Text(WINSIZEX * 0.5f, WINSIZEY * 0.5f, L"Press Space");
}

void CSceneTitle::Enter()
{
}

void CSceneTitle::Exit()
{
}
