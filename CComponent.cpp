#include "framework.h"
#include "CComponent.h"

CComponent::CComponent():
    m_pOwner(nullptr),
    m_component(ComponentType::GameObject)
{
}

CComponent::~CComponent()
{
}

CGameObject* CComponent::GetOwner()
{
    return m_pOwner;
}

ComponentType CComponent::GetComponentType() const
{
    return m_component;
}

void CComponent::SetOwner(CGameObject* pOwner)
{
    m_pOwner = pOwner;
}
