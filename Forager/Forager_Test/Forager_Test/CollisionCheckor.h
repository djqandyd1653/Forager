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

	void CheckCollisionPO();						// �÷��̾�� ������Ʈ �浹�˻�
	void CheckCollisionMO(FPOINT cameraPos);		// ���콺�� ������Ʈ �浹�˻�
	void CheckCollisionIPIM();						// �����۰� �÷��̾� �Ǵ� �����۰� ���콺
};

