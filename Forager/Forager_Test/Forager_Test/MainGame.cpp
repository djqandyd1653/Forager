#include "MainGame.h"
#include "Image.h"
#include "TestScene.h"
#include "TileMapToolScene.h"
#include "PlayScene.h"

HRESULT MainGame::Init()
{
	srand(UINT(time(NULL)));

	backBuffer = new Image();
	backBuffer->Init(WINSIZE_X, WINSIZE_Y);
	memDC = backBuffer->GetMemDC();
	hdc = GetDC(g_hWnd);

	// font
	AddFontResource("Font/Maplestory Bold.ttf");
	font.lfHeight = 28;
	font.lfWidth = 0;
	font.lfEscapement = 0;
	font.lfOrientation = 0;
	font.lfWeight = 0;
	font.lfItalic = 0;
	font.lfUnderline = 0;
	font.lfStrikeOut = 0;
	font.lfCharSet = HANGEUL_CHARSET;
	font.lfOutPrecision = 0;
	font.lfClipPrecision = 0;
	font.lfQuality = 0;
	font.lfPitchAndFamily = 0;
	strcpy_s(font.lfFaceName, "Maplestory");
	
	// tile
	ImageManager::GetSingleton()->AddImage("Sample_Tile", "Image/Sample_Tile.bmp", 224, 112, SAMPLE_TILE_X, SAMPLE_TILE_Y);
	ImageManager::GetSingleton()->AddImage("Tile_Border", "Image/Tile_Border.bmp", 224, 224, 4, 4);

	// player
	ImageManager::GetSingleton()->AddImage("Player_Idle", "Image/Player/Player_Idle.bmp", 640, 112, 10, 2);
	ImageManager::GetSingleton()->AddImage("Player_Run", "Image/Player/Player_Run.bmp", 512, 112, 8, 2);
	ImageManager::GetSingleton()->AddImage("Player_Roll", "Image/Player/Player_Roll.bmp", 1000, 200, 10, 2);

	// player UI
	ImageManager::GetSingleton()->AddImage("EXP_Bar", "Image/GUI/Player_UI/EXP_Bar.bmp", 792, 22);
	ImageManager::GetSingleton()->AddImage("EXP_Back", "Image/GUI/Player_UI/EXP_Bar_Back.bmp", 800, 30);
	ImageManager::GetSingleton()->AddImage("Life", "Image/GUI/Player_UI/Life.bmp", 210, 38, 5, 1);
	ImageManager::GetSingleton()->AddImage("Life_Back", "Image/GUI/Player_UI/Life_Back.bmp", 42, 38);
	ImageManager::GetSingleton()->AddImage("Stamina", "Image/GUI/Player_UI/Stamina.bmp", 63, 16);
	ImageManager::GetSingleton()->AddImage("Stamina_Back", "Image/GUI/Player_UI/Stamina_Back.bmp", 73, 26);
	ImageManager::GetSingleton()->AddImage("Object_Hp", "Image/GUI/Player_UI/Object_Hp.bmp", 44, 7);
	ImageManager::GetSingleton()->AddImage("Object_Hp_Back", "Image/GUI/Player_UI/Object_Hp_Back.bmp", 50, 13);

	// object
	ImageManager::GetSingleton()->AddImage("Tree", "Image/Object/Tree.bmp", 280, 168, 5, 1);
	ImageManager::GetSingleton()->AddImage("Rock", "Image/Object/Rock.bmp", 112, 56, 2, 1);
	ImageManager::GetSingleton()->AddImage("Fruit", "Image/Object/Fruit.bmp", 168, 56, 3, 1);

	// building
	ImageManager::GetSingleton()->AddImage("Blast_Furnace", "Image/Object/Blast_Furnace.bmp", 336, 168, 3, 1);
	ImageManager::GetSingleton()->AddImage("Blast_Furnace_Impossible", "Image/Object/Blast_Furnace_Impossible.bmp", 112, 160);
	ImageManager::GetSingleton()->AddImage("Anvil", "Image/Object/Anvil.bmp", 285, 95, 3, 1);
	ImageManager::GetSingleton()->AddImage("Anvil_Impossible", "Image/Object/Anvil_Impossible.bmp", 100, 90);
	ImageManager::GetSingleton()->AddImage("Sewing_Machine", "Image/Object/Sewing_Machine.bmp", 336, 115, 3, 1);
	ImageManager::GetSingleton()->AddImage("Sewing_Machine_Impossible", "Image/Object/Sewing_Machine_Impossible.bmp", 127, 155);
	ImageManager::GetSingleton()->AddImage("Bridge", "Image/Object/Bridge.bmp", 224, 56, 4, 1);
	ImageManager::GetSingleton()->AddImage("Fish_Trap", "Image/Object/Fish_Trap.bmp", 168, 56, 3, 1);

	// Item
	ImageManager::GetSingleton()->AddImage("Fruit_Item", "Image/Item/Fruit_Item1.bmp", 70, 70);
	ImageManager::GetSingleton()->AddImage("Fruit_Item_Drop", "Image/Item/Fruit_Item_Drop.bmp", 56, 56);
	ImageManager::GetSingleton()->AddImage("Rock_Item", "Image/Item/Rock_Item1.bmp", 70, 70);
	ImageManager::GetSingleton()->AddImage("Rock_Item_Drop", "Image/Item/Rock_Item_Drop.bmp", 56, 56);
	ImageManager::GetSingleton()->AddImage("Tree_Item", "Image/Item/Tree_Item1.bmp", 70, 70);
	ImageManager::GetSingleton()->AddImage("Tree_Item_Drop", "Image/Item/Tree_Item_Drop.bmp", 56, 56);

	// weapon
	ImageManager::GetSingleton()->AddImage("Pickaxe", "Image/Weapon/Pickaxe_Action.bmp", 255, 140, 3, 2);

	// Inventory
	ImageManager::GetSingleton()->AddImage("Inventory_Back", "Image/GUI/Inventory/Inventory_Back.bmp", 1280, 720);
	ImageManager::GetSingleton()->AddImage("Inventory_Slot", "Image/GUI/Inventory/Inventory_Slot.bmp", 88, 88);

	TimeManager::GetSingleton()->Init();

	SceneManager::GetSingleton()->AddScene("Play", new PlayScene);
	SceneManager::GetSingleton()->AddScene("Test", new TestScene);
	SceneManager::GetSingleton()->AddScene("Tile", new TileMapToolScene);

	SceneManager::GetSingleton()->ChangeScene("Play");
	return S_OK;
}

void MainGame::Release()
{
	backBuffer->Release();
	delete backBuffer;
}

void MainGame::Update()
{
	SceneManager::GetSingleton()->currScene->Update();
}

void MainGame::Render()
{
	//흰색 빈 비트맵 (패턴 방식 초기화)
	PatBlt(memDC, 0, 0, WINSIZE_X, WINSIZE_Y, PATCOPY); 

	SceneManager::GetSingleton()->currScene->Render(memDC);
	TimeManager::GetSingleton()->Render(memDC);

	
	// 1. 이미지를 출력할 핸들 / 2. 이미지를 출력할 x, y / 3. 원본 이미지의 너비와 높이 
	// 4. 이미지의 핸들 / 5. 가져올 이미지의 시작점 x, y
	backBuffer->Render(hdc, 0, 0);
}

LPARAM MainGame::wndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_MOUSEMOVE:
		g_ptMouse.x = LOWORD(lParam);
		g_ptMouse.y = HIWORD(lParam);
		break;
	case WM_CREATE:
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}
