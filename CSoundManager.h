#pragma once
#include "SingleTon.h"
class CCore;
class CSound;

class CSoundManager :
    public SingleTon<CSoundManager>
{
public:
    FMOD::System* GetSystem();
    void Play(CSound* pSound, bool loop = false, float volume = 1.f);
    void Stop(CSound* pSound);
    void Pause(CSound* pSound);
    void Resume(CSound* pSound);

    friend CCore;
    friend SingleTon<CSoundManager>;
private:
    CSoundManager();
    virtual ~CSoundManager();

    void Init();
    void Release();

    void Update();

    FMOD::System* m_pSystem;

};
#define SOUND CSoundManager::GetInstance()

