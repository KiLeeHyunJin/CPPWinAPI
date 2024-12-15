#pragma once
#include "CGameObject.h"

class CPlayer :
    public CGameObject
{
public:
    CPlayer();
    virtual ~CPlayer();


private:
    // CGameObject을(를) 통해 상속됨
    void Init()     override;
    void Release()  override;

    void Update()   override;
    void Render()   override;

    void OnCollisionStay(CCollider* pOtherCollision) override;

    Vector m_vecSize    = {10,10};
    float m_fSpeed      = 100;
};

