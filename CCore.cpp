#include "framework.h"
#include "CCore.h"
#include "CPPWinAPI.h"
#include "CTimeManager.h"

CCore::CCore()
	:m_hdc(nullptr), m_fMoveX(INT_MIN), m_fMoveY(INT_MIN)
{
}

CCore::~CCore()
{
}

void CCore::Init()
{
	TIME->Init();

	m_hdc = GetDC(hWnd);
	m_fMoveX = m_fMoveY = 20;
}

void CCore::Update()
{
	TIME->Update();

	float speed = 1 * TIME->GetDeltaTime();
	
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
	int size = 20;
	Rectangle(m_hdc, m_fMoveX - size, m_fMoveY - size, m_fMoveX + size, m_fMoveY + size);

	wstring fps = to_wstring(FPS);
	TextOutW(m_hdc, 700, 10, fps.c_str(), fps.size());

	wstring left = to_wstring(m_fMoveX - size);
	wstring right = to_wstring(m_fMoveX + size);

	wstring top = to_wstring(m_fMoveY - size);
	wstring bottom = to_wstring(m_fMoveY + size);


	TextOutW(m_hdc, 600, 30, right.c_str(), right.size());
	TextOutW(m_hdc, 500, 30, left.c_str(), left.size());

	TextOutW(m_hdc, 600, 50, top.c_str(), top.size());
	TextOutW(m_hdc, 500, 50, bottom.c_str(), bottom.size());
}

void CCore::Release()
{
	TIME->Release();

	ReleaseDC(hWnd, m_hdc);
}



