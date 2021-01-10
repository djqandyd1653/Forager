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

	currObjCreateTime = 0.0f;
	currObjCnt = 0;

	//test
	img = ImageManager::GetSingleton()->FindImage("Sewing_Machine");

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
	tileMap->SetObject(objFactory->CreateAcObj(currObjCreateTime, 1.0f, currObjCnt, 30, tileMap->RandGrassPos()));
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
	playUI->Render(hdc);

	// test
	//img->FrameRender(hdc, g_ptMouse.x, g_ptMouse.y, 0, 0);
}

PlayScene::PlayScene()
{
}

PlayScene::~PlayScene()
{
	this->Release();
}
