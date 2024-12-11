#include "framework.h"
#include "CGameObject.h"
#include "CComponent.h"

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

void CGameObject::AddComponent(CComponent* component)
{
	m_listComponent.push_back(component);
	component->Init();
	component->SetOwner(this);
}

void CGameObject::RemoveComponent(CComponent* component)
{
	m_listComponent.remove(component);
	component->Release();
	delete component;
}

void CGameObject::GameObjectInit()
{
	for (CComponent* component : m_listComponent)
	{
		component->Init();
	}
	Init();
}

void CGameObject::GameObjectUpdate()
{
	for (CComponent* component : m_listComponent)
	{
		component->Update();
	}
	Update();
}

void CGameObject::GameObjectRender()
{
	for (CComponent* component : m_listComponent)
	{
		component->Render();
	}
	Render();
}

void CGameObject::GameObjectRelease()
{
	for (CComponent* component : m_listComponent)
	{
		component->Release();
		delete component;
	}
	m_listComponent.clear();
	Release();
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


