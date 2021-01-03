#include "PlayScene.h"
#include "Image.h"
#include "Camera.h"
#include "TileMap.h"
#include "Player.h"

HRESULT PlayScene::Init()
{
	blueBrush = (HBRUSH)CreateSolidBrush(RGB(48, 149, 252));
	transparentBrush = (HBRUSH)GetStockObject(NULL_BRUSH);

	camera = new Camera;
	camera->Init();

	tileMap = new TileMap;
	tileMap->Init();

	player = new Player;
	player->Init();

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
	camera->Update();
	tileMap->Update();
	player->Update();
}

void PlayScene::Render(HDC hdc)
{
	SelectObject(hdc, blueBrush);

	camera->Render(hdc);

	SelectObject(hdc, transparentBrush);

	tileMap->Render(hdc, camera->GetStartNumX(), camera->GetStartNumY());
	player->Render(hdc);
	
	char s[32];
	wsprintf(s, "%d, %d", camera->GetStartNumX(), camera->GetStartNumY());
	TextOut(hdc, 50, 50, s, (int)strlen(s));
}

PlayScene::PlayScene()
{
}

PlayScene::~PlayScene()
{
	this->Release();
}
