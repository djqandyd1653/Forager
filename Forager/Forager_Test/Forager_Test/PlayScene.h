#pragma once
#include "GameNode.h"

enum class GAME_MODE
{
	PLAY,
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
class Menu;
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
	Menu* menu;
	Inventory* inven;

	HBRUSH blueBrush;
	HBRUSH transparentBrush;

	GAME_MODE currMode;			// ���� ���
	int modeNum;				// ���� ��� ��ȣ
	float currObjCreateTime;	// ������Ʈ ���� �����ð�

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	PlayScene();
	~PlayScene();
};

