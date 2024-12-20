#pragma once
class CCore;
enum class ClickState		{ Down, Up, Stay };
enum class MouseState		{ Left, Right };

class CInputManager : 
	public SingleTon<CInputManager>
{
public :
	bool GetButton		(const int keyId) const;
	bool GetButtonDown	(const int keyId) const;
	bool GetButtonUp	(const int keyId) const;

	bool GetLMouseUp(bool ignoreUI);
	bool GetLMouseDown(bool ignoreUI);
	bool GetLMouseStay(bool ignoreUI);
	bool GetRMouseUp(bool ignoreUI);
	bool GetRMouseDown(bool ignoreUI);
	bool GetRMouseStay(bool ignoreUI);
	bool GetMouse(MouseState mouse, ClickState click, bool ignoreUI);

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
	bool GetMouseOnUI();

	static const int VKEY_SIZE = 255;
	bool m_arrCurKey[VKEY_SIZE];
	bool m_arrPrevKey[VKEY_SIZE];

	bool (*MouseFunc[3])(const int keyId);
	int m_arrMouseID[2] = {VK_LBUTTON, VK_RBUTTON};
	Vector m_vecMousePos;
};
#define INPUT				CInputManager::GetInstance()
#define BUTTONSTAY(key)		CInputManager::GetInstance()->GetButton(key)
#define BUTTONDOWN(key)		CInputManager::GetInstance()->GetButtonDown(key)
#define BUTTONUP(key)		CInputManager::GetInstance()->GetButtonUp(key)
#define MOUSESCREENPOSITION CInputManager::GetInstance()->GetMouseScreenPosition()
#define MOUSEWORLDPOSITION	CInputManager::GetInstance()->GetMouseWorldPosition()

#define LMOUSESTAY(ignoreUI)CInputManager::GetInstance()->GetMouse(MouseState::Left,	ClickState::Stay,	ignoreUI)
#define LMOUSEUP(ignoreUI)	CInputManager::GetInstance()->GetMouse(MouseState::Left,	ClickState::Up,		ignoreUI)
#define LMOUSEDOWN(ignoreUI)CInputManager::GetInstance()->GetMouse(MouseState::Left,	ClickState::Down,	ignoreUI)
#define RMOUSESTAY(ignoreUI)CInputManager::GetInstance()->GetMouse(MouseState::Right,	ClickState::Stay,	ignoreUI)
#define RMOUSEUP(ignoreUI)	CInputManager::GetInstance()->GetMouse(MouseState::Right,	ClickState::Up,		ignoreUI)
#define RMOUSEDOWN(ignoreUI)CInputManager::GetInstance()->GetMouse(MouseState::Right,	ClickState::Down,	ignoreUI)