#pragma once
#include "Struct.h"

class CScene;

class CGameObject
{
public:
	CGameObject();
	virtual ~CGameObject();

	Vector	GetPosition() const;
	void	SetPosition(Vector pos);
	void	SetPosition(float x, float y);

	Vector	GetScale() const;
	void	SetScale(Vector scale);
	void	SetScale(float x, float y);

protected:
	Vector m_vecPos;
	Vector m_vecScale;

	friend CScene;
public:
	virtual void Init()		= 0;
	virtual void Release() = 0;

	virtual void Update()	= 0;
	virtual void Render()	= 0;

};

