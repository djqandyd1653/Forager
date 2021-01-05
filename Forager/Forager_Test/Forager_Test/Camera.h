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

	int playerPosX;		// �÷��̾� ������ǥ X
	int playerPosY;		// �÷��̾� ������ǥ Y
	int mousePosX;		// ���콺 ������ǥ X
	int mousePosY;		// ���콺 ������ǥ Y

	Player* player;

public:
	virtual HRESULT Init(Player* player);
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	int GetStartNumX() { return startNumX; }
	int GetStartNumY() { return startNumY; }
};

