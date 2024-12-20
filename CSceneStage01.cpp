#include "framework.h"
#include "CPPWinAPI.h"
#include "CSceneStage01.h"

#include "CRenderManager.h"
#include "CInputManager.h"
#include "CEventManager.h"
#include "CCameraManager.h"

#include "CPlayer.h"
#include "CMonster.h"
#include "CButton.h"
#include "CPanel.h"

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
	if (LMOUSEDOWN(false))
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
	//const Vector mousePos = MOUSESCREENPOSITION;
	//if (mousePos.x < 40)
	//{
	//	dir.x = -1;
	//}
	//else if (mousePos.x > WINSIZEX - 40)
	//{
	//	dir.x = 1;
	//}
	//if (mousePos.y < 40)
	//{
	//	dir.y = -1;
	//}
	//else if (mousePos.y > WINSIZEY - 40)
	//{
	//	dir.y = 1;
	//}

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
	CButton* pButton1 = new CButton();
	pButton1->SetPosition(Vector(100, 100));
	pButton1->SetScale(Vector(100, 100));
	AddGameObject(pButton1);


	CPanel* pPanel = new CPanel();
	pPanel->SetPosition(Vector(0, 0));
	pPanel->SetScale(Vector(500, 500));
	pPanel->SetDraggable(true);
	AddGameObject(pPanel);

	CPanel* pPanel1 = new CPanel();
	pPanel1->SetPosition(Vector(100, 0));
	pPanel1->SetScale(Vector(500, 500));
	pPanel1->SetDraggable(true);
	AddGameObject(pPanel1);



	CButton* pButton = new CButton();
	pButton->SetPosition(Vector(100, 100));
	pButton->SetScale(Vector(100, 100));
	pPanel->AddChildUI(pButton);




}

void CSceneStage01::Exit()
{
}
