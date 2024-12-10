#pragma once
#include "SingleTon.h"

class CCore;
class CGameObject;

class CEventManager :
    public SingleTon<CEventManager>
{
public:
    void EventAddObject     (CGameObject* pGameObj);
    void EventDeleteObject  (CGameObject* pGameObj);

    friend CCore;
    friend SingleTon<CEventManager>;
private:
    CEventManager();
    virtual ~CEventManager();

    void Init();
    void Release();

    void Update();

    void ProgressAddObject();
    void ProgressDeleteObject();

    queue<CGameObject*> m_quequeAddObject;
    queue<CGameObject*> m_quequeDeleteObject;
};
#define EVENT           CEventManager::GetInstance()
#define ADDOBJECT(pObj) CEventManager::GetInstance()->EventAddObject(pObj);
#define DELETEOBJECT(pObj) CEventManager::GetInstance()->EventDeleteObject(pObj)
