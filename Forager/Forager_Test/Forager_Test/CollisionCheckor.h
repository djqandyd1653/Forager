#pragma once
#include "pch.h"

typedef struct tagTile TILE_INFO;

class TileMap;
class Player;
class ObjectFactory;
class ItemManager;
class Inventory;
class Menu;
class BuildManager;

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
	BuildManager* buildMgr;
	multimap<int, GameNode*>* renderMap;

public:
	HRESULT Init(Player* player, TileMap* tileMap, ObjectFactory* objFactory, ItemManager* itemMgr, Inventory* inven, Menu* menu, BuildManager* buildMgr, multimap<int, GameNode*>* map);
	void Update(FPOINT cameraPos);

	void CheckCollisionPO();						// �÷��̾�� ������Ʈ �浹�˻�
	void CheckCollisionMO(FPOINT cameraPos);		// ���콺�� ������Ʈ �浹�˻�
	void CheckCollisionIPIM(FPOINT cameraPos);		// �����۰� �÷��̾� �Ǵ� �����۰� ���콺 �浹�˻�
	void ChekckCollisionMS();						// ���콺�� �κ��丮 ���� �浹�˻�
	void CheckCollisionMB();						// ���콺�� �޴���ư �浹�˻�
	void CheckCollisionMBB();						// ���콺�� �Ǽ��޴���ư �浹�˻�
	void CheckCollisionMT(FPOINT cameraPos);		// ���콺�� Ÿ�� (�ǹ� ��ġ ������������ �ƴ���)
	void CheckCreateBuilding();						// �ǹ����� �˻�
};

