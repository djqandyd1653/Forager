#pragma once
#include "GameNode.h"

class Player;

class Camera : public GameNode
{
private:
	FPOINT pos;

	Player* player;

public:
	virtual HRESULT Init(Player* player);
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	FPOINT GetPos() { return pos; }
};

