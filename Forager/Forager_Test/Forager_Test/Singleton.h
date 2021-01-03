#pragma once

template <typename T>
class Singleton
{
protected:
	//싱글톤 인스턴스 선언
	static T* instance;

	Singleton() {}
	~Singleton() {}

public:
	//싱글톤 가져오기
	static T* GetSingleton();
	//싱글톤 메모리에서 해제하기
	void ReleaseSingleton();
};

//싱글톤 초기화
// static 변수 문법상 {} 영역 밖에서 초기화한다.
template <typename T>
T* Singleton<T>::instance = nullptr;

template<typename T>
inline T * Singleton<T>::GetSingleton()
{
	// 싱글톤이 없으면 새로 생성하자
	if (!instance)
	{
		instance = new T;
	}

	return instance;
}

template<typename T>
inline void Singleton<T>::ReleaseSingleton()
{
	//싱글톤이 있다면 메모리에서 해제하자
	if (instance)
	{
		delete instance;
		instance = 0;
	}
}