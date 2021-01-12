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
	int nextFrameDir;		// ���� ���������� �̵�

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc, POINT playerPos, FPOINT cameraPos, bool isLeft);
	virtual void Attack(bool &ableAttack) = 0;
};

