#pragma once
#include "GameNode.h"

class Image;
class Player;
class TextUI;

class PlayUI : public GameNode
{
private:

	bool isBack;
	int lifeFrameX;
	float lifeFrameTime;
	int cnt;

	Image* EXP[2];	
	Image* life[2];
	Image* stamina[2];

	Player* player;

	TextUI* levelText;
public:
	virtual HRESULT Init(Player* player);
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
};

