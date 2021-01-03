#pragma once
#include "pch.h"
#include "Singleton.h"

class TimeManager : public Singleton<TimeManager>
{
private:
	bool isHardware;				// 고성능 타이머를 지원하냐?
	float timeScale;				// 경과 진동수를 초당 진동수로 나눠서 시간단위로 변환
	float timeElapsed;				// 이전 시간과 현재 시간의 경과량
	__int64 currTime;				// 현재 시간 (고성능 타이머 값)
	__int64 lastTime;				// 이전 시간 (고성능 타이머 값)
	__int64 periodFrequency;		// 시간주기 (1초에 몇번이나 카운트되는지)

	float fpsTimeElapsed;			// 프레임 경과 확인 (1초 확인)
	unsigned long fps;				// FPS
	unsigned long fpsFrameCount;	// FPS 카운트

public:
	HRESULT Init();
	void Update();
	void Render(HDC hdc);

	//한프레임당 경과시간 가져오기
	float GetElapsedTime();
};

