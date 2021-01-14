#pragma once
#include "pch.h"

typedef struct tagTile TILE_INFO;
class TileMap;
class Player;
class ObjectFactory;
class ItemManager;
class Inventory;

class CollisionCheckor
{
private:
	tagTile* tile;

	Player* player;
	TileMap* tileMap;
	ObjectFactory* objFactory;
	ItemManager* itemMgr;
	Inventory* inven;

public:
	HRESULT Init(Player* player, TileMap* tileMap, ObjectFactory* objFactory, ItemManager* itemMgr, Inventory* inven);
	void Update(FPOINT cameraPos);

	void CheckCollisionPO();						// �÷��̾�� ������Ʈ �浹�˻�
	void CheckCollisionMO(FPOINT cameraPos);		// ���콺�� ������Ʈ �浹�˻�
	void CheckCollisionIPIM(FPOINT cameraPos);						// �����۰� �÷��̾� �Ǵ� �����۰� ���콺
};

