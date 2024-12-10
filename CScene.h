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
	//�ھ�� ȣ��  // ���ӿ�����Ʈ ȣ�� �� virtual �޼ҵ� ȣ��
	void SceneInit();
	void SceneRelease();

	void SceneUpdate();
	void SceneRender();

	void SceneEnter();
	void SceneExit();

	//�����ؼ� ���
	virtual void Init()		= 0;
	virtual void Release()	= 0;

	virtual void Update()	= 0;
	virtual void Render()	= 0;
	
	virtual void Enter()	= 0;
	virtual void Exit()		= 0;


	list<CGameObject*> m_listObj;
};

