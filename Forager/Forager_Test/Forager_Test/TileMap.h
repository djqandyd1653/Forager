#pragma once
#include "GameNode.h"

typedef struct tagTile TILE_INFO;
class Image;

class TileMap : public GameNode
{
private:
	tagTile* tile;
	Image* img;

	vector<tagTile*> vecGrassTile;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc, FPOINT cameraPos);

	void LoadMap(int mapNum, int posNum);

	tagTile* GetTile() { return tile; }

	TileMap();
	~TileMap();
};

