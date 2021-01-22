#pragma once
#include "GameNode.h"

typedef struct tagTile TILE_INFO;

class Camera;
class TileMap;
class Player;
class PlayUI;
class ObjectFactory;
class CollisionCheckor;
class ItemManager;
class Menu;
class Inventory;
class BuildManager;

class PlayScene : public GameNode
{
private:

	multimap<int, GameNode*> renderMap;
	multimap<int, GameNode*>::iterator itRender;

	Camera* camera;
	TileMap* tileMap;
	tagTile* tile;
	Player* player;
	PlayUI* playUI;
	ObjectFactory* objFactory;
	CollisionCheckor* collisionCheckor;
	ItemManager* itemMgr;
	Menu* menu;
	Inventory* inven;
	BuildManager* buildMgr;

	HBRUSH blueBrush;
	HBRUSH transparentBrush;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	//void ChangeInfo();

	PlayScene();
	~PlayScene();
};

