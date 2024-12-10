#pragma once
#include "CGameObject.h"

class CPlayer;

class CMonster :
    public CGameObject
{
public:
    CMonster();
    virtual ~CMonster();

    void SetTarget(CPlayer* pTargetPlayer);

private:
    // CGameObject��(��) ���� ��ӵ�
    void Init()         override;
    void Release()      override;
    void Update()       override;
    void Render()       override;

    void Trace();


    CPlayer*    m_pTarget;
    Vector      m_vecDirection;
};

