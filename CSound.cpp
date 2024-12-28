#include "framework.h"
#include "CSound.h"
#include "CSoundManager.h"

CSound::CSound() :
	m_fVolume(1), m_bLoop(false),
	m_pChannel(nullptr), m_pSound(nullptr)
{	}

CSound::~CSound()
{
	//Stop();
	if (m_pSound != nullptr)
	{
		m_pSound->release();
	}
}

//void CSound::Play(bool loop, float volume)
//{
//}
//
//void CSound::Stop()
//{
//	assert(m_pChannel);
//	m_pChannel->stop();
//
//}
//
//void CSound::Pause()
//{
//	assert(m_pChannel);
//	m_pChannel->setPaused(true);
//}
//
//void CSound::Resume()
//{
//	assert(m_pChannel);
//	m_pChannel->setPaused(false);
//}

bool CSound::GetLoop()
{
	return false;
}

float CSound::GetVolume()
{
	return 0.0f;
}

void CSound::SetLoop(bool loop)
{
	m_bLoop = loop;
	if (loop)
	{
		m_pSound->setMode(FMOD_LOOP_NORMAL);
	}
	else
	{
		m_pSound->setMode(FMOD_LOOP_OFF);
	}
}

void CSound::SetVolume(float volume)
{
	m_fVolume = volume;
	assert(m_pChannel);
	m_pChannel->setVolume(m_fVolume);
}

FMOD::Sound* CSound::GetSound()
{
	return m_pSound;
}

FMOD::Channel** CSound::GetChannel()
{
	return &m_pChannel;
}

bool CSound::IsPlaying()
{
	bool playing;
	assert(m_pChannel);
	m_pChannel->isPlaying(&playing);
	return false;
}

bool CSound::IsPaused()
{
	bool paused;
	assert(m_pChannel);
	m_pChannel->getPaused(&paused);
	return false;
}


void CSound::Load(const wstring& soundName)
{
	char str[255];
	wcstombs_s(nullptr, str, soundName.c_str(), 255);
	SOUND->GetSystem()->createSound(str, FMOD_LOOP_OFF, nullptr, &m_pSound);
}

void CSound::SetChannel(FMOD::Channel* pChannel)
{
	m_pChannel = pChannel;
}

