#include "PlayScene.h"
#include "Image.h"
#include "Camera.h"
#include "TileMap.h"
#include "Player.h"
#include "PlayUI.h"
#include "ObjectFactory.h"
#include "CollisionCheckor.h"
#include "ItemManager.h"
#include "Menu.h"
#include "Inventory.h"

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

	itemMgr = new ItemManager;
	itemMgr->Init();

	menu = new Menu;
	menu->Init(currMode, modeNum);

	inven = new Inventory;
	inven->Init();

	collisionCheckor = new CollisionCheckor;
	collisionCheckor->Init(player, tileMap, objFactory, itemMgr, inven, menu);

	currObjCreateTime = 0.0f;

	return S_OK;
}

void PlayScene::Release()
{
	camera->Release();
	delete camera;
	tileMap->Release();
	delete tileMap;
	player->Release();
	delete player;
	playUI->Release();
	delete playUI;
	objFactory->Release();
	delete objFactory;
	itemMgr->Release();
	delete itemMgr;
	delete collisionCheckor;
	delete menu;
	delete inven;
}

void PlayScene::Update()
{
	if(currMode == GAME_MODE::PLAY)
		player->Update(camera->GetPos());
	camera->Update();
	collisionCheckor->Update(camera->GetPos(), currMode, modeNum);
	tileMap->Update();
	objFactory->Update();
	tileMap->SetObject(objFactory->CreateAcObj(currObjCreateTime, 1.0f, 5, tileMap->RandGrassPos()));
	playUI->Update();
	itemMgr->Update();

	menu->Update(currMode, modeNum);
}

void PlayScene::Render(HDC hdc)
{
	SelectObject(hdc, blueBrush);

	PatBlt(hdc, 0, 0, WINSIZE_X, WINSIZE_Y, PATCOPY);

	SelectObject(hdc, transparentBrush);

	tileMap->Render(hdc, camera->GetPos());
	player->Render(hdc, camera->GetPos());
	camera->Render(hdc);
	objFactory->Render(hdc, camera->GetPos());
	itemMgr->Render(hdc, camera->GetPos());

	playUI->Render(hdc);
	menu->Render(hdc, currMode);
	inven->Render(hdc, currMode);
}

PlayScene::PlayScene()
{
}

PlayScene::~PlayScene()
{
	this->Release();
}
