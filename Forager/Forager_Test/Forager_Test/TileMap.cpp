#include "TileMap.h"
#include "TileMapToolScene.h"
#include "Image.h"

HRESULT TileMap::Init()
{
	// Ÿ�� �ʱ�ȭ
	if (tile == nullptr)
		tile = new tagTile[MAP_SIZE * MAP_SIZE];

	for (int i = 0; i < MAP_SIZE * MAP_SIZE; i++)
	{
		tile[i].frameX = -1;
		tile[i].frameY = -1;
	}

	// �� �ε�
	DWORD readByte;
	HANDLE hFile = CreateFile("Save/saveMapData.map", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(hFile, tile, sizeof(tagTile) * MAP_SIZE * MAP_SIZE, &readByte, NULL);

	CloseHandle(hFile);

	img = ImageManager::GetSingleton()->FindImage("Sample_Tile");

	return S_OK;
}

void TileMap::Release()
{
	ImageManager::GetSingleton()->DeleteImg("Sample_Tile");
	SAFE_DELETE_ARRAY(tile);
}

void TileMap::Update()
{
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

void TileMap::Render(HDC hdc, int x, int y)
{
	for (int i = 0; i < MAP_SIZE * MAP_SIZE; i++)
	{
		if (tile[i].terrain == TERRAIN::WATER)
			continue;

		// ȭ�� ���̸� ���� ���ϱ�
		if (tile[i].rc.left + x > WINSIZE_X || tile[i].rc.top + y > WINSIZE_Y || tile[i].rc.right + x < 0 || tile[i].rc.bottom + y < 0)
			continue;

		// Ÿ��
		img->FrameRender(hdc, tile[i].rc.left + x, tile[i].rc.top + y, tile[i].frameX, tile[i].frameY);

		// Ÿ�� ��ȣ
		char c[32];
		wsprintf(c, "%d", tile[i].tileNum);
		TextOut(hdc, tile[i].rc.left + x, tile[i].rc.top + y, c, (int)strlen(c));

		// ����Ÿ�� ���ڼ�
		Rectangle(hdc, tile[i].rc.left + x, tile[i].rc.top + y, tile[i].rc.right + x, tile[i].rc.bottom + y);
	}
}

void TileMap::LoadMap(int mapNum, int posNum)
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
		}
	}
}

TileMap::TileMap() : tile(nullptr)
{
}

TileMap::~TileMap()
{
	this->Release();
}
