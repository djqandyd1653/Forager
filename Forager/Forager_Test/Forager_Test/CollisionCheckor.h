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

	void CheckCollisionPO();						// 플레이어와 오브젝트 충돌검사
	void CheckCollisionMO(FPOINT cameraPos);		// 마우스와 오브젝트 충돌검사
	void CheckCollisionIPIM(FPOINT cameraPos);		// 아이템과 플레이어 또는 아이템과 마우스 충돌검사
	void ChekckCollisionMS();						// 마우스와 인벤토리 슬롯 충돌검사
	void CheckCollisionMB();						// 마우스와 메뉴버튼 충돌검사
	void CheckCollisionMBB();						// 마우스와 건설메뉴버튼 충돌검사
	void CheckCollisionMT(FPOINT cameraPos);		// 마우스와 타일 (건물 설치 가능지역인지 아닌지)
	void CheckCreateBuilding();						// 건물생성 검사
};

