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

	// object
	ImageManager::GetSingleton()->AddImage("Tree", "Image/Object/Tree.bmp", 280, 168, 5, 1);
	ImageManager::GetSingleton()->AddImage("Rock", "Image/Object/Rock.bmp", 112, 56, 2, 1);
	ImageManager::GetSingleton()->AddImage("Fruit", "Image/Object/Fruit.bmp", 112, 56, 2, 1);

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
