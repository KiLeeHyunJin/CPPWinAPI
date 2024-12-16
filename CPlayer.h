#pragma once
#include "CGameObject.h"

class CImage;

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

    Vector m_vecSize    = {50,50};
    float m_fSpeed      = 100;

    CImage* pImg;
};

