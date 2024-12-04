#pragma once
class CCore;

class CInputManager : public SingleTon<CInputManager>
{
public :
	bool GetButton(const int keyId);
	bool GetButtonDown(const int keyId);
	bool GetButtonUp(const int keyId);
	POINT GetMousePos();


	friend CCore;
	friend SingleTon<CInputManager>;
private :
	CInputManager();
	virtual ~CInputManager();

	void Init();
	void Release();

	void Update();

};

