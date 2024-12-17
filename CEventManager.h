#pragma once
#include "SingleTon.h"
#include "CPPWinAPI.h"

class CCore;
class CGameObject;

class CEventManager :
    public SingleTon<CEventManager>
{
public:
    void EventAddObject     (CGameObject* pGameObj);
    void EventDeleteObject  (CGameObject* pGameObj);
    void EventChangerScene  (GroupScene eScene, float delay = 0);

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
    void ProgressChangeScene();

    queue<CGameObject*> m_quequeAddObject;
    queue<CGameObject*> m_quequeDeleteObject;
    pair<GroupScene,float>*   m_pChangeScene;
};
#define EVENT                           CEventManager::GetInstance()
#define ADDOBJECT(pObj)                 CEventManager::GetInstance()->EventAddObject(pObj);
#define DELETEOBJECT(pObj)              CEventManager::GetInstance()->EventDeleteObject(pObj)
#define CHANGESCENE(scene)              CEventManager::GetInstance()->EventChangerScene(scene)
#define DELAYCHANGESCENE(scene, delay)  CEventManager::GetInstance()->EventChangerScene(scene, delay)