#pragma once

template <typename T>
class SingleTon
{
protected:
	SingleTon() {};
	virtual ~SingleTon() {};

public:
	static T* GetInstance()
	{
		static T instance;
		return &instance;
	}
};

#define SINGLE(A)	A::GetInstance()




