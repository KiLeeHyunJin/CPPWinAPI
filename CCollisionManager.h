#pragma once
#include "SingleTon.h"
#include "CPPWinAPI.h"

class CCore;

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
    void Release();

    void CheckLayer(Layer left, Layer right);
    void UnCheckLayer(Layer left, Layer right);
    void ResetLayer();

    bool m_arrLayer[(int)Layer::Size][(int)Layer::Size];
};
#define COLLISION CCollisionManager::GetInstance()

