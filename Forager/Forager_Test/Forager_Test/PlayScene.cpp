#include "PlayScene.h"
#include "Image.h"
#include "Camera.h"
#include "TileMap.h"
#include "Player.h"
#include "PlayUI.h"
#include "ObjectFactory.h"

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

	playUI = new PlayUI;
	playUI->Init(player);

	objFactory = new ObjectFactory;
	objFactory->Init();

	currTime = 0.0f;
	currCnt = 0;

	return S_OK;
}

void PlayScene::Release()
{
	camera->Release();
	tileMap->Release();
	player->Release();
	playUI->Release();
	objFactory->Release();
}

void PlayScene::Update()
{
	player->Update(camera->GetPos());
	camera->Update();
	tileMap->Update();
	playUI->Update();
	objFactory->Update();
	objFactory->CreateAcObj(currTime, 1.0f, currCnt, 5);
}

void PlayScene::Render(HDC hdc)
{
	SelectObject(hdc, blueBrush);

	PatBlt(hdc, 0, 0, WINSIZE_X, WINSIZE_Y, PATCOPY);

	SelectObject(hdc, transparentBrush);

	tileMap->Render(hdc, camera->GetPos());
	player->Render(hdc, camera->GetPos());
	camera->Render(hdc);
	playUI->Render(hdc);
	objFactory->Render(hdc, camera->GetPos());
}

PlayScene::PlayScene()
{
}

PlayScene::~PlayScene()
{
	this->Release();
}
