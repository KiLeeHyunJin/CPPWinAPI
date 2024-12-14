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
    void PhysicsUpdate();
    void CollisionUpdate(Layer leftLayer, Layer rightLayer);
    void Release();

    void CheckLayer(Layer left, Layer right);
    void UnCheckLayer(Layer left, Layer right);
    void ResetLayer();

    bool IsCollision(CCollider* pLeftCollider, CCollider* pRightCollider);
    
    bool m_arrLayer[(int)Layer::Size][(int)Layer::Size];
};
#define COLLISION CCollisionManager::GetInstance()

