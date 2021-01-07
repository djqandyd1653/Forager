#pragma once
#include "Object.h"

class Rock : public Object
{
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc, FPOINT pos);
};

