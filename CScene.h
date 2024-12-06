#pragma once
class CScene
{
public :
	CScene();
	virtual ~CScene();

	void Init();
	void Release();

	void Update();
	void Render();
	
	void Enter();
	void Exit();
};

