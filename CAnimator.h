#pragma once
#include "CComponent.h"

class CGameObject;
class CAnimation;
class CImage;

class CAnimator :
    public CComponent
{
public : 
    CAnimator();
    virtual ~CAnimator();

    void Play(const wstring& animKey, bool trigger = false);
    void Stop();

    void CreateAnimation(const wstring& animKey, CImage* pImg, 
        Vector leftTop, Vector slice, Vector step, float duration, UINT count, bool repeat = true);
    void RemoveAnimation(const wstring& animKey);

    CAnimation* FindAnimation(const wstring& animKey);

    friend CGameObject;
private:
    // CComponent을(를) 통해 상속됨
    void Init() override;
    void Release() override;

    void Update() override;
    void Render() override;


    map<wstring, CAnimation*> m_mapAnim;
    CAnimation* m_pCurAnim;

};

