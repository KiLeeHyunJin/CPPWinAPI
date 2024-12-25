#pragma once
#include "CGameObject.h"

class CImage;
class CScene;
class CGroundTile;

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
    void SetTileIndex(UINT index);
    int GetTilePosX();
    int GetTilePosY();
    int GetTileIndex();

    bool GetLineRender();

    virtual void Load(FILE* pFile);
    virtual void Save(FILE* pFile);

    const static int TILESIZE = 32;

protected:

    TileType m_tileType;

    CImage* m_pImg;
    UINT m_uiImgXCount;
    UINT m_uiImgYCount;

    UINT m_uiTilePosX;
    UINT m_uiTilePosY;
    UINT m_uiTileIndex;

    bool m_bLineRender;

    friend CScene;
    friend CGroundTile;
private:
    // CGameObject을(를) 통해 상속됨
    void Init() override;

    void Release() override;

    void Update() override;

    void Render() override;


    



};

