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
	string itemKey;		// 아이템 키
	int cnt;			// 아이템 개수
	bool isMove;		// 아이템 드랍시 움직임 여부
	int dir;			// 방향
	float incline;		// 아이템 드랍시 기울기
	int maxHeight;		// 아이템 드랍시 최대 높이

	Image* img;
	Image* invenImg;
	Image* dropImg;
	ITEM_TYPE type;

public:
	virtual HRESULT Init(ITEM_TYPE itemType);
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc, FPOINT cameraPos);
	virtual void UseItem();

	FPOINT GetPos() { return pos; }
	void SetPos(FPOINT pos) { this->pos = pos; }
	void SetRandParabola()
	{
		destPos = { pos.x + 56, pos.y + 56 };
		cnt = 1;
		isMove = true;
		if (rand() % 2 == 0)
			dir = 1;
		else
			dir = -1;
		incline = (rand() % 3 + 1) * 0.1f;
		maxHeight = rand() % 30 + 45;
	}

	RECT GetRect() { return rc; }

	string GetItemKey() { return itemKey; }

	int GetItemCnt() { return cnt; }
	void SetItemCnt(int cnt) { this->cnt = cnt; }
	void PlusItemCnt(int cnt) { this->cnt += cnt; }
	void MinusItemCnt(int cnt) { this->cnt -= cnt; }

	void SetIsMove(bool isMove) { this->isMove = isMove; }

	ITEM_TYPE GetType() { return type; }

	void SetInvenImg() { img = invenImg; }
	void SetDropImg() { img = dropImg; }

	Image* GetImg() { return img; }

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

