#pragma once
#include "GameNode.h"

class Camera : public GameNode
{
private:
	int startNumX;
	int startNumY;
	int endNumX;
	int endNumY;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	int GetStartNumX() { return startNumX; }
	int GetStartNumY() { return startNumY; }
};

