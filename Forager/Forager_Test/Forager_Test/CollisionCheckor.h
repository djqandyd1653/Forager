#pragma once
#include "pch.h"

typedef struct tagTile TILE_INFO;
class TileMap;
class Player;
class ObjectFactory;
class ItemManager;

class CollisionCheckor
{
private:
	tagTile* tile;

	Player* player;
	TileMap* tileMap;
	ObjectFactory* objFactory;
	ItemManager* itemMgr;

public:
	HRESULT Init(Player* player, TileMap* tileMap, ObjectFactory* objFactory, ItemManager* itemMgr);
	void Update(FPOINT cameraPos);

	void CheckCollisionPO();						// 플레이어와 오브젝트 충돌검사
	void CheckCollisionMO(FPOINT cameraPos);		// 마우스와 오브젝트 충돌검사
	void CheckCollisionIPIM();						// 아이템과 플레이어 또는 아이템과 마우스
};

