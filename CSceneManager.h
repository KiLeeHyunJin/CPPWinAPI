#pragma once
#include "SingleTon.h"

class CCore;

class CSceneManager : 
	public SingleTon<CSceneManager>
{
public :

	friend CCore;
	friend SingleTon<CSceneManager>;
private :
	CSceneManager();
	virtual ~CSceneManager();
};

