#pragma once
template<typename T>
class SingleTon
{
public:
	static T* GetInstance() 
	{
		static T instance;
		return &instance;
	};

protected :
	static T* instance;

	SingleTon()				{ };
	virtual ~SingleTon()	{ };
};

