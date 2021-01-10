#pragma once
#include "Object.h"

class Fruit : public Object
{
public:
	virtual HRESULT Init(int typeNum);
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc, FPOINT cameraPos);
	virtual void UpdateRect();
};

