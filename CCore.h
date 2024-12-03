#pragma once

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

	float m_fMoveX;
	float m_fMoveY;



};
#define CORE  CCore::GetInstance()



