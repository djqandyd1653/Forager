#pragma once

#include "Windows.h"
#include <cstdlib>
#include <ctime>
#include <string>
#include <map>
#include <vector>
#include <cmath>
#include <list>

using namespace std;

#include "KeyManager.h"
#include "ImageManager.h"
#include "TimeManager.h"
#include "SceneManager.h"

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "msimg32.lib")

#define WINSIZE_X 1280
#define WINSIZE_Y 720

// 동적할당 해제
#define SAFE_RELEASE(p)			{if(p) { p->Release(); }}
#define SAFE_DELETE(p)			{if(p) {delete (p); (p) = NULL;}}
#define SAFE_DELETE_ARRAY(p)	{if(p) {delete[] (p); (p) = NULL;}}

// 각도 라디안 변환
#define DEGREE_TO_RADIAN(p)		p * 3.14f / 180.0f
#define RADIAN_TO_DEGREE(p)		p * 180.0f / 3.14f

extern HINSTANCE	g_hInstance;
extern HWND			g_hWnd;
extern POINT		g_ptMouse;
extern LOGFONT		font;
extern bool			changeMode;	// 게임 모드가 변했는가? (원래 playscene에 있어야함)
extern float		renderSize;

struct FPOINT
{
	float x;
	float y;
};

inline void SetWindowSize(int startX, int startY, int sizeX, int sizeY)
{
	// 윈도우 작업영역 지정
	RECT rc;
	rc.left = 0;
	rc.top = 0;
	rc.right = sizeX;
	rc.bottom = sizeY;

	// 실제 윈도우 크기 받아오기
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);

	// 이동
	MoveWindow(g_hWnd, startX, startY, rc.right - rc.left, rc.bottom - rc.top, true);
}

template <typename T>
inline T Lerp(T a, T b, float t)
{
	return a + (b - a) * t;
}



