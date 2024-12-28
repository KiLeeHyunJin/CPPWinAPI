#include "framework.h"
#include "CSoundManager.h"
#include "CSound.h"

CSoundManager::CSoundManager()
	:m_pSystem(nullptr)
{
}

CSoundManager::~CSoundManager()
{
}

void CSoundManager::Init()
{
	FMOD::System_Create(&m_pSystem);
	assert(m_pSystem);
	m_pSystem->init(32, FMOD_INIT_NORMAL, nullptr);
}

void CSoundManager::Release()
{
	m_pSystem->release();
	m_pSystem->close();
}

void CSoundManager::Update()
{
	m_pSystem->update();
}

FMOD::System* CSoundManager::GetSystem()
{
	return m_pSystem;
}

void CSoundManager::Play(CSound* pSound, bool loop, float volume)
{
	m_pSystem->playSound(pSound->GetSound(), nullptr, false, pSound->GetChannel());
	pSound->SetVolume(volume);
	pSound->SetLoop(loop);
}

void CSoundManager::Stop(CSound* pSound)
{
}

void CSoundManager::Pause(CSound* pSound)
{
}

void CSoundManager::Resume(CSound* pSound)
{
}
