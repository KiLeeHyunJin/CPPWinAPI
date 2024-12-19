#pragma once

class CAnimator;
class CImage;

class CAnimation
{
public : 
	CAnimation();
	virtual ~CAnimation();
	const wstring& GetKey();

	friend CAnimator;
private:
	void Init();
	void Release();

	void Render();
	void Update();

	void SetKey(const wstring& strKey);
	void Create(CImage* pImg, Vector leftTop, Vector slice, Vector step, float duration, UINT count, bool repeat);
	void Replay();

	CAnimator*	m_pAnimator;
	wstring		m_strKey;
	CImage*		m_pImg;
	UINT		m_uiCurFrame;

	vector<Vector> m_vecAnimFrame;
	Vector		m_vecSliceScale;
	float		m_fduration;

	float		m_fAccTime;
	bool		m_bRepeat;
};

