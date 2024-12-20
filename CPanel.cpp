#include "framework.h"
#include "CPanel.h"
#include "CRenderManager.h"
#include "CInputManager.h"
CPanel::CPanel()
{
	m_vecDragStartPos = Vector(0, 0);
	m_bDraggable = false;
	m_bIsDragging = false;
	m_bScreenFixed = true;
}

CPanel::~CPanel()
{
}

bool CPanel::GetDraggable()
{
	return m_bDraggable;
}

void CPanel::SetDraggable(bool dragState)
{
	m_bDraggable = dragState;
	m_bScreenFixed = dragState;
}

void CPanel::Init()
{
}

void CPanel::Release()
{
}

void CPanel::Update()
{
	if (m_bCurMouseOn)
	{
		m_colorFill = Color(0, 0, 255, 1);
	}
	else
	{
		m_colorFill = Color(255, 0, 255, 1);
	}
}

void CPanel::Render()
{
	RENDER->FillRect(m_vecRenderPos, m_vecRenderPos + m_vecScale, m_colorFill);
	RENDER->FrameRect(m_vecRenderPos, m_vecRenderPos + m_vecScale, Color(0,0,0,1));
}

void CPanel::OnMouseEnter()
{
}

void CPanel::OnMouseExit()
{
	if (m_bIsDragging)
	{
		m_bIsDragging = false;
	}
}

void CPanel::OnMouseOver()
{
	if (m_bIsDragging)
	{
		Vector vecDiff = MOUSESCREENPOSITION - m_vecDragStartPos;
		m_vecPos = m_vecPos + vecDiff;
		m_vecDragStartPos = MOUSESCREENPOSITION;
	}
}

void CPanel::OnMouseClicked()
{
}

void CPanel::OnMouseUp()
{
	if (m_bIsDragging)
	{
		m_bIsDragging = false;
		m_vecRenderPos = MOUSESCREENPOSITION;
	}
}

void CPanel::OnMouseDown()
{
	m_vecDragStartPos = MOUSESCREENPOSITION;
	m_bIsDragging = m_bDraggable;
}
