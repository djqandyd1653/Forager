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

// �����Ҵ� ����
#define SAFE_RELEASE(p)			{if(p) { p->Release(); }}
#define SAFE_DELETE(p)			{if(p) {delete (p); (p) = NULL;}}
#define SAFE_DELETE_ARRAY(p)	{if(p) {delete[] (p); (p) = NULL;}}

// ���� ���� ��ȯ
#define DEGREE_TO_RADIAN(p)		p * 3.14f / 180.0f
#define RADIAN_TO_DEGREE(p)		p * 180.0f / 3.14f

extern HINSTANCE	g_hInstance;
extern HWND			g_hWnd;
extern POINT		g_ptMouse;
extern LOGFONT		font;
extern bool			changeMode;	// ���� ��尡 ���ߴ°�? (���� playscene�� �־����)
extern float		renderSize;

struct FPOINT
{
	float x;
	float y;
};

inline void SetWindowSize(int startX, int startY, int sizeX, int sizeY)
{
	// ������ �۾����� ����
	RECT rc;
	rc.left = 0;
	rc.top = 0;
	rc.right = sizeX;
	rc.bottom = sizeY;

	// ���� ������ ũ�� �޾ƿ���
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);

	// �̵�
	MoveWindow(g_hWnd, startX, startY, rc.right - rc.left, rc.bottom - rc.top, true);
}

template <typename T>
inline T Lerp(T a, T b, float t)
{
	return a + (b - a) * t;
}



