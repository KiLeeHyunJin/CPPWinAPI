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
    void OnMouseEnter() override;
    void OnMouseExit()  override;

    void OnMouseOver()  override;
    void OnMouseClicked() override;

    void OnMouseUp()    override;
    void OnMouseDown()  override;

};

