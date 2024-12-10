#pragma once
#include "Struct.h"

class CScene;
class CEventManager;

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

protected:
	Vector m_vecPos;
	Vector m_vecScale;

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

	bool m_bSafeToDelete;
	bool m_bReserveDelete;
};

