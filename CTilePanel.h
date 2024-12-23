#pragma once
#include "CPanel.h"

class CImage;
class CTileButton;

class CTilePanel :
    public CPanel
{
public:
    CTilePanel();
    virtual ~CTilePanel();

private:

    void Init()     override;
    void Release()  override;
    void Render()   override;
    void Update()   override;

    void CreateTilePalette();
    void CreatepageButton();
    void SetPage(UINT page);
    void SetPrevPage();
    void SetNextPage();


    CImage* m_pImage;
    vector<CTileButton*> m_vecTileButton;
    
    UINT m_uiMenuHeight;
    UINT m_uiTilePage;
    
    UINT m_uiPaletteX;
    UINT m_uiPaletteY;

    UINT m_uiTileCountX;
    UINT m_uiTileCountY;


};

