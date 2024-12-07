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

	CScene* m_pCurScene;
	CScene* m_pSceneTitle;
	CScene* m_pSceneStage01;

};
#define CORE  CCore::GetInstance()



