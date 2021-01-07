#include "PlayScene.h"
#include "Image.h"
#include "Camera.h"
#include "TileMap.h"
#include "Player.h"
#include "PlayUI.h"
#include "Tree.h"
#include "Rock.h"
#include "Fruit.h"

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

	obj1 = new Tree;
	obj1->Init();

	obj2 = new Rock;
	obj2->Init();
	   
	obj3 = new Fruit;
	obj3->Init();

	return S_OK;
}

void PlayScene::Release()
{
	camera->Release();
	tileMap->Release();
	player->Release();
	playUI->Release();
}

void PlayScene::Update()
{
	player->Update(camera->GetPos());
	camera->Update();
	tileMap->Update();
	playUI->Update();
}

void PlayScene::Render(HDC hdc)
{
	SelectObject(hdc, blueBrush);

	PatBlt(hdc, 0, 0, WINSIZE_X, WINSIZE_Y, PATCOPY);

	SelectObject(hdc, transparentBrush);

	tileMap->Render(hdc, camera->GetPos());
	player->Render(hdc, camera->GetPos());
	camera->Render(hdc);
	obj1->Render(hdc, camera->GetPos());
	obj2->Render(hdc, camera->GetPos());
	obj3->Render(hdc, camera->GetPos());

	playUI->Render(hdc);
}

PlayScene::PlayScene()
{
}

PlayScene::~PlayScene()
{
	this->Release();
}
