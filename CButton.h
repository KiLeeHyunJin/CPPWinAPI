#pragma once
#include "CUI.h"


class CButton :
    public CUI
{
public :
    CButton();
    virtual ~CButton();

protected:
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
};

