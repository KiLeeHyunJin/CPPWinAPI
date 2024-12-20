#include "framework.h"
#include "CUI.h"
#include "CCameraManager.h"
#include "CInputManager.h"


CUI::CUI():
	m_pParentUI(nullptr),
	m_bScreenFixed(false)
{
	m_vecAbsolutePos = Vector(0, 0);
	m_vecRenderPos = Vector(0, 0);
	m_layer = Layer::Ui;

	m_bPrevMouseOn = false;
	m_bCurMouseOn = false;
	m_bPrevMouseDown = false;
	m_bCurMouseDown = false;
}

CUI::~CUI()
{
}

CUI* CUI::GetParentUI()
{
	return m_pParentUI;
}

void CUI::SetParentUI(CUI* pParentUI)
{
	m_pParentUI = pParentUI;
}

void CUI::AddChildUI(CUI* pChildUI)
{
	m_listChildUI.push_back(pChildUI);
	pChildUI->SetParentUI(this);
	pChildUI->SetScreenFixed(m_bScreenFixed);
}

void CUI::RemoveChildUI(CUI* pChildUI)
{
	m_listChildUI.remove(pChildUI);
}

bool CUI::GetScreenFixed()
{
	return m_bScreenFixed;
}

void CUI::SetScreenFixed(bool bFixedState)
{
	m_bScreenFixed = bFixedState;
	for (CUI* childUI : m_listChildUI)
	{
		childUI->SetScreenFixed(bFixedState);
	}
}

void CUI::MouseOnCheck()
{
	Vector mousePos = MOUSESCREENPOSITION;
	Vector uiPos = CAMERA->WorldToScreenPoint(m_vecRenderPos);

	m_bPrevMouseOn = m_bCurMouseOn;

	if (uiPos.x <= mousePos.x && mousePos.x < uiPos.x + m_vecScale.x &&
		uiPos.y <= mousePos.y && mousePos.y < uiPos.y + m_vecScale.y)
	{
		m_bCurMouseOn = true;
	}
	else
	{
		m_bCurMouseOn = false;
	}
}

void CUI::Init()
{
}

void CUI::Release()
{
}

void CUI::Update()
{
}

void CUI::Render()
{
}

void CUI::GameObjectInit()
{
	Init();


	for (CUI* childUI : m_listChildUI)
	{
		childUI->GameObjectInit();
	}
}

void CUI::GameObjectUpdate()
{
	Update();

	m_vecAbsolutePos = m_vecPos;
	if (m_pParentUI != nullptr)
	{
		m_vecAbsolutePos = m_vecAbsolutePos + (m_pParentUI->m_vecAbsolutePos);
	}

	if (m_bScreenFixed == false)
	{
		m_vecRenderPos = CAMERA->ScreenToWorldPoint(m_vecAbsolutePos);
	}
	else
	{
		m_vecRenderPos = m_vecAbsolutePos;
	}

	for (CUI* childUI : m_listChildUI)
	{
		childUI->GameObjectUpdate();
	}
	MouseOnCheck();
}

void CUI::GameObjectRender()
{
	Render();
	for (CUI* childUI : m_listChildUI)
	{
		childUI->GameObjectRender();
	}
}

void CUI::GameObjectRelease()
{
	for (CUI* childUI : m_listChildUI)
	{
		childUI->GameObjectRelease();
		delete childUI;
	}
	m_listChildUI.clear();
	Release();
}
