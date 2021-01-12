#pragma once
#include "GameNode.h"

class Image;

class Weapon : public GameNode
{
protected:
	Image* img;
	int currFrameCnt;
	float currFrameTime;
	float frameDelayTime;
	int nextFrameDir;		// 다음 프레임으로 이동

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc, POINT playerPos, FPOINT cameraPos, bool isLeft);
	virtual void Attack(bool &ableAttack) = 0;
};

