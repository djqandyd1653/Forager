#pragma once
#include "GameNode.h"

class Image;

class MainGame : public GameNode
{
private:
	Image* backBuffer;
	HDC memDC;
	HDC hdc;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();

	LPARAM CALLBACK wndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
};

