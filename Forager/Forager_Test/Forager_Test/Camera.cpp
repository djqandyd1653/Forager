#include "Camera.h"
#include "TileMapToolScene.h"
#include "Player.h"

HRESULT Camera::Init(Player* player)
{
	startNumX = -480;
	startNumY = -750;
	endNumX = startNumX + WINSIZE_X;
	endNumY = startNumY + WINSIZE_Y;

	mousePosX = WINSIZE_X / 2;
	mousePosY = WINSIZE_Y / 2;

	this->player = player;

	return S_OK;
}

void Camera::Release()
{
}

void Camera::Update()
{
	int x = WINSIZE_X / 2 - player->GetPos().x;
	int y = WINSIZE_Y / 2 - player->GetPos().y;

	startNumX += x;
	startNumY += y;
	endNumX += x;
	endNumY += y;

	if (startNumX < 0 && endNumX > 2 * WINSIZE_X - MAP_SIZE * TILE_SIZE)
	{
		player->SetPosX(player->GetPos().x + x);
	}
	if (startNumY < 0 && endNumY > 2 * WINSIZE_Y - MAP_SIZE * TILE_SIZE)
	{
		player->SetPosY(player->GetPos().y + y);
	}

	if (g_ptMouse.x - mousePosX > 100)
	{
		startNumX += 100;
		endNumX += 100;
		//player->SetPosX(player->GetPos().x + 100);
		mousePosX = g_ptMouse.x;
	}

	if (g_ptMouse.x - mousePosX < -100)
	{
		startNumX -= 100;
		endNumX -= 100;
		//player->SetPosX(player->GetPos().x - 100);
		mousePosX = g_ptMouse.x;
	}

	if (g_ptMouse.y - mousePosY > 100)
	{
		startNumY += 100;
		endNumY += 100;
		//player->SetPosY(player->GetPos().y + 100);
		mousePosY = g_ptMouse.y;
	}

	if (g_ptMouse.y - mousePosY < -100)
	{
		startNumY -= 100;
		endNumY -= 100;
		//player->SetPosY(player->GetPos().y - 100);
		mousePosY = g_ptMouse.y;
	}

	if (startNumX >= 0)
	{
		startNumX = 0;
		endNumX = WINSIZE_X;
	}

	if (startNumY >= 0)
	{
		startNumY = 0;
		endNumY = WINSIZE_Y;
	}

	if (endNumX <= 2 * WINSIZE_X - MAP_SIZE * TILE_SIZE)
	{
		startNumX = WINSIZE_X - MAP_SIZE * TILE_SIZE;
		endNumX = 2 * WINSIZE_X - MAP_SIZE * TILE_SIZE;
	}

	if (endNumY <= 2 * WINSIZE_Y - MAP_SIZE * TILE_SIZE)
	{
		startNumY = WINSIZE_Y - MAP_SIZE * TILE_SIZE;
		endNumY = 2 * WINSIZE_Y - MAP_SIZE * TILE_SIZE;
	}
}

void Camera::Render(HDC hdc)
{
	PatBlt(hdc, 0, 0, WINSIZE_X, WINSIZE_Y, PATCOPY);
}
