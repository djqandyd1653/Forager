#pragma once

#include "Windows.h"
#include <string>
#include <map>
#include <vector>
#include <cmath>

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

extern HINSTANCE	g_hInstance;
extern HWND			g_hWnd;
extern POINT		g_ptMouse;

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