#include "Object.h"

HRESULT Object::Init(int typeNum)
{
	return S_OK;
}

void Object::Release()
{
}

void Object::Update()
{
}

void Object::Render(HDC hdc, FPOINT cameraPos)
{
	// 화면 밖이면 렌더 안하기
	if (pos.x - cameraPos.x > WINSIZE_X || pos.y - cameraPos.y > WINSIZE_Y || pos.x + 56 - cameraPos.x < 0 || pos.y + 56 - cameraPos.y < 0)
		return;
}
