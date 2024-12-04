#include "framework.h"
#include "CCore.h"
#include "CPPWinAPI.h"
#include "CTimeManager.h"
#include "CRenderManager.h"

CCore::CCore()
{
}

CCore::~CCore()
{
}

void CCore::Init()
{
	TIME->Init();
	RENDER->Init();

	m_fMoveX = m_fMoveY = 20;
}

void CCore::Release()
{
	TIME->Release();
	RENDER->Release();
}

void CCore::Update()
{
	TIME->Update();

	float speed = 20 * TIME->GetDeltaTime();
	
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_fMoveX -= speed;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_fMoveX += speed;
	}

	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		m_fMoveY -= speed;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		m_fMoveY += speed;
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

	RENDER->EndDraw();
}





