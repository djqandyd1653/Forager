#pragma once
#include "pch.h"

class GameNode
{
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Render(HDC hdc, FPOINT pos);
};

