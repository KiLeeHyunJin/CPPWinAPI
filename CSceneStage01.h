#pragma once
#include "CScene.h"

class CGameObject;

class CSceneStage01 :
    public CScene
{
public:
    
private:
    // CScene을(를) 통해 상속됨
    void Init()     override;
    void Release()  override;
    void Update()   override;
    void Render()   override;
    void Enter()    override;
    void Exit()     override;

};

