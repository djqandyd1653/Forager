#pragma once
#include "Object.h"

class Rock : public Object
{
public:
	virtual HRESULT Init(int typeNum);
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc, FPOINT pos);
};

