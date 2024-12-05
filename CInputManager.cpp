#include "framework.h"
#include "CInputManager.h"
#include "CPPWinAPI.h"


CInputManager::CInputManager()
{
	Init();
}

CInputManager::~CInputManager()
{
}

void CInputManager::Init()
{
	m_arrCurKey[0] = false;
	m_arrPrevKey[0] = false;
	m_ptMousePos = { 0,0 };
}

void CInputManager::Release()
{
}

void CInputManager::Update()
{
	if (GetFocus() != hWnd)
	{
		FocusOff();
	}
	else
	{
		FocusOn();
	}
}

void CInputManager::FocusOn()
{
	for (int key = 0; key < VKEY_SIZE; key++)
	{
		m_arrPrevKey[key] = m_arrCurKey[key];
		m_arrCurKey[key] = GetAsyncKeyState(key) & 0x8000;
	}
	GetCursorPos(&m_ptMousePos);
	ScreenToClient(hWnd, &m_ptMousePos);
}

void CInputManager::FocusOff()
{
	for (int key = 0; key < VKEY_SIZE; key++)
	{
		m_arrPrevKey[key] = m_arrCurKey[key];

		if (false != m_arrCurKey[key])
		{
			m_arrCurKey[key] = false;
		}
	}
}



bool CInputManager::GetButton(const int keyId)
{
	return m_arrCurKey[keyId];
}

bool CInputManager::GetButtonDown(const int keyId)
{
	if (m_arrPrevKey[keyId] == false &&
		m_arrCurKey[keyId] == true)
	{
		return true;
	}
	return false;
}

bool CInputManager::GetButtonUp(const int keyId)
{
	if (m_arrPrevKey[keyId] == true &&
		m_arrCurKey[keyId] == false)
	{
		return true;
	}
	return false;
}

POINT CInputManager::GetMousePos()
{
	return m_ptMousePos;
}
