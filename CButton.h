#pragma once
#include "CUI.h"


typedef void (*CallBackFunc)(DWORD_PTR param1, DWORD_PTR param2);

class CButton :
    public CUI
{
public :
    CButton();
    virtual ~CButton();

    void SetClickedCallBack(CallBackFunc pCallback, DWORD_PTR param1, DWORD_PTR param2);

protected:
    Color m_ColorRect;

    void Init()         override;
    void Release()      override;

    void Update()       override;
    void Render()       override;


    // CUI을(를) 통해 상속됨
    void OnMouseEnter()     final;
    void OnMouseExit()      final;

    void OnMouseOver()      final;
    void OnMouseClicked()   final;

    void OnMouseUp()        final;
    void OnMouseDown()      final;

    void AddChildUI(CUI* pChildUI) = delete;

    CallBackFunc m_pCallBack;
    DWORD_PTR m_pParam1;
    DWORD_PTR m_pParam2;
};

