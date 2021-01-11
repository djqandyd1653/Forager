#pragma once
#include "GameNode.h"

class Image;

class Weapon : public GameNode
{
protected:
	Image* img;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Attack() = 0;
};

