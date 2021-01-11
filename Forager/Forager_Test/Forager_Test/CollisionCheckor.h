#pragma once
#include "pch.h"

typedef struct tagTile TILE_INFO;
class TileMap;
class Player;
class ObjectFactory;

class CollisionCheckor
{
private:
	tagTile* tile;

	Player* player;
	TileMap* tileMap;
	ObjectFactory* objFactory;

public:
	HRESULT Init(Player* player, TileMap* tileMap, ObjectFactory* objFactory);
	void Update(FPOINT cameraPos);

	void CheckCollisionPO();		// 플레이어와 오브젝트 충돌검사
	void CheckCollisionMO(FPOINT cameraPos);		// 마우스와 오브젝트 충돌검사
};

