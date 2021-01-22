#pragma once
#include "pch.h"

enum class GAME_MODE
{
	PLAY,
	INVENTORY,
	BUILD,
	LAND_PURCHASSE,
	SETTING
};

class Image;

typedef struct tagButton
{
	Image* img;
	POINT pos;
	POINT imgPos;
	RECT rc;

}MENU_BUTTON_INFO;

class Menu
{
private:
	Image* background;
	Image* menuList;
	Image* currModeImg;

	MENU_BUTTON_INFO button[7];

	GAME_MODE currMode;		// 현재 게임 모드
	GAME_MODE lastMode;		// 이전 게임 모드

public:
	HRESULT Init();
	void Release();
	void Update(bool & selectBuild);
	void Render(HDC hdc);

	void SelectMenu(bool & selectBuild);

	MENU_BUTTON_INFO* GetMenuButton() { return button; }

	GAME_MODE GetCurrMode() { return currMode; }
	GAME_MODE GetLastMode() { return lastMode; }
	void SetCurrMode(GAME_MODE mode) { currMode = mode; }
	void SetLastMode() { lastMode = currMode; }
};

