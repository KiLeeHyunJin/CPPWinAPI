#pragma once
#include "Struct.h"

class CScene;
class CEventManager;
class CComponent;
class CCollider;

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

	friend CScene;
	friend CEventManager;
private:
	virtual void Init()		= 0;
	virtual void Release() = 0;

	virtual void Update()	= 0;
	virtual void Render()	= 0;


	void SetSafeToDelete();
	void SetReserveDelete(); 

	bool GetSafeToDelete() const;

	void AddComponent(CComponent* component);
	void RemoveComponent(CComponent* component);

	void AddCollider(Vector scale, Vector offset);
	void RemoveCollider();
	CCollider* GetCollider();

	void GameObjectInit();
	void GameObjectUpdate();
	void GameObjectRender();
	void GameObjectRelease();

public:

protected:
	Vector m_vecPos;
	Vector m_vecScale;

private:
	list<CComponent*> m_listComponent;

	CCollider* m_pCollider;


	bool m_bSafeToDelete;
	bool m_bReserveDelete;
};

