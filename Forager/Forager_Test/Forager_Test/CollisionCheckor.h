#pragma once
#include "pch.h"

typedef struct tagTile TILE_INFO;
enum class GAME_MODE;

class TileMap;
class Player;
class ObjectFactory;
class ItemManager;
class Inventory;
class Menu;

class CollisionCheckor
{
private:
	tagTile* tile;

	Player* player;
	TileMap* tileMap;
	ObjectFactory* objFactory;
	ItemManager* itemMgr;
	Inventory* inven;
	Menu* menu;

public:
	HRESULT Init(Player* player, TileMap* tileMap, ObjectFactory* objFactory, ItemManager* itemMgr, Inventory* inven, Menu* menu);
	void Update(FPOINT cameraPos, GAME_MODE& currMode, int& modeNum);

	void CheckCollisionPO();										// �÷��̾�� ������Ʈ �浹�˻�
	void CheckCollisionMO(FPOINT cameraPos);						// ���콺�� ������Ʈ �浹�˻�
	void CheckCollisionIPIM(FPOINT cameraPos);						// �����۰� �÷��̾� �Ǵ� �����۰� ���콺 �浹�˻�
	void ChekckCollisionMS(GAME_MODE& currMode, int& modeNum);		// ���콺�� �κ��丮 ���� �浹�˻�
	void CheckCollisionMB(GAME_MODE& currMode, int& modeNum);		// ���콺�� �޴���ư �浹�˻�
};

