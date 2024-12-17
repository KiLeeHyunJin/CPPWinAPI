#pragma once
#include "SingleTon.h"

class CCore;
class CGameObject;

class CCameraManager :
    public SingleTon<CCameraManager>
{
public :
    Vector          WorldToScreenPoint(Vector vecWorld);
    Vector          ScreenToWorldPoint(Vector vecScreen);

    CGameObject*    GetTargetObject();
    Vector          GetLookAt();
    Vector          GetTargetPos();
    float           GetScale();

    void            SetTargetPosition(Vector targetPos, float timeToTarget = 0);
    void            SetTargetObject(CGameObject* targetObject);
    void            Scroll(Vector dir, float velocity);
    void            SetScale(float scale);

    void FadeIn(float duration);
    void FadeOut(float duration);

    friend CCore;
    friend SingleTon<CCameraManager>;
private:
    CCameraManager();
    virtual ~CCameraManager();

    void Init();
    void Release();

    void Update();
    void Render();

    void RenderEffect();
    void MoveToTarget();
    
    CGameObject* m_pTarget;

    Vector          m_vecLookAt;
    Vector          m_vecTargetPos;
    
    float           m_fTimeToTarget;
    float           m_fScale;

    float           m_fTargetBright;
    float           m_fCurBright;
    float           m_fTimeToBright;
};
#define CAMERA CCameraManager::GetInstance()

