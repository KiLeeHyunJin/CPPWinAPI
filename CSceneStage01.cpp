#include "framework.h"
#include "CPPWinAPI.h"
#include "CSceneStage01.h"

#include "CRenderManager.h"
#include "CInputManager.h"
#include "CEventManager.h"

#include "CPlayer.h"
#include "CMonster.h"

void CSceneStage01::Init()
{
	CPlayer* pPlayer = new CPlayer();
	AddGameObject(pPlayer);

	CMonster* pMonster = new CMonster();
	pMonster->SetPosition(WINSIZEX, WINSIZEY);
	pMonster->SetTarget(pPlayer);
	AddGameObject(pMonster);
}

void CSceneStage01::Release()
{
}

void CSceneStage01::Update()
{
	if (BUTTONDOWN(VK_ESCAPE))
	{
		CHANGESCENE(GroupScene::Title);
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
