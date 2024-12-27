#pragma once
#include "CResource.h"
class CSound :
    public CResource
{
public : 
    CSound();
    virtual ~CSound();

    void Play(bool loop = false, float volume = 1.0f);
    void Stop();
    void Pause();
    void Resume();

    bool GetLoop();
    void SetLoop(bool loop);

    float GetVolume();
    void SetVolume(float volume);

    void Load(const wstring& soundName);
    bool IsPlaying();
    bool IsPaused();
private:
    bool m_bLoop;
    float m_fVolume;

    FMOD::Sound* m_pSound;
    FMOD::Channel* m_pChannel;


};

