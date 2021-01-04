#pragma once
#include "GameNode.h"

class Player;

class Camera : public GameNode
{
private:
	int startNumX;
	int startNumY;
	int endNumX;
	int endNumY;

	int mousePosX;		// 마우스 기준좌표 X
	int mousePosY;		// 마우스 기준좌표 Y

	Player* player;

public:
	virtual HRESULT Init(Player* player);
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	int GetStartNumX() { return startNumX; }
	int GetStartNumY() { return startNumY; }
};

