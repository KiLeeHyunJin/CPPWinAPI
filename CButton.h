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


    // CUI��(��) ���� ��ӵ�
    void OnMouseEnter()     final;
    void OnMouseExit()      final;

    void OnMouseOver()      final;
    void OnMouseClicked()   final;

    void OnMouseUp()        final;
    void OnMouseDown()      final;

    void AddChildUI(CUI* pChildUI) = delete;
};

