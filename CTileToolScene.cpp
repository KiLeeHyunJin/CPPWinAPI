#include "framework.h"
#include "CTileToolScene.h"
#include "CInputManager.h"
#include "CEventManager.h"
#include "CCameraManager.h"

CTileToolScene::CTileToolScene()
{
}

CTileToolScene::~CTileToolScene()
{
}

void CTileToolScene::Init()
{
}

void CTileToolScene::Release()
{
}

void CTileToolScene::Render()
{
}

void CTileToolScene::Update()
{
	if (BUTTONDOWN(VK_F1))
	{
		CHANGESCENE(GroupScene::Title);
	}
	if (BUTTONDOWN(VK_SPACE))
	{
		CAMERA->FadeOut(0.25f);
		DELAYCHANGESCENE(GroupScene::Stage01, 0.25f);
	}
}

void CTileToolScene::Enter()
{
}

void CTileToolScene::Exit()
{
}
