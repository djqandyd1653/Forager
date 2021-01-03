#pragma once
#include "GameNode.h"

struct tagTile;
class Image;

class TileMap : public GameNode
{
private:
	tagTile* tile;
	Image* img;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc, int x, int y);

	void LoadMap(int mapNum, int posNum);

	TileMap();
	~TileMap();
};

