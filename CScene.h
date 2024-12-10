#pragma once
class CSceneManager;
class CGameObject;

class CScene
{
public:
	CScene();
	virtual ~CScene();

	void AddGameObject(CGameObject* pObj);

	friend CSceneManager;
private:
	//코어에서 호출  // 게임오브젝트 호출 및 virtual 메소드 호출
	void SceneInit();
	void SceneRelease();

	void SceneUpdate();
	void SceneRender();

	void SceneEnter();
	void SceneExit();

	//수정해서 사용
	virtual void Init()		= 0;
	virtual void Release()	= 0;

	virtual void Update()	= 0;
	virtual void Render()	= 0;
	
	virtual void Enter()	= 0;
	virtual void Exit()		= 0;


	list<CGameObject*> m_listObj;
};

