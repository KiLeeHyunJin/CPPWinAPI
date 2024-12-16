#include "framework.h"
#include "CResource.h"

CResource::CResource():
	m_strKey(L""),
	m_strPath(L"")
{

}

CResource::~CResource()
{
}

void CResource::SetKey(const wstring& key)
{
	m_strKey = key;
}

void CResource::SetPath(const wstring& path)
{
	m_strPath;
}

const wstring& CResource::GetKey()
{
	return m_strKey;
}

const wstring& CResource::GetPath()
{
	return m_strPath;
}
