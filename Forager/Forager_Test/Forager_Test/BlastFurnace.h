#pragma once
#include "Building.h"

class BlastFurnace : public Building
{
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc, FPOINT cameraPos);
};

