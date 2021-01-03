#include "Camera.h"
#include "TileMapToolScene.h"

HRESULT Camera::Init()
{
	startNumX = 0;
	startNumY = 0;
	endNumX = WINSIZE_X;
	endNumY = WINSIZE_Y;

	return S_OK;
}

void Camera::Release()
{
}

void Camera::Update()
{
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT))
	{
		if (startNumX < 0)
		{
			startNumX += static_cast<int>(TimeManager::GetSingleton()->GetElapsedTime() * 500);
			endNumX += static_cast<int>(TimeManager::GetSingleton()->GetElapsedTime() * 500);
		}
		if(startNumX >= 0)
		{
			startNumX = 0;
			endNumX = WINSIZE_X;
		}
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_UP))
	{
		if (startNumY < 0)
		{
			startNumY += static_cast<int>(TimeManager::GetSingleton()->GetElapsedTime() * 500);
			endNumY += static_cast<int>(TimeManager::GetSingleton()->GetElapsedTime() * 500);
		}
		if(startNumY >= 0)
		{
			startNumY = 0;
			endNumY = WINSIZE_Y;
		}
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT))
	{
		if (endNumX > 2 * WINSIZE_X - MAP_SIZE * TILE_SIZE)
		{
			startNumX -= static_cast<int>(TimeManager::GetSingleton()->GetElapsedTime() * 500);
			endNumX -= static_cast<int>(TimeManager::GetSingleton()->GetElapsedTime() * 500);
		}
		if(endNumX <= 2 * WINSIZE_X - MAP_SIZE * TILE_SIZE)
		{
			startNumX = WINSIZE_X - MAP_SIZE * TILE_SIZE;
			endNumX = 2 * WINSIZE_X - MAP_SIZE * TILE_SIZE;
		}
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_DOWN))
	{
		if (endNumY > 2 * WINSIZE_Y - MAP_SIZE * TILE_SIZE)
		{
			startNumY -= static_cast<int>(TimeManager::GetSingleton()->GetElapsedTime() * 500);
			endNumY -= static_cast<int>(TimeManager::GetSingleton()->GetElapsedTime() * 500);
		}
		if(endNumY <= 2 * WINSIZE_Y - MAP_SIZE * TILE_SIZE)
		{
			startNumY = WINSIZE_Y - MAP_SIZE * TILE_SIZE;
			endNumY = 2 * WINSIZE_Y - MAP_SIZE * TILE_SIZE;
		}
	}
}

void Camera::Render(HDC hdc)
{
	PatBlt(hdc, 0, 0, WINSIZE_X, WINSIZE_Y, PATCOPY);
}
