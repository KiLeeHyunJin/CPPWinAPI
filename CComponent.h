#pragma once
class CComponent
{
public :
	CComponent();
	virtual ~CComponent();

private:
	virtual void Init()		= 0;
	virtual void Release()	= 0;

	virtual void Update()	= 0;
	virtual void Render()	= 0;
};

