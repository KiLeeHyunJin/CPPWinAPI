#include "framework.h"
#include "CInputManager.h"
#include "CCameraManager.h"
#include "CUIManager.h"
#include "CPPWinAPI.h"

CInputManager::CInputManager()
{	Init();	}

CInputManager::~CInputManager()	{	}

void CInputManager::Init()
{
	m_arrCurKey[0]	= false;
	m_arrPrevKey[0] = false;


	MouseFunc[0] = [](int keyId)
		{
			return CInputManager::GetInstance()->GetButtonDown(keyId);
		};
	MouseFunc[1] = [](int keyId)
		{
			return CInputManager::GetInstance()->GetButtonUp(keyId);
		};
	MouseFunc[2] = [](int keyId)
		{
			return CInputManager::GetInstance()->GetButton(keyId);
		};
}

void CInputManager::Release()	{	}

void CInputManager::Update()
{
	memcpy(m_arrPrevKey, m_arrCurKey, sizeof(bool) * VKEY_SIZE);

	if (GetFocus() != hWnd)
	{	FocusOff();	}
	else
	{	FocusOn();	}
}

void CInputManager::FocusOn()
{
	for (int key = 0; key < VKEY_SIZE; key++)
	{
		m_arrCurKey[key] = GetAsyncKeyState(key) & 0x8000;
	}
	POINT mousePoint;
	GetCursorPos(&mousePoint);
	ScreenToClient(hWnd, &mousePoint);
	m_vecMousePos.x = mousePoint.x;
	m_vecMousePos.y = mousePoint.y;
}

void CInputManager::FocusOff()
{	
	memset(m_arrCurKey, 0, sizeof(bool) * VKEY_SIZE);	
}

bool CInputManager::GetMouseOnUI()
{
	return UI->GetMouseOnUI();
}



bool CInputManager::GetButton(const int keyId)		const
{	return m_arrCurKey[keyId];			}

bool CInputManager::GetButtonDown(const int keyId)	const
{
	const bool buttonDownResult =
		m_arrPrevKey[keyId] == false	&&
		m_arrCurKey[keyId]	== true;

	return buttonDownResult;
}

bool CInputManager::GetButtonUp(const int keyId)	const
{
	const bool buttonUpResult =
		m_arrPrevKey[keyId] == true		&&
		m_arrCurKey[keyId]	== false;

	return buttonUpResult;
}

bool CInputManager::GetMouse(MouseState mouse, ClickState click, bool ignoreUI)
{
	bool state = MouseFunc[(int)mouse](m_arrMouseID[(int)click]);
	if (state)
	{
		if (ignoreUI) return true;
		else return GetMouseOnUI() == false;
	}
	return false;
}

Vector CInputManager::GetMouseScreenPosition() const
{
	return m_vecMousePos;	
}

Vector CInputManager::GetMouseWorldPosition() const
{
	return CAMERA->ScreenToWorldPoint(m_vecMousePos);
}
