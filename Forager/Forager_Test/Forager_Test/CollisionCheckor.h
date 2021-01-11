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

	void CheckCollisionPO();		// �÷��̾�� ������Ʈ �浹�˻�
	void CheckCollisionMO(FPOINT cameraPos);		// ���콺�� ������Ʈ �浹�˻�
};

