#pragma once
#include "CGameObject.h"

class CImage;

class CTile :
    public CGameObject
{
public :
    CTile();
    virtual ~CTile();

    void SetPos(Vector pos) = delete;
    void SetPos(float x, float y) = delete;

    void SetTilePosX(UINT x);
    void SetTilePosY(UINT y);

    void SetTilePos(UINT x, UINT y);

    int GetTilePosX();
    int GetTilePosY();
    int GetTileIndex();
private:
    const static int TILESIZE = 32;

    CImage* m_pImg;
    UINT m_uiImgXCount;
    UINT m_uiImgYCount;

    UINT m_uiTilePosX;
    UINT m_uiTilePosY;
    UINT m_uiTileIndex;
};

