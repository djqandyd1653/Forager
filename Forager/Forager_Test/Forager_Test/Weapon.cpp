#include "Weapon.h"

HRESULT Weapon::Init()
{
	currFrameCnt = 0;
	currFrameTime = 0.0f;
	nextFrameDir = 1;
	return S_OK;
}

void Weapon::Release()
{
}

void Weapon::Update()
{
}

void Weapon::Render(HDC hdc, POINT playerPos, FPOINT cameraPos, bool isLeft)
{
}
