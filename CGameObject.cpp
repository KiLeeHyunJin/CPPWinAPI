#include "framework.h"
#include "CGameObject.h"
#include "CComponent.h"
#include "CCollider.h"

CGameObject::CGameObject() :
	m_vecPos	(Vector(0,0)),
	m_vecScale	(Vector(0,0)),
	m_bReserveDelete(false),
	m_bSafeToDelete(false),
	m_layer(Layer::Default),
	m_strName(L"")
{
}

CGameObject::~CGameObject()
{	}

Vector CGameObject::GetPosition()
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

const wstring* CGameObject::GetName()
{
	return &m_strName;
}

void CGameObject::SetName(const wstring& name)
{
	m_strName = name;
}

Vector CGameObject::GetScale()
{
	return m_vecScale;
}

bool CGameObject::GetSafeToDelete()
{
	return m_bSafeToDelete;
}

void CGameObject::AddComponent(CComponent* component)
{
	ComponentType com = component->GetComponentType();
	map<ComponentType, CComponent*>::iterator iter = m_mapComponent.find(com);
	if (iter == m_mapComponent.end())
	{
		m_mapComponent.insert(pair<ComponentType, CComponent*> (com, component));
	}
	else
	{
		//iter->second.push_back(component);
	}
	component->Init();
	component->SetOwner(this);
}

void CGameObject::RemoveComponent(CComponent* component)
{
	const ComponentType componentType = component->GetComponentType();
	map<ComponentType, CComponent*>::iterator iter = m_mapComponent.find(componentType);
	if (iter == m_mapComponent.end())
	{
		return;
	}
	component->Release();
	delete component;
	m_mapComponent.erase(componentType);
}

void CGameObject::AddCollider(ColliderType type, SHORT colliderId, Vector scale, Vector offset)
{
	map<ComponentType, CComponent*>::iterator iter = m_mapComponent.find(ComponentType::Collider);
	CCollider* m_pCollider = nullptr;
	if (iter == m_mapComponent.end())
	{
		m_pCollider = new CCollider();
	}
	else
	{
		m_pCollider = reinterpret_cast<CCollider*>(iter->second);
	}

	m_pCollider->SetCollider(type, colliderId, offset, scale);

	AddComponent(m_pCollider);
}

void CGameObject::RemoveCollider()
{
	map<ComponentType, CComponent*>::iterator iter = m_mapComponent.find(ComponentType::Collider);
	if (iter != m_mapComponent.end())
	{
		CComponent* component = iter->second;
		iter->second = nullptr;
		component->Release();
		delete component;
	}
}

CCollider* CGameObject::GetCollider()
{
	map<ComponentType, CComponent*>::iterator iter = m_mapComponent.find(ComponentType::Collider);
	if (iter == m_mapComponent.end())
	{
		return nullptr;
	}
	return reinterpret_cast<CCollider*>(iter->second);
}

void CGameObject::GameObjectInit()
{
	for (pair<ComponentType, CComponent*> component : m_mapComponent)
	{
		component.second->Init();
	}
	Init();
}

void CGameObject::GameObjectUpdate()
{
	Update();

	for (const pair<ComponentType, CComponent*>& component : m_mapComponent)
	{
		component.second->Update();
	}
}

void CGameObject::GameObjectPhysicsUpdate()
{
	for (const pair<ComponentType, CComponent*>& component : m_mapComponent)
	{
		component.second->PhysicsUpdate();
	}
}

void CGameObject::GameObjectRender()
{
	Render();

	for (const pair<ComponentType, CComponent*>& component : m_mapComponent)
	{
		component.second->Render();
	}

}

void CGameObject::GameObjectRelease()
{
	for (const pair<ComponentType, CComponent*>& component : m_mapComponent)
	{
		component.second->Release();
		delete component.second;
	}
	m_mapComponent.clear();
	Release();
}

bool CGameObject::GetReserveDelete() const
{
	return m_bReserveDelete;
}

Layer CGameObject::GetLayer() const 
{
	return m_layer;
}

void CGameObject::SetLayer(Layer layer)
{
	m_layer = layer;
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


