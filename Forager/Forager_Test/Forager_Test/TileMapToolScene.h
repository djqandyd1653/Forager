#pragma once
#include "GameNode.h"

#define TILE_SIZE			56	// Ÿ�� 1�� ũ��
#define SAMPLE_TILE_X		4	// ����Ÿ�� x�� ����
#define SAMPLE_TILE_Y		2	// ����Ÿ�� y�� ����
#define MAP_SIZE			40	// �� 1�� ������
#define CAMERA_SIZE			12	// ī�޶� ������

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

	// ����Ÿ�� ����
	TILE_INFO tileInfo[MAP_SIZE * MAP_SIZE];
	RECT rcMain;

	// ����Ÿ�� ����
	SAMPLE_TILE sampleTileInfo[SAMPLE_TILE_X * SAMPLE_TILE_Y];
	RECT rcSample;

	// ����Ÿ�� ����
	SELECT_TILE selectTileInfo;

	// ���̺�, �ε� ��ư
	RECT rcSave;
	RECT rcLoad;

	char c[32];

	// ī�޶� ��ǥ
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

