#pragma once
#include "SingleTon.h"
class CCore;

class CPathManager :
    public SingleTon<CPathManager>
{
public:
    const wstring& GetPath();

    friend CCore;
    friend SingleTon<CPathManager>;
private : 
    CPathManager();
    virtual ~CPathManager();

    void Init();
    void Release();


    wstring m_strPath;

};
#define PATH CPathManager::GetInstance()
#define GETPATH CPathManager::GetInstance()->GetPath()
