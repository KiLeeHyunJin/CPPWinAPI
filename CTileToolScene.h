#pragma once
#include "CScene.h"



class CTileToolScene :
    public CScene
{
public:
    CTileToolScene();
    virtual ~CTileToolScene();

private:
    void Init()     override;
    void Release()  override;
    void Render()   override;
    void Update()   override;

    // CScene을(를) 통해 상속됨
    void Enter() override;
    void Exit() override;

    void SetTileIndex(UINT index);

    void CameraMove();

    void LoadTileData();
    void SaveTileData();
    void SaveTile(const wstring& strPath);

    UINT m_iTileSizeX;
    UINT m_iTileSizeY;
    float m_fScrollSpeed;

    HWND m_hWndTileTool;
};

