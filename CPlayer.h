#pragma once
#include "CGameObject.h"

class CImage;
class CAnimator;

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

    void OnCollisionEnter(CCollider* pOtherCollider)override;
    void OnCollisionStay(CCollider* pOtherCollider)	override;
    void OnCollisionExit(CCollider* pOtherCollider)	override;

    void AnimationUpdate();

    Vector  m_vecMoveDir;
    Vector  m_vecLookDir;
    bool    m_bIsMove;

    float   m_fSpeed;

    CImage* m_pImg;

    CImage* m_pIdleImg;
    CImage* m_pMoveImg;
    CAnimator* m_pAnim;
};

