#include "Fruit.h"
#include "Image.h"
#include "Item.h"

HRESULT Fruit::Init(int typeNum)
{
	Object::Init(typeNum);
	img = ImageManager::GetSingleton()->FindImage("Fruit");
	this->typeNum = typeNum;
	itemType = ITEM_TYPE::FRUIT;
	maxHp = 2;
	currHp = maxHp;
	EXP = 20; // 3

	return S_OK;
}

void Fruit::Release()
{
}

void Fruit::Render(HDC hdc, FPOINT cameraPos)
{
	Object::Render(hdc, cameraPos);
	img->FrameRender(hdc, int(pos.x - cameraPos.x), int(pos.y - cameraPos.y), frameCnt, 0);
	//Rectangle(hdc, rc.left - cameraPos.x, rc.top - cameraPos.y, rc.right - cameraPos.x, rc.bottom - cameraPos.y);
}

void Fruit::UpdateRect()
{
	rc.left = LONG(pos.x + 5);
	rc.top = LONG(pos.y + 10);
	rc.right = LONG(pos.x + 51);
	rc.bottom = LONG(pos.y + 56);
}
