#include "TestScene.h"
#include "Image.h"
#include "TileMapToolScene.h"

HRESULT TestScene::Init()
{
	if(tile == nullptr)
		tile = new tagTile[MAP_SIZE * MAP_SIZE];

	for (int i = 0; i < MAP_SIZE * MAP_SIZE; i++)
	{
		tile[i].frameX = -1;
		tile[i].frameY = -1;
	}

	// 맵 로드
	DWORD readByte;
	HANDLE hFile = CreateFile("Save/saveMapData.map", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(hFile, tile, sizeof(tagTile) * MAP_SIZE * MAP_SIZE, &readByte, NULL);

	CloseHandle(hFile);
	
	img = ImageManager::GetSingleton()->FindImage("Sample_Tile");
	//border = ImageManager::GetSingleton()->FindImage("Tile_Border");


	startNumX = 0;
	startNumY = 0;
	endNumX = WINSIZE_X;
	endNumY = WINSIZE_Y;
	time = 0.0f;

	myBrush = nullptr;
	oldBrush = nullptr;

	//vecGrassTile.reserve(40);
	return S_OK;
}

void TestScene::Release()
{
}

void TestScene::Update()
{
	if (PtInRect(&tile[123].rc, g_ptMouse))
	{
		int a = 0;
	}

	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT))
	{
		if (startNumX != 0)
		{
			startNumX++;
			endNumX++;
		}
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_UP))
	{
		if (startNumY != 0)
		{
			startNumY++;
			endNumY++;
		}
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT))
	{
		if (endNumX != 2 * WINSIZE_X - MAP_SIZE * TILE_SIZE)
		{
			startNumX--;
			endNumX--;
		}
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_DOWN))
	{
		if (endNumY != 2 * WINSIZE_Y - MAP_SIZE * TILE_SIZE)
		{
			startNumY--;
			endNumY--;
		}
	}

	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_NUMPAD1))
		LoadMap(1, 1);
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_NUMPAD2))
		LoadMap(1, 2);
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_NUMPAD3))
		LoadMap(1, 3);
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_NUMPAD4))
		LoadMap(1, 4);
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_NUMPAD5))
		LoadMap(1, 5);
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_NUMPAD6))
		LoadMap(1, 6);
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_NUMPAD7))
		LoadMap(1, 7);
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_NUMPAD8))
		LoadMap(1, 8);
}

void TestScene::Render(HDC hdc)
{
	myBrush = (HBRUSH)CreateSolidBrush(RGB(48, 149, 252));
	oldBrush = (HBRUSH)SelectObject(hdc, myBrush);

	PatBlt(hdc, 0, 0, WINSIZE_X, WINSIZE_Y, PATCOPY);

	SelectObject(hdc, oldBrush);
	DeleteObject(myBrush);

	myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	oldBrush = (HBRUSH)SelectObject(hdc, myBrush);

	for (int i = 0; i < MAP_SIZE * MAP_SIZE; i++)
	{
		if (tile[i].terrain == TERRAIN::WATER)
			continue;

		// 화면 밖이면 렌더 안하기
		if (tile[i].rc.left + startNumX > WINSIZE_X || tile[i].rc.top + startNumY > WINSIZE_Y || tile[i].rc.right + startNumX < 0 || tile[i].rc.bottom + startNumY < 0)
			continue;

		// 타일
		img->FrameRender(hdc, tile[i].rc.left + startNumX, tile[i].rc.top + startNumY, tile[i].frameX, tile[i].frameY);

		//// 타일 태두리
		//for (itTile = vecGrassTile.begin(); itTile != vecGrassTile.end(); itTile++)
		//{
		//	int num = (*itTile).tileNum;

		//	if (tile[num + 1].terrain != TERRAIN::GRASS)
		//	{
		//		border->FrameRender(hdc, (*itTile).rc.left + startNumX, (*itTile).rc.top + startNumY, 2, 0);
		//	}

		//	if (tile[num - 1].terrain != TERRAIN::GRASS)
		//	{
		//		border->FrameRender(hdc, (*itTile).rc.left + startNumX, (*itTile).rc.top + startNumY, 0, 0);
		//	}

		//	if (tile[num - MAP_SIZE].terrain != TERRAIN::GRASS)
		//	{
		//		border->FrameRender(hdc, (*itTile).rc.left + startNumX, (*itTile).rc.top + startNumY, 1, 0);
		//	}

		//	if (tile[num + MAP_SIZE].terrain != TERRAIN::GRASS)
		//	{
		//		border->FrameRender(hdc, (*itTile).rc.left + startNumX, (*itTile).rc.top + startNumY, 3, 0);
		//	}
		//}

		// 타일 번호
		char c[32];
		wsprintf(c, "%d", tile[i].tileNum);
		TextOut(hdc, tile[i].rc.left + startNumX, tile[i].rc.top + startNumY, c, (int)strlen(c));

		// 매인타일 격자선
		Rectangle(hdc, tile[i].rc.left + startNumX, tile[i].rc.top + startNumY, tile[i].rc.right + startNumX, tile[i].rc.bottom + startNumY);
	}

	SelectObject(hdc, oldBrush);
	DeleteObject(myBrush);

	char s[32];
	wsprintf(s, "%d, %d, %d, %d", startNumX, startNumY, endNumX, endNumY);
	TextOut(hdc, 50, 50, s, (int)strlen(s));
}

void TestScene::LoadMap(int mapNum, int posNum)
{
	tagTile* loadTile = new tagTile[CAMERA_SIZE * CAMERA_SIZE];
	string fileName = "Save/saveMapData" + to_string(mapNum) + ".map";

	DWORD readByte;
	HANDLE hFile = CreateFile(fileName.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(hFile, loadTile, sizeof(tagTile) * CAMERA_SIZE * CAMERA_SIZE, &readByte, NULL);

	CloseHandle(hFile);

	int posX;
	int posY;

	switch (posNum)
	{
	case 1:
		posX = 2;
		posY = 2;
		break;
	case 2:
		posX = 14;
		posY = 2;
		break;
	case 3:
		posX = 26;
		posY = 2;
		break;
	case 4:
		posX = 2;
		posY = 14;
		break;
	case 5:
		posX = 26;
		posY = 14;
		break;
	case 6:
		posX = 2;
		posY = 26;
		break;
	case 7:
		posX = 14;
		posY = 26;
		break;
	case 8:
		posX = 26;
		posY = 26;
		break;
	default:
		break;
	}

	for (int i = 0; i < CAMERA_SIZE; i++)
	{
		for (int j = 0; j < CAMERA_SIZE; j++)
		{
			tile[i + posX + (j + posY) * MAP_SIZE].frameX = loadTile[i + j * CAMERA_SIZE].frameX;
			tile[i + posX + (j + posY) * MAP_SIZE].frameY = loadTile[i + j * CAMERA_SIZE].frameY;
			tile[i + posX + (j + posY) * MAP_SIZE].terrain = loadTile[i + j * CAMERA_SIZE].terrain;

			//// 땅 타일 입력
			//if (tile[i + posX + (j + posY) * MAP_SIZE].terrain == TERRAIN::GRASS)
			//{
			//	vecGrassTile.push_back(tile[i + posX + (j + posY) * MAP_SIZE]);
			//}
		}
	}
}

TestScene::TestScene() : tile(nullptr)
{
}

TestScene::~TestScene()
{
	this->Release();
}
