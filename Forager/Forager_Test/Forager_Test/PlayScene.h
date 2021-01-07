#pragma once
#include "GameNode.h"

//struct tagTile;

class Camera;
class TileMap;
class Player;
class PlayUI;
class Object;

class PlayScene : public GameNode
{
private:

	Camera* camera;
	TileMap* tileMap;
	Player* player;
	PlayUI* playUI;
	Object* obj1;
	Object* obj2;
	Object* obj3;

	HBRUSH blueBrush;
	HBRUSH transparentBrush;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	PlayScene();
	~PlayScene();
};

