#include "framework.h"
#include "CGameObject.h"

CGameObject::CGameObject() :
	m_vecPos	(Vector(0,0)),
	m_vecScale	(Vector(0,0)),
	m_bReserveDelete(false),
	m_bSafeToDelete(false)
{
}

CGameObject::~CGameObject()
{	}

Vector CGameObject::GetPosition()	const
{
	return m_vecPos;
}

void CGameObject::SetPosition(Vector vecPos)
{
	memcpy(&m_vecPos, &vecPos, sizeof(Vector));
}

void CGameObject::SetScale(Vector vecScale)
{
	memcpy(&m_vecScale, &vecScale, sizeof(Vector));
}

void CGameObject::SetPosition(float x, float y)
{
	m_vecPos.x = x;
	m_vecPos.y = y;
}

void CGameObject::SetScale(float x, float y)
{
	m_vecScale.x = x;
	m_vecScale.y = y;
}

Vector CGameObject::GetScale()		const
{
	return m_vecScale;
}

bool CGameObject::GetSafeToDelete() const
{
	return m_bSafeToDelete;
}

bool CGameObject::GetReserveDelete() const
{
	return m_bReserveDelete;
}

void CGameObject::SetSafeToDelete()
{
	if (m_bSafeToDelete == false)
	{
		m_bSafeToDelete = true;
	}
}

void CGameObject::SetReserveDelete() 
{
	if (m_bReserveDelete == false)
	{
		m_bReserveDelete = true;
	}
}


