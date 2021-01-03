#pragma once

template <typename T>
class Singleton
{
protected:
	//�̱��� �ν��Ͻ� ����
	static T* instance;

	Singleton() {}
	~Singleton() {}

public:
	//�̱��� ��������
	static T* GetSingleton();
	//�̱��� �޸𸮿��� �����ϱ�
	void ReleaseSingleton();
};

//�̱��� �ʱ�ȭ
// static ���� ������ {} ���� �ۿ��� �ʱ�ȭ�Ѵ�.
template <typename T>
T* Singleton<T>::instance = nullptr;

template<typename T>
inline T * Singleton<T>::GetSingleton()
{
	// �̱����� ������ ���� ��������
	if (!instance)
	{
		instance = new T;
	}

	return instance;
}

template<typename T>
inline void Singleton<T>::ReleaseSingleton()
{
	//�̱����� �ִٸ� �޸𸮿��� ��������
	if (instance)
	{
		delete instance;
		instance = 0;
	}
}