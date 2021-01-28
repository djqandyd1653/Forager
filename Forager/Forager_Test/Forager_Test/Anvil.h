#pragma once
#include "Building.h"

class Anvil : public Building
{
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc, FPOINT cameraPos);

	virtual void SetRect();
};

