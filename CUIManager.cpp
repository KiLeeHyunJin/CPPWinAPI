#include "framework.h"
#include "CUIManager.h"
#include "CSceneManager.h"
#include "CInputManager.h"

#include "CScene.h"
#include "CUI.h"

CUIManager::CUIManager()
{
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
	CScene* pCurScene = SCENE->GetCurScene();
	const list<CGameObject*>& listUI = pCurScene->m_listObj[(int)Layer::Ui];
	for (CGameObject* pGameObj: listUI)
	{
		CUI* pUi = dynamic_cast<CUI*>(pGameObj);
		if (pUi != nullptr)
		{
			MouseEvent(pUi);
		}
	}
}

void CUIManager::MouseEvent(CUI* pUI)
{
	if (pUI->m_bCurMouseOn)
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
}
