#include "framework.h"
#include "CPPWinAPI.h"
#include "CSceneStage01.h"

#include "CRenderManager.h"
#include "CInputManager.h"
#include "CEventManager.h"
#include "CCameraManager.h"

#include "CPlayer.h"
#include "CMonster.h"

void CSceneStage01::Init()
{


}

void CSceneStage01::Release()
{	}

void CSceneStage01::Update()
{
	if (BUTTONDOWN(VK_ESCAPE))
	{
		CAMERA->FadeOut(1);
		DELAYCHANGESCENE(GroupScene::Title, 1);
	}
	if (BUTTONDOWN(VK_LBUTTON))
	{

		CAMERA->SetTargetPosition(MOUSEWORLDPOSITION, 1);
	}
	Vector dir;
	if (BUTTONSTAY('A'))
	{
		dir.x = -1;
	}
	else if (BUTTONSTAY('D'))
	{
		dir.x = 1;
	}
	else if (BUTTONSTAY('W'))
	{
		dir.y = -1;

	}
	else if (BUTTONSTAY('S'))
	{
		dir.y = 1;
	}
	const Vector mousePos = MOUSESCREENPOSITION;
	if (mousePos.x < 40)
	{
		dir.x = -1;
	}
	else if (mousePos.x > WINSIZEX - 40)
	{
		dir.x = 1;
	}
	if (mousePos.y < 40)
	{
		dir.y = -1;
	}
	else if (mousePos.y > WINSIZEY - 40)
	{
		dir.y = 1;
	}

	if (BUTTONDOWN('Y'))
	{
		CAMERA->FadeIn(3);
	}
	if (BUTTONDOWN('H'))
	{
		CAMERA->FadeOut(3);
	}
	CAMERA->Scroll(dir, 300);
}

void CSceneStage01::Render()
{
	RENDER->SetText(TextType::Middle);
	RENDER->Text(WINSIZEX * 0.5f, WINSIZEY * 0.5f, L"Press Ctl + Esc");
}

void CSceneStage01::Enter()
{
	CPlayer* pPlayer = new CPlayer();
	AddGameObject(pPlayer);

	CMonster* pMonster = new CMonster();
	pMonster->SetPosition(WINSIZEX, WINSIZEY);
	pMonster->SetTarget(pPlayer);
	AddGameObject(pMonster);
	CAMERA->FadeIn(1);

	//CAMERA->SetTargetObject(pPlayer);

}

void CSceneStage01::Exit()
{
}
