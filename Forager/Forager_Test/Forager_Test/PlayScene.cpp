#include "PlayScene.h"
#include "Image.h"
#include "Camera.h"
#include "TileMap.h"
#include "Player.h"

HRESULT PlayScene::Init()
{
	blueBrush = (HBRUSH)CreateSolidBrush(RGB(48, 149, 252));
	transparentBrush = (HBRUSH)GetStockObject(NULL_BRUSH);

	tileMap = new TileMap;
	tileMap->Init();

	player = new Player;
	player->Init(tileMap->GetTile());

	camera = new Camera;
	camera->Init(player);

	return S_OK;
}

void PlayScene::Release()
{
	camera->Release();
	tileMap->Release();
	player->Release();
}

void PlayScene::Update()
{
	player->Update(camera->GetPos());
	camera->Update();
	tileMap->Update();
}

void PlayScene::Render(HDC hdc)
{
	SelectObject(hdc, blueBrush);

	PatBlt(hdc, 0, 0, WINSIZE_X, WINSIZE_Y, PATCOPY);

	SelectObject(hdc, transparentBrush);

	tileMap->Render(hdc, camera->GetPos());
	player->Render(hdc, camera->GetPos());
	camera->Render(hdc);
	
	char s[32];
	wsprintf(s, "%d, %d", camera->GetPos().x, camera->GetPos().y);
	TextOut(hdc, 50, 50, s, (int)strlen(s));
}

PlayScene::PlayScene()
{
}

PlayScene::~PlayScene()
{
	this->Release();
}
