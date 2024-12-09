#pragma once
class CSceneManager;

class CScene
{
public:
	CScene();
	virtual ~CScene();

	friend CSceneManager;
private:
	virtual void Init()		= 0;
	virtual void Release()	= 0;

	virtual void Update()	= 0;
	virtual void Render()	= 0;
	
	virtual void Enter()	= 0;
	virtual void Exit()		= 0;

};

