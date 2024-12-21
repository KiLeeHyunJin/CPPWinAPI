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

    // CScene��(��) ���� ��ӵ�
    void Enter() override;
    void Exit() override;
};

