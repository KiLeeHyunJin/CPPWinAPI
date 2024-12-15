#pragma once
#include "SingleTon.h"
#include "CPPWinAPI.h"

class CCore;
class CCollider;

class CCollisionManager :
    public SingleTon<CCollisionManager>
{
    friend CCore;
    friend SingleTon<CCollisionManager>;
private:
    CCollisionManager();
    virtual ~CCollisionManager();

    void Init();
    void Release();

    void PhysicsUpdate();
    void CollisionUpdate(Layer leftLayer, Layer rightLayer);

    void CheckLayer     (Layer left, Layer right);
    void UnCheckLayer   (Layer left, Layer right);
    void ResetLayer();

    bool IsCollisionList(list<CCollider*>* pLeftCollider, list<CCollider*>* pRightCollider, bool reserveDelete);
    bool IsCollision(CCollider* pLeftCollider, CCollider* pRightCollider);

    UINT64 CollisionID(UINT leftID, UINT rightID);
    
    bool m_arrLayer[(int)Layer::Size][(int)Layer::Size];        //충돌 레이어
    unordered_map<UINT64, bool> m_umapPrevCollision;              //충돌 상태
};
#define COLLISION CCollisionManager::GetInstance()

