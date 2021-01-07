#pragma once
#include "Object.h"

class Tree : public Object
{
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc, FPOINT pos);
};

