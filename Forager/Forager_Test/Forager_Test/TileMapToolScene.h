#pragma once
#include "GameNode.h"

#define TILE_SIZE			56	// 타일 1개 크기
#define SAMPLE_TILE_X		4	// 샘플타일 x축 개수
#define SAMPLE_TILE_Y		2	// 샘플타일 y축 개수
#define MAP_SIZE			40	// 맵 1개 사이즈
#define CAMERA_SIZE			12	// 카메라 사이즈

enum class TERRAIN { GRASS, WATER, CLIFF };

class Object;
class Building;

typedef struct tagTile
{
	TERRAIN terrain;
	RECT rc;
	int tileNum;
	int frameX;
	int frameY;
	bool ableBuild;

	Object* obj;
	Building* building;
}TILE_INFO;

typedef struct tagSampleTile
{
	RECT rc;
	int frameX;
	int frameY;
}SAMPLE_TILE;

typedef struct tagSelectTile
{
	int startFrameX;
	int startFrameY;
	int endFrameX;
	int endFrameY;
}SELECT_TILE;

class Image;

class TileMapToolScene : public GameNode
{
private:
	Image* sampleTile;
	Image* selectTile;

	// 메인타일 정보
	TILE_INFO tileInfo[MAP_SIZE * MAP_SIZE];
	RECT rcMain;

	// 샘플타일 정보
	SAMPLE_TILE sampleTileInfo[SAMPLE_TILE_X * SAMPLE_TILE_Y];
	RECT rcSample;

	// 선택타일 정보
	SELECT_TILE selectTileInfo;

	// 세이브, 로드 버튼
	RECT rcSave;
	RECT rcLoad;

	char c[32];

	// 카메라 좌표
	int startNumX;
	int endNumX;
	int startNumY;
	int endNumY;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc) ;

	void CheckRcSample();
	void CheckRcMain();
	void Save();
	void Load();

	void MoveCamera();
};

