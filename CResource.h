#pragma once
class CResource
{
public :
	CResource();
	virtual ~CResource();

	void SetKey(const wstring& key);
	void SetPath(const wstring& path);

	const wstring& GetKey();
	const wstring& GetPath();

protected:
	wstring m_strPath;
	wstring m_strKey;
};

