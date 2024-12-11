#include "framework.h"
#include "CComponent.h"

CComponent::CComponent():
    m_pOwner(nullptr)
{
}

CComponent::~CComponent()
{
}

CGameObject* CComponent::GetOwner()
{
    return m_pOwner;
}

void CComponent::SetOwner(CGameObject* pOwner)
{
    m_pOwner = pOwner;
}
