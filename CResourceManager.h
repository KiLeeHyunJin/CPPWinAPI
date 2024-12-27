#pragma once
#include "SingleTon.h"

class CCore;
class CImage;
class CSound;

class CResourceManager :
    public SingleTon<CResourceManager>
{
public:
    CImage* LoadImg(const wstring& key, const wstring& fileName);
    CImage* FindImg(const wstring& key);

    CSound* LoadSound(const wstring& key, const wstring& fileName);
    CSound* FindSound(const wstring& key);

    friend CCore;
    friend SingleTon<CResourceManager>;
private:
    CResourceManager();
    virtual ~CResourceManager();    

    void Init();
    void Release();

    unordered_map<wstring, CImage*> m_umapImg;
    unordered_map<wstring, CSound*> m_umapSound;
};
#define RESOURCE CResourceManager::GetInstance()

