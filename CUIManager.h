#pragma once
#include "SingleTon.h"

class CCore;
class CUI;

class CUIManager :
    public SingleTon<CUIManager>
{



    friend CCore;
    friend SingleTon<CUIManager>;
private:
    CUIManager();
    virtual ~CUIManager();

    void Init();
    void Release();

    void Update();

    void MouseEvent(CUI* pUI);

};
#define UI CUIManager::GetInstance()

