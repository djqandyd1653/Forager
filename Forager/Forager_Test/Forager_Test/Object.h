#pragma once
#include "GameNode.h"

class Image;

class Object : public GameNode
{
protected:
	RECT rc;
	Image* img;
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc, FPOINT pos);
};

