#include "Object.h"
#include "Image.h"

HRESULT Object::Init(int typeNum)
{
	frameCnt = 0;
	frameTime = 0.0f;
	isFrame = false;

	hp = ImageManager::GetSingleton()->FindImage("Object_Hp");
	hpBack = ImageManager::GetSingleton()->FindImage("Object_Hp_Back");
	return S_OK;
}

void Object::Release()
{
}

void Object::Update()
{
	UpdateFrame(0.05f);
}

void Object::Render(HDC hdc, FPOINT cameraPos)
{
	// 화면 밖이면 렌더 안하기
	if (pos.x - cameraPos.x > WINSIZE_X || pos.y - cameraPos.y > WINSIZE_Y || pos.x + 56 - cameraPos.x < 0 || pos.y + 56 - cameraPos.y < 0)
		return;

	if (currHp < maxHp)
	{
		hpBack->Render(hdc, int(pos.x + 3 - cameraPos.x), int(pos.y + 65 - cameraPos.y));
		hp->Render(hdc, int(pos.x + 6 - cameraPos.x), int(pos.y + 68 - cameraPos.y), 0, 0, (currHp * 44) / maxHp, 7);
	}
}

void Object::UpdateFrame(float time)
{
	if (!isFrame)
		return;

	frameTime += TimeManager::GetSingleton()->GetElapsedTime();

	if (frameTime >= time)
	{
		frameCnt++;

		if (frameCnt > img->GetMaxFrameX())
		{
			frameCnt = 0;
			SetIsFrame(false);
		}
		frameTime = 0.0f;
	}
}
