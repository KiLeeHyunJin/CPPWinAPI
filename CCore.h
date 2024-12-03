#pragma once

class CCore : public SingleTon<CCore>
{
public :
	void Init();
	void Update();
	void Render() const;
	void Release();

	friend SingleTon<CCore>;
private:
	CCore();
	virtual ~CCore();

	HDC m_hdc;
	float m_fMoveX;
	float m_fMoveY;

};
#define CORE  CCore::GetInstance()



