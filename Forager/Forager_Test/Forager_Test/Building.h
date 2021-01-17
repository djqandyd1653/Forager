#pragma once
#include "GameNode.h"

typedef struct tagTile TILE_INFO;

class Image;
class TileMap;

class Building : public GameNode
{
protected:
	FPOINT pos;
	RECT rc;

	Image* img;
	TileMap* tileMap;
	tagTile* tile;
	
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc, FPOINT cameraPos);
};

