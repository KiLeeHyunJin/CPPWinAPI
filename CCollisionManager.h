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

    bool IsCollisionTrigger (CCollider* const pLeftCollider, CCollider* const pRightCollider, const bool reserveDelete);
    bool IsCollisionCheck   (CCollider* const pLeftCollider, CCollider* const pRightCollider);
    bool RectCollision(const ColliderMatrix& const matLeft, const ColliderMatrix& const matRight, Vector& const vecLeftPos, Vector& const vecRightPos);
    bool CircleCollision(float leftRadius,float rightRadius, Vector& const vecLeftPos, Vector& const vecRightPos);
    bool RectCircleCollision(const ColliderMatrix& const matRect, float circleRadius, Vector& const vecRectPos, Vector& const vecCirclePos);

    UINT64 CollisionID(UINT leftID, UINT rightID);
    
    bool m_arrLayer[(int)Layer::Size][(int)Layer::Size];        //�浹 ���̾�
    unordered_map<UINT64, bool> m_umapPrevCollision;              //�浹 ����
};
#define COLLISION CCollisionManager::GetInstance()

