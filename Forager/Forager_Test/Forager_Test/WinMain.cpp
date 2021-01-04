#include "pch.h"
#include "MainGame.h"

HINSTANCE	g_hInstance;		// 프로그램 인스턴스 핸들
HWND		g_hWnd;				// 윈도우 핸들
LPSTR		g_lpszClass = (LPSTR)TEXT("Forager");

MainGame*	g_mainGame = nullptr;
POINT		g_ptMouse;			// 전역 마우스 좌표

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

// 메인함수
int APIENTRY WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _lpszCmdParam, int nCmdShow)
{
	g_mainGame = new MainGame();

	// 윈도우를 생성하기 위한 기본셋팅
	g_hInstance = _hInstance;
	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;	// 클래스의 여분 메모리
	wndClass.cbWndExtra = 0;	// 윈도우의 여분 메모리
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = g_hInstance;
	wndClass.lpfnWndProc = WndProc;
	wndClass.lpszClassName = g_lpszClass;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	// 윈도우 클래스 등록
	RegisterClass(&wndClass);

	// 윈도우 생성
	g_hWnd = CreateWindow(g_lpszClass, g_lpszClass,
		WS_OVERLAPPEDWINDOW,
		50, 50, WINSIZE_X, WINSIZE_Y,
		NULL, NULL, g_hInstance, NULL);

	// 윈도우 출력
	ShowWindow(g_hWnd, nCmdShow);

	// 실제 작업 사이즈로 설정
	SetWindowSize(50, 50, WINSIZE_X, WINSIZE_Y);

	// mainGame이 초기화에 실패하면 종료
	if (FAILED(g_mainGame->Init()))
	{
		return 0;
	}

	// 메시지 큐에 있는 메시지 처리
	MSG message;
	while (true)
	{
		if (PeekMessage(&message, 0, 0, 0, PM_REMOVE))
		{
			if (message.message == WM_QUIT)	break;

			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
		{
			if (TimeManager::GetSingleton()->Update())
			{
				g_mainGame->Update();
				g_mainGame->Render();
			}
		}
	}

	g_mainGame->Release();
	delete g_mainGame;

	return message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	return g_mainGame->wndProc(hWnd, iMessage, wParam, lParam);
}
