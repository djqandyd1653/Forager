#pragma once
#include "GameNode.h"

enum class ITEM_TYPE;

class Image;

class Object : public GameNode
{
private:

protected:
	// status
	FPOINT pos;
	RECT rc;
	int typeNum;
	ITEM_TYPE itemType;
	int maxHp;
	int currHp;
	int EXP;

	// image
	int frameCnt;
	float frameTime;
	bool isFrame;

	Image* img;
	Image* hp;
	Image* hpBack;
	
public:
	virtual HRESULT Init(int typeNum);
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc, FPOINT cameraPos);
	virtual void UpdateRect() = 0;
	virtual void UpdateFrame(float time);

	FPOINT GetPos() { return pos; }
	void SetPos(FPOINT pos) { this->pos = pos; };

	RECT GetRect() { return rc; }
	int GetTypeNum() { return typeNum; }
	ITEM_TYPE GetItemType() { return itemType; }

	int GetMaxHp() { return maxHp; }
	int GetCurrHp() { return currHp; }
	void SetCurrHp(int hp) { currHp = hp; }
	void GetDamage(int damage) 
	{ 
		currHp -= damage;
		if (currHp < 0)
			currHp = 0;
	}

	void SetIsFrame(bool isFrame) { this->isFrame = isFrame; }

	int GiveEXP() { return EXP; }
};