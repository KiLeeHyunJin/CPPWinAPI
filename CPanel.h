#pragma once
#include "CUI.h"
class CPanel :
    public CUI
{
public:
    CPanel();
    virtual ~CPanel();

    bool GetDraggable();
    void SetDraggable(bool dragState);

protected:
    void Init()     override;
    void Release()  override;
    void Update()   override;
    void Render()   override;

    // CUI을(를) 통해 상속됨
    void OnMouseEnter()     final;
    void OnMouseExit()      final;
    
    void OnMouseOver()      final;
    void OnMouseClicked()   final;

    void OnMouseUp()        final;
    void OnMouseDown()      final;
    Color m_colorFill;
private:
    Vector  m_vecDragStartPos;
    bool    m_bDraggable;
    bool    m_bIsDragging;
};

