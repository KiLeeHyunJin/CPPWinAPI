#include "framework.h"
#include "CResourceManager.h"
#include "CPathManager.h"
#include "CImage.h"
#include "CSound.h"

CResourceManager::CResourceManager()	{}

CResourceManager::~CResourceManager()	{}

CImage* CResourceManager::LoadImg(const wstring& key, const wstring& fileName)
{
	CImage* pImg = FindImg(key);
	if (pImg != nullptr)
	{
		return pImg;
	}

	wstring filePath = GETPATH + fileName;
	pImg = new CImage;
	pImg->Load(filePath);
	pImg->SetKey(key);
	pImg->SetPath(filePath);
	m_umapImg.insert(make_pair(key, pImg));
	return pImg;
}

CImage* CResourceManager::FindImg(const wstring& key)
{
	unordered_map<wstring, CImage*>::iterator iter = m_umapImg.find(key);
	if (m_umapImg.end() != iter)
	{
		return iter->second;
	}
	return nullptr;
}

CSound* CResourceManager::LoadSound(const wstring& key, const wstring& fileName)
{
	CSound* pSound = FindSound(key);
	if (pSound != nullptr)
	{
		return pSound;
	}

	wstring filePath = GETPATH + fileName;
	pSound = new CSound;
	pSound->Load(filePath);
	pSound->SetKey(key);
	pSound->SetPath(filePath);
	m_umapSound.insert(make_pair(key, pSound));
	return pSound;
}

CSound* CResourceManager::FindSound(const wstring& key)
{
	unordered_map<wstring, CSound*>::iterator iter = m_umapSound.find(key);
	if (m_umapSound.end() != iter)
	{
		return iter->second;
	}
	return nullptr;
}

void CResourceManager::Init()
{
}

void CResourceManager::Release()
{
	for (const pair<wstring, CImage*> pImgPair : m_umapImg)
	{
		delete pImgPair.second;
	}
	m_umapImg.clear();

	for (const pair<wstring, CSound*> pSoundPair : m_umapSound)
	{
		delete pSoundPair.second;
	}
	m_umapSound.clear();
}
