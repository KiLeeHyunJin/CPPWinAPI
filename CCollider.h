#pragma once
#include "CComponent.h"
#include "Struct.h"

class CGameObject;
class CCollisionManager;


enum class ColliderType
{    Rect, Circle,   };

class CCollider :
    public CComponent
{
public:
    CCollider();
    virtual ~CCollider();

    UINT GetID();
    const wstring& GetName();

    Vector GetPos();
    Vector GetOffset(SHORT offsetId);
    Vector GetScale(SHORT scaleId);

    RectSize GetBaseSize();
    ColliderType GetType(SHORT colliderId);

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

    void SetCollider(ColliderType type, SHORT colliderId,Vector offset, Vector scale);

    void SetPos(Vector pos);
    //void SetType(ColliderType type);

    map<SHORT, ColliderMatrix> m_mapColliderTransform;

    Vector m_vecPos;
    RectSize m_sizeBase;

    UINT32    m_uiID;
    static UINT32 s_uiID;    

    UINT32 m_uiCollisionCount;

};

