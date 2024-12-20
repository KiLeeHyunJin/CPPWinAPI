#pragma once
#include "SingleTon.h"

class CCore;
class CUI;
class CInputManager;

class CUIManager :
    public SingleTon<CUIManager>
{

    bool GetMouseOnUI();


    friend CCore;
    friend SingleTon<CUIManager>;
    friend CInputManager;
private:
    CUIManager();
    virtual ~CUIManager();

    void Init();
    void Release();

    void Update();

    void MouseEvent(CUI* pUI, CUI* pTopChildUI);
    void SetFocusedUI(CUI* pUI);
    CUI* GetFocusedUI();

    CUI* GetTopUI();
    CUI* GetTopChildUI(CUI* pUI);

    CUI* m_pFocusedUI;
    bool m_bMouseOnUI;

};
#define UI CUIManager::GetInstance()

