#include "Building.h"
#include "Image.h"
#include "TileMap.h"
#include "TileMapToolScene.h"

HRESULT Building::Init()
{
	//test
	img = ImageManager::GetSingleton()->FindImage("Blast_Furnace_Impossible");
	return S_OK;
}

void Building::Release()
{
}

void Building::Update()
{
}

void Building::Render(HDC hdc, FPOINT cameraPos)
{
	// test
	//img->FrameRender(hdc, g_ptMouse.x, g_ptMouse.y, 0, 0);
	img->Render(hdc, g_ptMouse.x, g_ptMouse.y);
}
