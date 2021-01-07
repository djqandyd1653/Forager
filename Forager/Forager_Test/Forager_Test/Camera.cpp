#include "Camera.h"
#include "TileMapToolScene.h"
#include "Player.h"

HRESULT Camera::Init(Player* player)
{
	this->player = player;

	return S_OK;
}

void Camera::Release()
{
}

void Camera::Update()
{
	float destPosX = (player->GetPos().x * 70 + (g_ptMouse.x + pos.x) * 30) / 100 - WINSIZE_X / 2;
	float destPosY = (player->GetPos().y * 70 + (g_ptMouse.y + pos.y) * 30) / 100 - WINSIZE_Y / 2;

	if(abs(pos.x - destPosX) > 5.0f)
		pos.x = Lerp(pos.x, destPosX, TimeManager::GetSingleton()->GetElapsedTime() * 5);
	if (abs(pos.y - destPosY) > 5.0f)
		pos.y = Lerp(pos.y, destPosY, TimeManager::GetSingleton()->GetElapsedTime() * 5);
	//pos.y = (player->GetPos().y * 4 + g_ptMouse.y + pos.y) / 5 - WINSIZE_Y / 2;

	if (pos.x <= 0)
	{
		pos.x = 0;
	}

	if (pos.y <= 0)
	{
		pos.y = 0;
	}

	if (pos.x >= MAP_SIZE * TILE_SIZE - WINSIZE_X)
	{
		pos.x = MAP_SIZE * TILE_SIZE - WINSIZE_X;
	}

	if (pos.y >= MAP_SIZE * TILE_SIZE - WINSIZE_Y)
	{
		pos.y = MAP_SIZE * TILE_SIZE - WINSIZE_Y;
	}
}

void Camera::Render(HDC hdc)
{


	char c[32];
	wsprintf(c, "%d, %d", (int)g_ptMouse.x + (int)pos.x, (int)g_ptMouse.y + (int)pos.y);
	TextOut(hdc, g_ptMouse.x, g_ptMouse.y, c, (int)strlen(c));

	wsprintf(c, "%d, %d", 
		(int)(player->GetPos().x + g_ptMouse.x + pos.x) / 2,
		(int)(player->GetPos().y + g_ptMouse.y + pos.y) / 2);
	TextOut(hdc, 
		(int)(player->GetPos().x + g_ptMouse.x - pos.x) / 2,
		(int)(player->GetPos().y + g_ptMouse.y - pos.y) / 2, c, (int)strlen(c));


	wsprintf(c, "%d, %d", (int)player->GetPos().x, (int)player->GetPos().y);
	TextOut(hdc, int(player->GetPos().x - GetPos().x), int(player->GetPos().y - GetPos().y), c, (int)strlen(c));
}
