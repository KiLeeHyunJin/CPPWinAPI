#include "framework.h"
#include "CPathManager.h"

CPathManager::CPathManager()
{
}

CPathManager::~CPathManager()
{
}

void CPathManager::Init()
{
}

void CPathManager::Release()
{
}

const wstring& CPathManager::GetPath()
{
	WCHAR path[255] = {};
	GetCurrentDirectory(255, path);
	m_strPath = wstring(path);
	m_strPath += L"\\CPPWinAPI\\Resource\\";

	return m_strPath;
}
