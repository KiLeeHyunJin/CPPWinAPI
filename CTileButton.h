#pragma once
#include "CButton.h"
class CImage;

class CTileButton :
    public CButton
{
public:
    CTileButton();
    virtual ~CTileButton();

    CImage* GetImage();
    void SetImage(CImage* pimg);
    UINT GetTileIndex();
    void SetTileIndex(UINT index);

private:
    CImage* m_pImage;
    UINT m_uiTileIndex;
    int m_iImgHeight;
    int m_iImgWidth;
    int m_iCountX;
    int m_iCountY;
    int m_iTileX;
    int m_iTileY;

};

