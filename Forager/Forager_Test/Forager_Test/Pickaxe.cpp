#include "Pickaxe.h"
#include "Image.h"

HRESULT Pickaxe::Init()
{
	Weapon::Init();
	frameDelayTime = 0.1f;

	img = ImageManager::GetSingleton()->FindImage("Pickaxe");

	return S_OK;
}

void Pickaxe::Release()
{
}

void Pickaxe::Update()
{
}

void Pickaxe::Render(HDC hdc, POINT playerPos, FPOINT cameraPos, bool isLeft)
{
	img->FrameRender(hdc, int(playerPos.x - cameraPos.x), int(playerPos.y - cameraPos.y), currFrameCnt, isLeft);
}

void Pickaxe::Attack(bool &ableAttack)
{
	if (!ableAttack)
	{
		currFrameTime += TimeManager::GetSingleton()->GetElapsedTime();

		if (currFrameTime > frameDelayTime)
		{
			currFrameCnt += nextFrameDir;
			if (currFrameCnt == img->GetMaxFrameX())
				nextFrameDir = -1;

			currFrameTime = 0.0f;
		}

		if (currFrameCnt == 0 && nextFrameDir == -1)
		{
			nextFrameDir = 1;
			ableAttack = true;
		}
			
	}

}
