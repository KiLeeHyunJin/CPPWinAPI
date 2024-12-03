#pragma once
template<typename T>
class SingleTon
{
public:
	static T* GetInstance() 
	{
		if (instance == nullptr)
		{
			instance = new T;
		}
		return instance;
	};

protected :
	static T* instance;

	SingleTon() {};
	virtual ~SingleTon() 
	{
		ReleaseInstance();
	};
	static void ReleaseInstance()
	{
		if (instance != nullptr)
		{
			delete(instance);
			instance = nullptr;
		}
	}
};

template<typename T>
T* SingleTon<T>::instance = nullptr;

