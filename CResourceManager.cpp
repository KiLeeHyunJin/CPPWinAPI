#include "framework.h"
#include "CResourceManager.h"
#include "CPathManager.h"
#include "CImage.h"

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

void CResourceManager::Init()
{
}

void CResourceManager::Release()
{
	for (const pair<wstring, CImage*> pImgPair : m_umapImg)
	{
		//pImgPair.second->Release();
		delete pImgPair.second;
	}
	m_umapImg.clear();
}
