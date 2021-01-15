// StrategyPattern(전략 패턴) 사용

#pragma once
#include "pch.h"

class Weapon;

class WeaponManager
{
private:
	Weapon* weapon;

public:
	void Attack(bool &ableAttack);
	void ChangeWeapon(Weapon* weapon);
	void Release();
	void Render(HDC hdc, POINT playerPos, FPOINT cameraPos, bool isLeft);

	WeaponManager() : weapon(nullptr) {}
};

