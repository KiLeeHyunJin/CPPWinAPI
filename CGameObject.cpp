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
	Component com = component->GetComponentType();
	map<Component, list<CComponent*>>::iterator iter = m_mapListComponent.find(com);
	if (iter == m_mapListComponent.end())
	{
		pair<Component, list<CComponent*>> newPair;
		newPair.first = com;
		newPair.second.push_back(component);
		m_mapListComponent.insert(newPair);
	}
	else
	{
		iter->second.push_back(component);
	}
	component->Init();
	component->SetOwner(this);
}

void CGameObject::RemoveComponent(CComponent* component)
{
	map<Component, list<CComponent*>>::iterator iter = m_mapListComponent.find(component->GetComponentType());
	if (iter == m_mapListComponent.end())
	{
		return;
	}
	iter->second.remove(component);
	component->Release();
	delete component;
}

void CGameObject::AddCollider(Vector scale, Vector offset)
{
	CCollider* m_pCollider = new CCollider();

	m_pCollider->SetScale(scale);
	m_pCollider->SetOffset(offset);

	AddComponent(m_pCollider);
}

void CGameObject::RemoveCollider()
{
	map<Component, list<CComponent*>>::iterator iter = m_mapListComponent.find(Component::Collider);
	if (iter != m_mapListComponent.end())
	{
		if (iter->second.size() > 0)
		{
			CComponent* component = iter->second.front();
			iter->second.pop_front();
			component->Release();
			delete component;
		}
	}
}

list<CCollider*>* CGameObject::GetCollider()
{
	map<Component, list<CComponent*>>::iterator iter = m_mapListComponent.find(Component::Collider);
	if (iter == m_mapListComponent.end())
	{
		return nullptr;
	}
	return reinterpret_cast<list<CCollider*>*>(&iter->second);
}

void CGameObject::GameObjectInit()
{
	for (pair<Component, list<CComponent*>> listComponent : m_mapListComponent)
	{
		for (CComponent* component : listComponent.second)
		{
			component->Init();
		}
	}
	Init();
}

void CGameObject::GameObjectUpdate()
{
	Update();

	for (pair<Component, list<CComponent*>> listComponent : m_mapListComponent)
	{
		for (CComponent* component : listComponent.second)
		{
			component->Update();
		}
	}
}

void CGameObject::GameObjectPhysicsUpdate()
{
	for (pair<Component, list<CComponent*>> listComponent : m_mapListComponent)
	{
		for (CComponent* component : listComponent.second)
		{
			component->PhysicsUpdate();
		}
	}
}

void CGameObject::GameObjectRender()
{
	Render();

	for (pair<Component, list<CComponent*>> listComponent : m_mapListComponent)
	{
		for (CComponent* component : listComponent.second)
		{
			component->Render();
		}
	}

}

void CGameObject::GameObjectRelease()
{
	for (pair<Component,list<CComponent*>> listComponent : m_mapListComponent)
	{
		for (CComponent* component : listComponent.second)
		{
			component->Release();
			delete component;
		}
		listComponent.second.clear();
	}
	m_mapListComponent.clear();
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


