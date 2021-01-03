#pragma once
#include "GameNode.h"

//struct tagTile;

class Camera;
class TileMap;
class Player;

class PlayScene : public GameNode
{
private:

	Camera* camera;
	TileMap* tileMap;
	Player* player;

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

