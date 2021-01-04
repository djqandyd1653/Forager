#include "TimeManager.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

//timeGetTime함수를 사용하기 위해서
//윈도우가 시작되고 난 후 시간을 리턴시켜준다
//GetTickCount보다 성능이 쪼오끔~ 더 좋다

HRESULT TimeManager::Init()
{
	//고성능 타이머 지원여부 체크
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&periodFrequency))
	{
		//고성능 타이머를 지원하니까
		isHardware = true;
		//초기화 시점의 시간을 마지막 시간으로
		QueryPerformanceCounter((LARGE_INTEGER*)&lastTime);
		//초당 시간 계산(1초 몇번 카운팅 하냐)
		timeScale = 1.0f / periodFrequency;
	}
	else
	{
		//고성능 타이머를 지원하지 않으니까
		isHardware = false;
		lastTime = timeGetTime();
		timeScale = 1.0f / 1000.0f;
	}

	//변수들 초기화
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
		//현재시간 얻기
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
	}
	else
	{
		//고성능 타이머를 지원하지 않기때문에 그냥 time함수 사용한다
		currTime = timeGetTime();
	}

	//한프레임 간격의 초 계산
	timeElapsed = (currTime - lastTime) * timeScale;

	if (targetFps == 0 || timeElapsed > 1.0f / targetFps)
	{
		fpsFrameCount++;
		//프레임 초 누적
		fpsTimeElapsed += timeElapsed;

		//프레임 초기화를 1초마다 진행하기
		if (fpsTimeElapsed >= 1.0f)
		{
			fps = fpsFrameCount;
			fpsFrameCount = 0;
			fpsTimeElapsed = 0.0f;
		}

		//지난 시간 갱신
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
