#pragma once
#include "Struct.h"
#include "CPPWinAPI.h"
#include "CComponent.h"

class CScene;
class CEventManager;
class CComponent;
class CCollider;
class CCollisionManager;
enum class ColliderType;



class CGameObject
{
public:
	CGameObject();
	virtual ~CGameObject();

	Vector	GetPosition();
	Vector	GetScale();

	void	SetPosition(Vector vecPos);
	void	SetScale(Vector vecScale);

	void	SetPosition(float x, float y);
	void	SetScale(float x, float y);

	Layer	GetLayer() const;
	void	SetLayer(Layer layer);

	const wstring& GetName();
	void			SetName(const wstring& name);

	bool GetReserveDelete() const;

protected:

	template<typename T>
	T GetComponent(ComponentType component);

	void AddCollider(ColliderType type, SHORT colliderId, Vector scale, Vector offset);
	void RemoveCollider();
	CCollider* GetCollider();

	void AddComponent(CComponent* component);

	virtual void GameObjectInit();
	virtual void GameObjectUpdate();
	virtual void GameObjectPhysicsUpdate();
	virtual void GameObjectRender();
	virtual void GameObjectRelease();


	friend CScene;
	friend CCollider;
	friend CEventManager;
	friend CCollisionManager;
private:
	virtual void Init()		= 0;
	virtual void Release() = 0;

	virtual void Update()	= 0;
	virtual void Render()	= 0;

	virtual void OnCollisionEnter(CCollider* pOtherCollider) {};
	virtual void OnCollisionStay(CCollider* pOtherCollider)	{};
	virtual void OnCollisionExit(CCollider* pOtherCollider)	{};


	void SetSafeToDelete();
	void SetReserveDelete(); 

	bool GetSafeToDelete();

	void RemoveComponent(CComponent* component);

	

public:

protected:
	Vector	m_vecPos;
	Vector	m_vecScale;

	Layer	m_layer;
	wstring m_strName;

private:
	map<ComponentType, CComponent*> m_mapComponent;


	bool m_bSafeToDelete;
	bool m_bReserveDelete;
};

template<typename T>
inline T CGameObject::GetComponent(ComponentType component)
{
	return T();
}
