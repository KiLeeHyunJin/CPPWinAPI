#pragma once

class CCore;

class CScene
{
	friend CCore;
public :
	CScene();
	virtual ~CScene();

	virtual void Init()		= 0;
	virtual void Release()	= 0;

	virtual void Update()	= 0;
	virtual void Render()	= 0;
	
	virtual void Enter()	= 0;
	virtual void Exit()		= 0;

private:

};

