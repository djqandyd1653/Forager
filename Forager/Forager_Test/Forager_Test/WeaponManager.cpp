#include "WeaponManager.h"
#include "Weapon.h"

void WeaponManager::Attack(bool &ableAttack)
{
	weapon->Attack(ableAttack);
}

void WeaponManager::ChangeWeapon(Weapon * weapon)
{
	if (this->weapon) delete this->weapon;
	this->weapon = weapon;
	this->weapon->Init();
}

void WeaponManager::Release()
{
	delete weapon;
}

void WeaponManager::Render(HDC hdc, POINT playerPos, FPOINT cameraPos, bool isLeft)
{
	weapon->Render(hdc, playerPos, cameraPos, isLeft);
}
