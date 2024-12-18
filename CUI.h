#pragma once
#include "CGameObject.h"


class CUI :
    public CGameObject
{
public:
    CUI();
    virtual ~CUI();

    CUI* GetParentUI();
    void SetParentUI(CUI* pParentUI);

    void AddChildUI(CUI* pChildUI);
    void RemoveChildUI(CUI* pChildUI);

    bool GetScreenFixed();
    void SetScreenFixed(bool bFixedState);

protected:
    virtual void OnMouseEnter()     = 0;
    virtual void OnMouseExit()      = 0;

    virtual void OnMouseOver()      = 0;
    virtual void OnMouseClicked()   = 0;

    virtual void OnMouseUp()        = 0;
    virtual void OnMouseDown()      = 0;

    virtual void GameObjectInit()           override;
    virtual void GameObjectUpdate()         override;
    virtual void GameObjectRender()         override;
    virtual void GameObjectRelease()        override;

    list<CUI*>  m_listChildUI;
    CUI*        m_pParentUI;

    //Vector      m_vecParentPos;
    Vector      m_vecRenderPos;
    Vector      m_vecAbsolutePos;

    bool        m_bScreenFixed;

private:
    // CGameObject��(��) ���� ��ӵ�
    void Init() override;
    void Release() override;

    void Update() override;
    void Render() override;

};

