#include "framework.h"
#include "CUIManager.h"
#include "CSceneManager.h"
#include "CInputManager.h"

#include "CScene.h"
#include "CUI.h"

bool CUIManager::GetMouseOnUI()
{
	return m_bMouseOnUI;
}

CUIManager::CUIManager()
{
	m_bMouseOnUI = false;
	m_pFocusedUI = nullptr;

}

CUIManager::~CUIManager()
{
}

void CUIManager::Init()
{
}

void CUIManager::Release()
{
}

void CUIManager::Update()
{
	CUI* pTopUI = GetTopUI();
	CUI* pTopChildUI = GetTopChildUI(pTopUI);

	m_bMouseOnUI = pTopUI != nullptr;

	if (BUTTONDOWN(VK_LBUTTON))
	{
		SetFocusedUI(pTopUI);
	}

	CScene* pCurScene = SCENE->GetCurScene();
	const list<CGameObject*>& listUI = pCurScene->m_listObj[(int)Layer::Ui];
	for (CGameObject* pGameObj: listUI)
	{
		CUI* pUi = dynamic_cast<CUI*>(pGameObj);
		if (pUi != nullptr)
		{
			MouseEvent(pUi, pTopChildUI);
		}
	}
}

void CUIManager::MouseEvent(CUI* pUI, CUI* pTopChildUI)
{
	if (pUI == pTopChildUI && pUI->m_bCurMouseOn)
	{
		pUI->OnMouseOver();
		if (!pUI->m_bPrevMouseOn)
		{
			pUI->OnMouseEnter();
		}
		if (BUTTONDOWN(VK_LBUTTON))
		{
			pUI->OnMouseDown();
			pUI->m_bPrevMouseDown = true;
		}
		else if (BUTTONUP(VK_LBUTTON))
		{
			pUI->OnMouseUp();
			if (pUI->m_bPrevMouseDown)
			{
				pUI->OnMouseClicked();
				pUI->m_bPrevMouseDown = false;
			}
		}
	}
	else
	{
		if (pUI->m_bPrevMouseOn)
		{
			pUI->OnMouseExit();
		}
		else if (BUTTONUP(VK_LBUTTON))
		{
			pUI->m_bPrevMouseDown = false;
		}
	}
	for (CUI* pChildUI : pUI->m_listChildUI)
	{
		MouseEvent(pChildUI, pTopChildUI);
	}
}

void CUIManager::SetFocusedUI(CUI* pUI)
{
	if (m_pFocusedUI == pUI)
	{
		return;
	}
	if (pUI == nullptr)
	{
		m_pFocusedUI = nullptr;
		return;
	}
	m_pFocusedUI = pUI;
	CScene* pCurScene = SCENE->GetCurScene();
	list<CGameObject*>& listUI = pCurScene->m_listObj[(int)Layer::Ui];

	listUI.remove(m_pFocusedUI);
	listUI.push_back(m_pFocusedUI);
}

CUI* CUIManager::GetFocusedUI()
{
	return m_pFocusedUI;
}

CUI* CUIManager::GetTopUI()
{
	CScene* pCurScene = SCENE->GetCurScene();
	const list<CGameObject*> listUI = pCurScene->m_listObj[(int)Layer::Ui];

	for (auto iter = listUI.rbegin(); iter != listUI.rend(); iter++)
	{
		CUI* pUI = (CUI*)(*iter);
		if (pUI->m_bCurMouseOn)
		{
			return pUI;
		}
	}

	return nullptr;
}

CUI* CUIManager::GetTopChildUI(CUI* pUI)
{
	if (pUI == nullptr)
	{
		return nullptr;
	}
	queue<CUI*> queueUI;
	queueUI.push(pUI);

	CUI* pTargetUI = nullptr;

	while (!queueUI.empty())
	{
		CUI* pUI = queueUI.front();
		queueUI.pop();

		if (pUI->m_bCurMouseOn)
		{
			pTargetUI = pUI;
			for (CUI* pChildUI : pUI->m_listChildUI)
			{
				queueUI.push(pChildUI);
			}
		}
	}
	return pTargetUI;
}
