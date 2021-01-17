#pragma once
#include "pch.h"

enum class GAME_MODE;
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

public:
	HRESULT Init(GAME_MODE& currMode, int& modeNum);
	void Release();
	void Update(GAME_MODE& currMode, int& modeNum);
	void Render(HDC hdc, GAME_MODE& currMode);

	void SelectMenu(GAME_MODE & currMode, int & modeNum);

	MENU_BUTTON_INFO* GetMenuButton() { return button; }
};

