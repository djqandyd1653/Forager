#pragma once
#include "GameNode.h"

enum class GAME_MODE
{
	PLAY,
	MENU,
	INVENTORY,
	BUILD,
	LAND_PURCHASSE,
	SETTING
};

class Camera;
class TileMap;
class Player;
class PlayUI;
class ObjectFactory;
class CollisionCheckor;
class ItemManager;
class Inventory;

// test
class Image;

class PlayScene : public GameNode
{
private:
	
	Camera* camera;
	TileMap* tileMap;
	Player* player;
	PlayUI* playUI;
	ObjectFactory* objFactory;
	CollisionCheckor* collisionCheckor;
	ItemManager* itemMgr;
	Inventory* inven;

	HBRUSH blueBrush;
	HBRUSH transparentBrush;

	GAME_MODE currMode;			// ���� ���
	float currObjCreateTime;	// ������Ʈ ���� �����ð�

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	PlayScene();
	~PlayScene();
};

