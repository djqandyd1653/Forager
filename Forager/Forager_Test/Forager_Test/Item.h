#pragma once
#include "GameNode.h"

enum class ITEM_TYPE
{
	CONSUM = 0,
	FRUIT,
	ETC = 100,
	TREE,
	ROCK,
};

class Item : public GameNode
{
protected:
	FPOINT pos;
	FPOINT destPos;
	RECT rc;
	bool isMove;
	int dir;
	float incline;
	int maxHeight;

	Image* img;
	ITEM_TYPE type;

public:
	virtual HRESULT Init(int num);
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc, FPOINT cameraPos);
	virtual void UseItem();

	FPOINT GetPos() { return pos; }
	void SetPos(FPOINT pos) { this->pos = pos; }
	void SetRandParabola()
	{
		destPos = { pos.x + 56, pos.y + 56 };
		incline = (rand() % 3 + 1) * 0.1f;
		maxHeight = rand() % 30 + 45;
		if (rand() % 2 == 0)
			dir = 1;
		else
			dir = -1;
	}

	void SetIsMove(bool isMove) { this->isMove = isMove; }

	ITEM_TYPE GetType() { return type; }

	void SetInit()
	{
		pos = { 0.0f, 0.0f };
		destPos = { 0.0f, 0.0f };
		incline = 0.0f;
		maxHeight = 0;
		dir = 0;
		isMove = false;
	}
};

