#include "TileMapToolScene.h"
#include "Image.h"

HRESULT TileMapToolScene::Init()
{
	SetWindowSize(0, 0, WINSIZE_X, WINSIZE_Y);

	sampleTile = ImageManager::GetSingleton()->FindImage("샘플타일");

	// 세이브, 로드 버튼
	SetRect(&rcSave, 800, WINSIZE_Y - 220, 950, WINSIZE_Y - 150);
	SetRect(&rcLoad, 1000, WINSIZE_Y - 220, 1150, WINSIZE_Y - 150);

	// 메인타일 rect설정
	rcMain.left = 0;
	rcMain.top = 0;
	rcMain.right = rcMain.left + CAMERA_SIZE * TILE_SIZE;
	rcMain.bottom = rcMain.top + CAMERA_SIZE * TILE_SIZE;

	// 샘플타일 rect설정
	rcSample.left = WINSIZE_X - sampleTile->GetWidth();
	rcSample.top = 0;
	rcSample.right = WINSIZE_X;
	rcSample.bottom = sampleTile->GetHeight();

	// 선택된 타일 정보
	selectTileInfo.startFrameX = -1;
	selectTileInfo.startFrameY = -1;
	selectTileInfo.endFrameX = -1;
	selectTileInfo.endFrameY = -1;

	// 오른쪽 샘플 타일의 정보를 선택 / 셋팅
	for (int i = 0; i < SAMPLE_TILE_Y; i++)
	{
		for (int j = 0; j < SAMPLE_TILE_X; j++)
		{
			// 오른쪽에 그리기 위해 조정
			SetRect(&sampleTileInfo[i * SAMPLE_TILE_X + j].rc,
					WINSIZE_X - sampleTile->GetWidth() + j * TILE_SIZE,
					i * TILE_SIZE,
					WINSIZE_X - sampleTile->GetWidth() + (j + 1) * TILE_SIZE,
					i * TILE_SIZE + TILE_SIZE);

			sampleTileInfo[i * SAMPLE_TILE_X + j].frameX = j;
			sampleTileInfo[i * SAMPLE_TILE_X + j].frameY = i;
		}
	}

	// 왼쪽 상단에 메인 타일의 정보를 셋팅
	for (int i = 0; i < MAP_SIZE; i++)
	{
		for (int j = 0; j < MAP_SIZE; j++)
		{
			SetRect(&tileInfo[i * MAP_SIZE + j].rc, 
					j * TILE_SIZE, 
					i * TILE_SIZE, 
					(j + 1) * TILE_SIZE, 
					(i + 1) * TILE_SIZE);

			tileInfo[i * MAP_SIZE + j].terrain = TERRAIN::WATER;
			tileInfo[i * MAP_SIZE + j].tileNum = i * MAP_SIZE + j;
			tileInfo[i * MAP_SIZE + j].frameX = 0;
			tileInfo[i * MAP_SIZE + j].frameY = 1;
		}
	}

	// 카메라 좌표
	startNumX = 0;
	endNumX = 11;
	startNumY = 0;
	endNumY = 11;

	return S_OK;
}

void TileMapToolScene::Release()
{
}

void TileMapToolScene::Update()
{
	// 샘플 타일 영역 안 인지 확인
	CheckRcSample();
	CheckRcMain();

	// 버튼 처리
	Save();
	Load();

	MoveCamera();
}

void TileMapToolScene::Render(HDC hdc)
{
	// 흰색 그리기
	PatBlt(hdc, 0, 0, WINSIZE_X, WINSIZE_Y, WHITENESS);

	if (sampleTile)
	{
		// 샘플 타일 그리기
		sampleTile->Render(hdc, WINSIZE_X - sampleTile->GetWidth(), 0);

		// 메인타일
		for (int i = 0; i < MAP_SIZE * MAP_SIZE; i++)
		{
			// 타일 카메라 틀
			if (i % MAP_SIZE < startNumX || i % MAP_SIZE > endNumX || 
				i / MAP_SIZE < startNumY || i / MAP_SIZE > endNumY)
				continue;
			
			int left = tileInfo[i].rc.left - startNumX * TILE_SIZE;
			int top = tileInfo[i].rc.top - startNumY * TILE_SIZE;

			sampleTile->FrameRender(hdc, left, top, tileInfo[i].frameX, tileInfo[i].frameY);

			// 타일 번호
			wsprintf(c, "%d", tileInfo[i].tileNum);
			TextOut(hdc, left, top, c, (int)strlen(c));
		}
	}

	// 선택된 타일
	if (selectTileInfo.startFrameX != -1)
	{
		for (int i = 0; i <= selectTileInfo.endFrameY - selectTileInfo.startFrameY; i++)
		{
			for (int j = 0; j <= selectTileInfo.endFrameX - selectTileInfo.startFrameX; j++)
			{
				sampleTile->FrameRender(hdc, WINSIZE_X - sampleTile->GetWidth() + TILE_SIZE * j, sampleTile->GetHeight() + 100 + TILE_SIZE * i,
					selectTileInfo.startFrameX + j, selectTileInfo.startFrameY + i);
			}
		}
	}
	
	//Rectangle(hdc, rcMain.left, rcMain.top, rcMain.right, rcMain.bottom);
	//Rectangle(hdc, rcSample.left, rcSample.top, rcSample.right, rcSample.bottom);

	// 투명 사각형
	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);

	// 매인타일 격자선
	for (int i = 0; i < MAP_SIZE; i++)
	{
		for (int j = 0; j < MAP_SIZE; j++)
		{
			// 격자선 카메라 틀
			if (j % MAP_SIZE > 11 || i % MAP_SIZE > 11)
				continue;
			Rectangle(hdc, j * TILE_SIZE, i * TILE_SIZE, (j + 1) * TILE_SIZE, (i + 1) * TILE_SIZE);
		}
	}
	
	// 샘플타일 격자선
	for (int i = 0; i < SAMPLE_TILE_Y; i++)
	{
		for (int j = 0; j < SAMPLE_TILE_X; j++)
		{
			Rectangle(
				hdc, 
				j * TILE_SIZE + WINSIZE_X - sampleTile->GetWidth(),
				i * TILE_SIZE,
				(j + 1) * TILE_SIZE + WINSIZE_X - sampleTile->GetWidth(),
				(i + 1) * TILE_SIZE);
		}
	}

	SelectObject(hdc, oldBrush);
	DeleteObject(myBrush);

	//// 세이브, 로드 버튼
	Rectangle(hdc, rcSave.left, rcSave.top, rcSave.right, rcSave.bottom);
	Rectangle(hdc, rcLoad.left, rcLoad.top, rcLoad.right, rcLoad.bottom);
}

void TileMapToolScene::CheckRcSample()
{
	if (PtInRect(&rcSample, g_ptMouse))
	{
		if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
		{
			// 버튼 누르면 다시 초기화
			selectTileInfo.startFrameX = 0;
			selectTileInfo.startFrameY = 0;
			selectTileInfo.endFrameX = 0;
			selectTileInfo.endFrameY = 0;

			int posX = g_ptMouse.x - rcSample.left;
			int posY = g_ptMouse.y - rcSample.top;
			int idX = posX / TILE_SIZE;
			int idY = posY / TILE_SIZE;

			selectTileInfo.startFrameX = sampleTileInfo[idX + idY * SAMPLE_TILE_X].frameX;
			selectTileInfo.startFrameY = sampleTileInfo[idX + idY * SAMPLE_TILE_X].frameY;
		}

		if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_LBUTTON))
		{
			int posX = g_ptMouse.x - rcSample.left;
			int posY = g_ptMouse.y - rcSample.top;
			int idX = posX / TILE_SIZE;
			int idY = posY / TILE_SIZE;

			selectTileInfo.endFrameX = sampleTileInfo[idX + idY * SAMPLE_TILE_X].frameX;
			selectTileInfo.endFrameY = sampleTileInfo[idX + idY * SAMPLE_TILE_X].frameY;

			// 드래그 예외처리
			if (selectTileInfo.startFrameX > selectTileInfo.endFrameX)
			{
				int temp = selectTileInfo.startFrameX;
				selectTileInfo.startFrameX = selectTileInfo.endFrameX;
				selectTileInfo.endFrameX = temp;
			}

			if (selectTileInfo.startFrameY > selectTileInfo.endFrameY)
			{
				int temp = selectTileInfo.startFrameY;
				selectTileInfo.startFrameY = selectTileInfo.endFrameY;
				selectTileInfo.endFrameY = temp;
			}
		}
	}
}

void TileMapToolScene::CheckRcMain()
{
	if (PtInRect(&rcMain, g_ptMouse))
	{
		if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LBUTTON))
		{
			int posX = g_ptMouse.x - rcMain.left;
			int posY = g_ptMouse.y - rcMain.top;
			int idX = posX / TILE_SIZE;
			int idY = posY / TILE_SIZE;

			for (int i = 0; i <= selectTileInfo.endFrameY - selectTileInfo.startFrameY; i++)
			{
				for (int j = 0; j <= selectTileInfo.endFrameX - selectTileInfo.startFrameX; j++)
				{
					// 타일 범위 벗어나면 예외처리
					if (((idX + j) % MAP_SIZE == 0 && j != 0)
						|| ((idY + i) % MAP_SIZE == 0 && i != 0))
					{
						continue;
					}

					tileInfo[(idX + j + startNumX) + (idY + i + startNumY) * MAP_SIZE].frameX = selectTileInfo.startFrameX + j;
					tileInfo[(idX + j + startNumX) + (idY + i + startNumY) * MAP_SIZE].frameY = selectTileInfo.startFrameY + i;

					if(selectTileInfo.startFrameY + i == 0)
						tileInfo[(idX + j + startNumX) + (idY + i + startNumY) * MAP_SIZE].terrain = TERRAIN::GRASS;
					else if(selectTileInfo.startFrameY + i == 1 && selectTileInfo.startFrameX + j == 2)
						tileInfo[(idX + j + startNumX) + (idY + i + startNumY) * MAP_SIZE].terrain = TERRAIN::CLIFF;
				}
			}
		}
	}
}

void TileMapToolScene::Save()
{
	if (PtInRect(&rcSave, g_ptMouse) && KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
	{
		DWORD writtenByte;
		HANDLE hFile = CreateFile("Save/saveMapData1.map", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		WriteFile(hFile, tileInfo, sizeof(TILE_INFO) * MAP_SIZE * MAP_SIZE, &writtenByte, NULL);

		CloseHandle(hFile);
	}
}

void TileMapToolScene::Load()
{
	if (PtInRect(&rcLoad, g_ptMouse) && KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
	{
		DWORD readByte;
		HANDLE hFile = CreateFile("Save/saveMapData1.map", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		ReadFile(hFile, tileInfo, sizeof(TILE_INFO) * MAP_SIZE * MAP_SIZE, &readByte, NULL);

		CloseHandle(hFile);
	}
}

void TileMapToolScene::MoveCamera()
{
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LEFT))
	{
		if (startNumX == 0)
			return;

		startNumX--;
		endNumX--;
	}
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_UP))
	{
		if (startNumY == 0)
			return;

		startNumY--;
		endNumY--;
	}
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_RIGHT))
	{
		if (endNumX == MAP_SIZE - 1)
			return;

		startNumX++;
		endNumX++;
	}
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_DOWN))
	{
		if (endNumY == MAP_SIZE - 1)
			return;

		startNumY++;
		endNumY++;
	}
}
