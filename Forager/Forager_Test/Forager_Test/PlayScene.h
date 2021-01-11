#pragma once
#include "GameNode.h"

//struct tagTile;

class Camera;
class TileMap;
class Player;
class PlayUI;
class ObjectFactory;
class CollisionCheckor;

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

	HBRUSH blueBrush;
	HBRUSH transparentBrush;

	float currObjCreateTime;	// 오브젝트 생성 남은시간

	// test
	Image* img;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	PlayScene();
	~PlayScene();
};

