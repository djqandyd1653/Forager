#include "TimeManager.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

//timeGetTime�Լ��� ����ϱ� ���ؼ�
//�����찡 ���۵ǰ� �� �� �ð��� ���Ͻ����ش�
//GetTickCount���� ������ �ɿ���~ �� ����

HRESULT TimeManager::Init()
{
	//���� Ÿ�̸� �������� üũ
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&periodFrequency))
	{
		//���� Ÿ�̸Ӹ� �����ϴϱ�
		isHardware = true;
		//�ʱ�ȭ ������ �ð��� ������ �ð�����
		QueryPerformanceCounter((LARGE_INTEGER*)&lastTime);
		//�ʴ� �ð� ���(1�� ��� ī���� �ϳ�)
		timeScale = 1.0f / periodFrequency;
	}
	else
	{
		//���� Ÿ�̸Ӹ� �������� �����ϱ�
		isHardware = false;
		lastTime = timeGetTime();
		timeScale = 1.0f / 1000.0f;
	}

	//������ �ʱ�ȭ
	fps = 0;
	currTime = 0;
	fpsFrameCount = 0;
	fpsTimeElapsed = 0.0f;
	targetFps = 120.0f;

	return S_OK;
}

bool TimeManager::Update()
{
	if (isHardware)
	{
		//����ð� ���
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
	}
	else
	{
		//���� Ÿ�̸Ӹ� �������� �ʱ⶧���� �׳� time�Լ� ����Ѵ�
		currTime = timeGetTime();
	}

	//�������� ������ �� ���
	timeElapsed = (currTime - lastTime) * timeScale;

	if (targetFps == 0 || timeElapsed > 1.0f / targetFps)
	{
		fpsFrameCount++;
		//������ �� ����
		fpsTimeElapsed += timeElapsed;

		//������ �ʱ�ȭ�� 1�ʸ��� �����ϱ�
		if (fpsTimeElapsed >= 1.0f)
		{
			fps = fpsFrameCount;
			fpsFrameCount = 0;
			fpsTimeElapsed = 0.0f;
		}

		//���� �ð� ����
		lastTime = currTime;
		return true;
	}
	return false;
}

void TimeManager::Render(HDC hdc)
{
	char str[512];
	sprintf_s(str, "FPS : %d", fps);
	TextOut(hdc, 10, 10, str, int(strlen(str)));
}

float TimeManager::GetElapsedTime()
{
	return max(timeElapsed, 0.002f);
}
