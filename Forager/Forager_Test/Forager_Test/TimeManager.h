#pragma once
#include "pch.h"
#include "Singleton.h"

class TimeManager : public Singleton<TimeManager>
{
private:
	bool isHardware;				// ���� Ÿ�̸Ӹ� �����ϳ�?
	float timeScale;				// ��� �������� �ʴ� �������� ������ �ð������� ��ȯ
	float timeElapsed;				// ���� �ð��� ���� �ð��� �����
	__int64 currTime;				// ���� �ð� (���� Ÿ�̸� ��)
	__int64 lastTime;				// ���� �ð� (���� Ÿ�̸� ��)
	__int64 periodFrequency;		// �ð��ֱ� (1�ʿ� ����̳� ī��Ʈ�Ǵ���)

	float fpsTimeElapsed;			// ������ ��� Ȯ�� (1�� Ȯ��)
	unsigned long fps;				// FPS
	unsigned long fpsFrameCount;	// FPS ī��Ʈ

public:
	HRESULT Init();
	void Update();
	void Render(HDC hdc);

	//�������Ӵ� ����ð� ��������
	float GetElapsedTime();
};

