#pragma once
#include "Weapon.h"

class Pickaxe : public Weapon
{
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
};

