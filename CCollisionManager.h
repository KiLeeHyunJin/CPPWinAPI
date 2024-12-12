#pragma once
#include "SingleTon.h"

class CCollisionManager :
    public SingleTon<CCollisionManager>
{
private:
    CCollisionManager();
    virtual ~CCollisionManager();


};

