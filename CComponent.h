#pragma once
#include "CPPWinAPI.h"

enum class ComponentType
{
	GameObject,
	Collider,
	Animator,

	Size
};

class CGameObject;

class CComponent
{
public :
	CComponent();
	virtual ~CComponent();

	CGameObject* GetOwner();
	ComponentType GetComponentType() const;
protected:
	ComponentType m_component;

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

