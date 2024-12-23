#include "framework.h"
#include "CButton.h"
#include "CRenderManager.h"
#include "Struct.h"

CButton::CButton()
{
	m_pCallBack = nullptr;
	m_pParam1 = 0;
	m_pParam2 = 0;
}

CButton::~CButton()
{
}

void CButton::SetClickedCallBack(CallBackFunc pCallback, DWORD_PTR param1, DWORD_PTR param2)
{
	m_pCallBack = pCallback;
	m_pParam1 = param1;
	m_pParam2 = param2;
}

void CButton::Init()
{
}

void CButton::Release()
{
}

void CButton::Update()
{
}

void CButton::Render()
{
	RENDER->FillRect(m_vecRenderPos, m_vecRenderPos + m_vecScale, m_ColorRect);
	RENDER->FrameRect(m_vecRenderPos, m_vecRenderPos + m_vecScale, Color(0, 0, 0, 1));
}

void CButton::OnMouseEnter()
{
}

void CButton::OnMouseExit()
{
	m_ColorRect = Color(0, 255, 255, 1);
}

void CButton::OnMouseOver()
{
	m_ColorRect = Color(255, 0, 0, 1);
}

void CButton::OnMouseClicked()
{
	if (m_pCallBack != nullptr)
	{
		m_pCallBack(m_pParam1, m_pParam2);
	}
}

void CButton::OnMouseUp()
{
}

void CButton::OnMouseDown()
{
}
