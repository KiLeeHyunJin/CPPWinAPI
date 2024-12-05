#include "framework.h"
#include "CCore.h"
#include "CPPWinAPI.h"
#include "CTimeManager.h"
#include "CRenderManager.h"
#include "CInputManager.h"


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

	m_fMoveX = m_fMoveY = 20;
}

void CCore::Release()
{
	TIME->Release();
	INPUT->Release();
	RENDER->Release();
}

void CCore::Update()
{
	TIME->Update();
	INPUT->Update();

	float speed = 20 * TIME->GetDeltaTime();
	
	if (BUTTONSTAY(VK_LEFT))
	{
		m_fMoveX -= speed;
	}
	if (BUTTONSTAY(VK_RIGHT))
	{
		m_fMoveX += speed;
	}

	if (BUTTONSTAY(VK_UP))
	{
		m_fMoveY -= speed;
	}
	if (BUTTONSTAY(VK_DOWN))
	{
		m_fMoveY += speed;
	}


	if (BUTTONDOWN(VK_SPACE))
	{
		m_fMoveY += speed * 100;
	}
}

void CCore::Render() const
{
	RENDER->BeginDraw();

	int size = 20;
	RENDER->SetPen(PenType::Dash, RGB(255, 0, 0), 1);
	RENDER->SetBrush(BrushType::Solid, RGB(255, 255, 0));
	RENDER->Rect(m_fMoveX - size, m_fMoveY - size, m_fMoveX + size, m_fMoveY + size);

	RENDER->SetText(TextType::Right);
	wstring str = L"FPS : " + to_wstring(FPS);
	RENDER->Text(WINSIZEX - 30, 0, str);

	RENDER->SetText(TextType::Left);
	POINT point = INPUT->GetMousePos();
	wstring pointStr = L"X : " + to_wstring(point.x) + L", Y : " + to_wstring(point.y);
	RENDER->Text(point.x, point.y, pointStr);

	RENDER->EndDraw();
}





