#pragma once

class CScene;

class CCore : public SingleTon<CCore>
{
 public :
	void Init();
	void Release();

	void Update();
	void Render()	const;

	friend SingleTon<CCore>;
 private:
	CCore();
	virtual ~CCore();

};
#define CORE  CCore::GetInstance()



