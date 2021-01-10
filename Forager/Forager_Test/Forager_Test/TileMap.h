#pragma once
#include "GameNode.h"

typedef struct tagTile TILE_INFO;
class Image;
class Object;
class Building;

class TileMap : public GameNode
{
private:
	tagTile* tile;
	Image* img;

	int randNum;					// 랜덤타일 번호

	vector<int> vecGrassTileNum;	// 땅 타입 타일번호 리스트

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc, FPOINT cameraPos);

	void LoadMap(int mapNum, int posNum);
	FPOINT RandGrassPos();

	tagTile* GetTile() { return tile; }
	void SetObject(Object* obj);
	void SetBuilding(Building* building);
	void SetAbleBuild(bool isBuild);

	TileMap();
	~TileMap();
};

