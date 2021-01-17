#include "Menu.h"
#include "PlayScene.h"
#include "Image.h"

HRESULT Menu::Init(GAME_MODE & currMode, int & modeNum)
{
	currMode = GAME_MODE::PLAY;
	modeNum = 0;
	background = ImageManager::GetSingleton()->FindImage("Inventory_Back");
	menuList = ImageManager::GetSingleton()->FindImage("Menu_List_Icon");

	button[0].img = ImageManager::GetSingleton()->FindImage("Equip_Icon");
	button[1].img = ImageManager::GetSingleton()->FindImage("Item_Icon");
	button[2].img = ImageManager::GetSingleton()->FindImage("Construction_Icon");
	button[3].img = ImageManager::GetSingleton()->FindImage("Purchase_Land_Icon");
	button[4].img = ImageManager::GetSingleton()->FindImage("Setting_Icon");
	button[5].img = ImageManager::GetSingleton()->FindImage("E_Button");
	button[6].img = ImageManager::GetSingleton()->FindImage("Q_Button");

	for (int i = 0; i < 7; i++)
	{
		if (i < 5)
			button[i].pos = { 410 + 92 * i, 20 };
		else if (i < 6)
		{
			button[i].pos = { 890, 55 };
			continue;
		}
		else if (i < 7)
		{
			button[i].pos = { 330, 55 };
			continue;
		}

		button[i].rc.left = button[i].pos.x;
		button[i].rc.top = button[i].pos.y;
		button[i].rc.right = button[i].pos.x + 92;
		button[i].rc.bottom = button[i].pos.y + 92;
	}
	
	button[0].imgPos = { button[0].pos.x + 5, button[0].pos.y + 10 };
	button[1].imgPos = { button[1].pos.x + 7, button[1].pos.y + 10};
	button[2].imgPos = { button[2].pos.x + 9, button[2].pos.y + 10};
	button[3].imgPos = { button[3].pos.x - 7, button[3].pos.y + 10};
	button[4].imgPos = { button[4].pos.x + 13, button[4].pos.y + 15};
	return S_OK;
}

void Menu::Release()
{
}

void Menu::Update(GAME_MODE & currMode, int & modeNum)
{
	SelectMenu(currMode, modeNum);

	button[5].pos.x += 50 * TimeManager::GetSingleton()->GetElapsedTime();
	button[6].pos.x += 50 * TimeManager::GetSingleton()->GetElapsedTime();
}

void Menu::Render(HDC hdc, GAME_MODE & currMode)
{
	if (currMode != GAME_MODE::PLAY)
	{
		background->AlphaRender(hdc, 0, 0, 170);
		menuList->Render(hdc, 406, 15);

		button[int(currMode)].img->Render(hdc, button[int(currMode)].imgPos.x, button[int(currMode)].imgPos.y);
		button[5].img->Render(hdc, button[5].pos.x, button[5].pos.y);
		button[6].img->Render(hdc, button[6].pos.x, button[6].pos.y);
		Rectangle(hdc, button[5].rc.left, button[5].rc.top, button[5].rc.right, button[5].rc.bottom);
		Rectangle(hdc, button[6].rc.left, button[6].rc.top, button[6].rc.right, button[6].rc.bottom);
	}
}

void Menu::SelectMenu(GAME_MODE & currMode, int & modeNum)
{
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_ESCAPE))
	{
		if (currMode == GAME_MODE::PLAY)
			currMode = GAME_MODE(++modeNum);
		else
		{
			currMode = GAME_MODE::PLAY;
			modeNum = 0;
		}
	}

	if (currMode != GAME_MODE::PLAY)
	{
		if (KeyManager::GetSingleton()->IsOnceKeyDown('Q'))
		{
			if (modeNum > 1)
				modeNum--;
			currMode = GAME_MODE(modeNum);
		}

		if (KeyManager::GetSingleton()->IsOnceKeyDown('E'))
		{
			if (modeNum < 4)
				modeNum++;
			currMode = GAME_MODE(modeNum);
		}
	}
}
