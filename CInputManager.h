#pragma once
class CCore;

class CInputManager : 
	public SingleTon<CInputManager>
{
public :
	bool GetButton		(const int keyId) const;
	bool GetButtonDown	(const int keyId) const;
	bool GetButtonUp	(const int keyId) const;
	Vector GetMouseScreenPosition() const;
	Vector GetMouseWorldPosition() const;

	friend CCore;
	friend SingleTon<CInputManager>;
private :
	CInputManager();
	virtual ~CInputManager();

	void Init();
	void Release();

	void Update();

	void FocusOn();
	void FocusOff();

	static const int VKEY_SIZE = 255;
	bool m_arrCurKey[VKEY_SIZE];
	bool m_arrPrevKey[VKEY_SIZE];
	Vector m_vecMousePos;
};
#define INPUT				CInputManager::GetInstance()
#define BUTTONSTAY(key)		CInputManager::GetInstance()->GetButton(key)
#define BUTTONDOWN(key)		CInputManager::GetInstance()->GetButtonDown(key)
#define BUTTONUP(key)		CInputManager::GetInstance()->GetButtonUp(key)
#define MOUSESCREENPOSITION CInputManager::GetInstance()->GetMouseScreenPosition()
#define MOUSEWORLDPOSITION	CInputManager::GetInstance()->GetMouseWorldPosition()
