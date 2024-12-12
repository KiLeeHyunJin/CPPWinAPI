#pragma once
#include "CComponent.h"
class CGameObject;

class CCollider :
    public CComponent
{
public:
    CCollider();
    virtual ~CCollider();

    Vector GetPos();
    Vector GetOffset();
    Vector GetScale();

    friend CGameObject;
private:
    // CComponent을(를) 통해 상속됨
    void Init()             override;
    void Release()          override;
    void Update()           override;
    void PhysicsUpdate()    override;
    void Render()           override;

    void OnCollision(CCollider* pOtherCollider);

    void SetPos(Vector pos);
    void SetOffset(Vector offset);
    void SetScale(Vector scale);


    Vector m_vecPos;
    Vector m_vecScale;
    Vector m_vecOffset;

};

