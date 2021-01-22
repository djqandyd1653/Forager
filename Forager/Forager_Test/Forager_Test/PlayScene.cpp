#include "PlayScene.h"
#include "Image.h"
#include "Camera.h"
#include "TileMap.h"
#include "TileMapToolScene.h"
#include "Player.h"
#include "PlayUI.h"
#include "ObjectFactory.h"
#include "Object.h"
#include "CollisionCheckor.h"
#include "ItemManager.h"
#include "Menu.h"
#include "Inventory.h"
#include "BuildManager.h"

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
	menu->Init();

	inven = new Inventory;
	inven->Init();

	buildMgr = new BuildManager;
	buildMgr->Init();

	collisionCheckor = new CollisionCheckor;
	collisionCheckor->Init(player, tileMap, objFactory, itemMgr, inven, menu, buildMgr, &renderMap);

	changeMode = false;
	renderSize = 1.0f;

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
	buildMgr->Release();
	delete buildMgr;
	delete collisionCheckor;
	delete menu;
	delete inven;
}

void PlayScene::Update()
{
	if (changeMode)
		changeMode = false;

	if (menu->GetCurrMode() == GAME_MODE::PLAY)
	{
		player->Update(camera->GetPos());
		Object* tempObj = objFactory->CreateAcObj(1.0f, 5, tileMap->RandGrassPos());
		if (tempObj != nullptr)
		{
			tileMap->SetObject(tempObj);
			renderMap.insert(make_pair(int(tempObj->GetPos().y), tempObj));
		}
		tileMap->Update();
	}
		
	camera->Update();
	collisionCheckor->Update(camera->GetPos());
	objFactory->Update();
	playUI->Update();
	itemMgr->Update();
	buildMgr->Update();
	bool isSelectBuild = buildMgr->GetSelectBuild();
	menu->Update(isSelectBuild);
	buildMgr->SetSelectBuild(isSelectBuild);

	//if (changeMode)
	//{
	//	ChangeInfo();
	//}
}

void PlayScene::Render(HDC hdc)
{
	SelectObject(hdc, blueBrush);

	PatBlt(hdc, 0, 0, WINSIZE_X, WINSIZE_Y, PATCOPY);

	SelectObject(hdc, transparentBrush);

	tileMap->Render(hdc, camera->GetPos());
	
	itRender = renderMap.begin();
	while (itRender != renderMap.end())
	{
		if ((*itRender).first >= player->GetPos().y)
			break;
		(*itRender).second->Render(hdc, camera->GetPos());
		itRender++;
	}

	player->Render(hdc, camera->GetPos());

	while (itRender != renderMap.end())
	{
		(*itRender).second->Render(hdc, camera->GetPos());
		itRender++;
	}

	camera->Render(hdc);
	itemMgr->Render(hdc, camera->GetPos());

	playUI->Render(hdc);
	menu->Render(hdc);

	if(menu->GetCurrMode() == GAME_MODE::INVENTORY)
		inven->Render(hdc);

	if (menu->GetCurrMode() == GAME_MODE::BUILD)
		buildMgr->Render(hdc);

	char c[32];
	wsprintf(c, "%d", renderMap.size());
	TextOut(hdc, 200, 200, c, (int)strlen(c));
}

//void PlayScene::ChangeInfo()
//{
//	tile = tileMap->GetTile();
//	
//	if ((lastModeNum == 1 || lastModeNum == 4) && modeNum == 2)
//	{
//		renderSize = 0.8f;
//		for (int i = 0; i < MAP_SIZE * MAP_SIZE; i++)
//		{
//			tile[i].rc.left *= renderSize;
//			tile[i].rc.top *= renderSize;
//			tile[i].rc.right *= renderSize;
//			tile[i].rc.bottom *= renderSize;
//		}
//
//		player->SetPosX(player->GetPos().x * renderSize);
//		player->SetPosY(player->GetPos().y * renderSize);
//	}
//	else if ((lastModeNum == 1 || lastModeNum == 4) && modeNum == 3)
//	{
//		renderSize = 0.5f;
//		for (int i = 0; i < MAP_SIZE * MAP_SIZE; i++)
//		{
//			tile[i].rc.left *= renderSize;
//			tile[i].rc.top *= renderSize;
//			tile[i].rc.right *= renderSize;
//			tile[i].rc.bottom *= renderSize;
//		}
//
//		player->SetPosX(player->GetPos().x * renderSize);
//		player->SetPosY(player->GetPos().y * renderSize);
//	}
//	else if (lastModeNum == 2 && modeNum == 3)
//	{
//
//	}
//	else if (lastModeNum == 3 && modeNum == 2)
//	{
//
//	}
//	else if(lastModeNum == 2)
//	{
//		renderSize = 1.0f;
//		for (int i = 0; i < MAP_SIZE; i++)
//		{
//			for (int j = 0; j < MAP_SIZE; j++)
//			{
//				SetRect(&tile[i * MAP_SIZE + j].rc,
//					j * TILE_SIZE,
//					i * TILE_SIZE,
//					(j + 1) * TILE_SIZE,
//					(i + 1) * TILE_SIZE);
//			}
//		}
//		player->SetPosX(player->GetPos().x * 1.25f);
//		player->SetPosY(player->GetPos().y * 1.25f);
//	}
//	else if (lastModeNum == 3)
//	{
//		renderSize = 1.0f;
//		for (int i = 0; i < MAP_SIZE; i++)
//		{
//			for (int j = 0; j < MAP_SIZE; j++)
//			{
//				SetRect(&tile[i * MAP_SIZE + j].rc,
//					j * TILE_SIZE,
//					i * TILE_SIZE,
//					(j + 1) * TILE_SIZE,
//					(i + 1) * TILE_SIZE);
//			}
//		}
//		player->SetPosX(player->GetPos().x * 1.25f);
//		player->SetPosY(player->GetPos().y * 1.25f);
//	}
//}

PlayScene::PlayScene()
{
}

PlayScene::~PlayScene()
{
	this->Release();
}
