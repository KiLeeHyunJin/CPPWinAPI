#pragma once
#include "CTile.h"

class CCollider;

class CGroundTile :
    public CTile
{
public: 
    CGroundTile();
    virtual ~CGroundTile();

private:
    void Init() override;
    void Release() override;

    void Update() override;
    void Render() override;

    void OnCollisionEnter(CCollider* pOther) override;
    void OnCollisionExit(CCollider* pOther) override;
    void OnCollisionStay(CCollider* pOther) override;
};

