#include "framework.h"
#include "CComponent.h"

CComponent::CComponent():
    m_pOwner(nullptr),
    m_component(Component::GameObject)
{
}

CComponent::~CComponent()
{
}

CGameObject* CComponent::GetOwner()
{
    return m_pOwner;
}

Component CComponent::GetComponentType() const
{
    return m_component;
}

void CComponent::SetOwner(CGameObject* pOwner)
{
    m_pOwner = pOwner;
}
