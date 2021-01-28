#pragma once
#include "GameNode.h"

class Image;

class Building : public GameNode
{
protected:
	POINT pos;
	RECT rc;

	Image* img;
	
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc, FPOINT cameraPos);

	virtual void SetRect() = 0;

	void SetPos(POINT pos) { this->pos = pos; }
};

