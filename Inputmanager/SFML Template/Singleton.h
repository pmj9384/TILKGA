#pragma once

template <typename T>
class Singleton
{
protected:
	Singleton() = default;
	virtual ~Singleton() = default;
	
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;

public:

	static T& Instance()
	{
		static T Instance; //스태틱 지역변수:처음 만났을때 생성되고 계속 유지됨
		return Instance;
	}
	
};

