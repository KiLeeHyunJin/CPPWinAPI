#pragma once
#include "CPPWinAPI.h"

class CGameObject;

class CComponent
{
public :
	CComponent();
	virtual ~CComponent();

	CGameObject* GetOwner();
	Component GetComponentType() const;
protected:
	Component m_component;

	friend CGameObject;
private:
	virtual void Init()		= 0;
	virtual void Release()	= 0;

	virtual void Update()	= 0;
	virtual void PhysicsUpdate() {};

	virtual void Render()	= 0;

	void SetOwner(CGameObject* pOwner);

	CGameObject* m_pOwner;
};

