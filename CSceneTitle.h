#pragma once
#include "CScene.h"
class CSceneTitle : 
	public CScene
{
public :

private:
	// CScene��(��) ���� ��ӵ�
	void Init()		override;
	void Release()	override;
	void Update()	override;
	void Render()	override;
	void Enter()	override;
	void Exit()		override;
};

