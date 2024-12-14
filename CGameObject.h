#pragma once
#include "Struct.h"
#include "CPPWinAPI.h"

class CScene;
class CEventManager;
class CComponent;
class CCollider;
class CCollisionManager;

class CGameObject
{
public:
	CGameObject();
	virtual ~CGameObject();

	Vector	GetPosition()	const;
	Vector	GetScale()		const;

	void	SetPosition	(Vector vecPos);
	void	SetScale	(Vector vecScale);

	void	SetPosition	(float x, float y);
	void	SetScale	(float x, float y);

	bool GetReserveDelete() const;

	Layer GetLayer() const;
	void SetLayer(Layer layer);

protected:
	void AddCollider(Vector scale, Vector offset);
	void RemoveCollider();
	CCollider* GetCollider();

	friend CScene;
	friend CCollider;
	friend CEventManager;
	friend CCollisionManager;
private:
	virtual void Init()		= 0;
	virtual void Release() = 0;

	virtual void Update()	= 0;
	virtual void Render()	= 0;

	virtual void OnCollision() {};

	void SetSafeToDelete();
	void SetReserveDelete(); 

	bool GetSafeToDelete() const;

	void AddComponent(CComponent* component);
	void RemoveComponent(CComponent* component);

	

	void GameObjectInit();
	void GameObjectUpdate();
	void GameObjectPhysicsUpdate();
	void GameObjectRender();
	void GameObjectRelease();

public:

protected:
	Vector	m_vecPos;
	Vector	m_vecScale;

	Layer	m_layer;

private:
	list<CComponent*> m_listComponent;

	CCollider* m_pCollider;


	bool m_bSafeToDelete;
	bool m_bReserveDelete;
};

