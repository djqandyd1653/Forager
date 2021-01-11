#include "Rock.h"
#include "Image.h"

HRESULT Rock::Init(int typeNum)
{
	Object::Init(typeNum);
	img = ImageManager::GetSingleton()->FindImage("Rock");
	this->typeNum = typeNum;
	maxHp = 5;
	currHp = maxHp;

	return S_OK;
}

void Rock::Release()
{
}

void Rock::Render(HDC hdc, FPOINT cameraPos)
{
	Object::Render(hdc, cameraPos);
	img->FrameRender(hdc, int(pos.x - cameraPos.x), int(pos.y - cameraPos.y), frameCnt, 0);
	//Rectangle(hdc, rc.left - cameraPos.x, rc.top - cameraPos.y, rc.right - cameraPos.x, rc.bottom - cameraPos.y);
}

void Rock::UpdateRect()
{
	rc.left = pos.x + 5;
	rc.top = pos.y + 5;
	rc.right = pos.x + 51;
	rc.bottom = pos.y + 56;
}
