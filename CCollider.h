#pragma once
#include "CComponent.h"


class CGameObject;
class CCollisionManager;

class CCollider :
    public CComponent
{
public:
    CCollider();
    virtual ~CCollider();

    UINT GetID();
    const wstring* GetName();

    Vector GetPos();
    Vector GetOffset();
    Vector GetScale();

    friend CGameObject;
    friend CCollisionManager;
private:
    // CComponent을(를) 통해 상속됨
    void Init()             override;
    void Release()          override;
    void Update()           override;
    void PhysicsUpdate()    override;
    void Render()           override;

    void OnCollisionEnter(CCollider* pOtherCollider);
    void OnCollisionStay(CCollider* pOtherCollider) ;
    void OnCollisionExit(CCollider* pOtherCollider) ;

    void SetPos(Vector pos);
    void SetOffset(Vector offset);
    void SetScale(Vector scale);

    ColliderMatrix m_cmatrixTransform;

    UINT32    m_uiID;
    static UINT32 s_uiID;    

    UINT32 m_uiCollisionCount;

};

