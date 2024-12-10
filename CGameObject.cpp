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
{
}

Vector CGameObject::GetPosition()	const
{
	return m_vecPos;
}

void CGameObject::SetPosition(Vector pos)
{
	memcpy(&m_vecPos, &pos, sizeof(Vector));
}

void CGameObject::SetPosition(float x, float y)
{
	m_vecPos.x = x;
	m_vecPos.y = y;
}

Vector CGameObject::GetScale()		const
{
	return m_vecScale;
}

void CGameObject::SetScale(Vector scale)
{
	memcpy(&m_vecScale, &scale, sizeof(Vector));
}

void CGameObject::SetScale(float x, float y)
{
	m_vecScale.x = x;
	m_vecScale.y = y;
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


