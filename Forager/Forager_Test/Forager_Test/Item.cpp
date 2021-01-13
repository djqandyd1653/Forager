#include "Item.h"
#include "Image.h"

HRESULT Item::Init(int listNum)
{
	switch (ITEM_TYPE(listNum))
	{
	case ITEM_TYPE::FRUIT:
		img = ImageManager::GetSingleton()->FindImage("Fruit_Item_Drop");
		break;
	case ITEM_TYPE::TREE:
		img = ImageManager::GetSingleton()->FindImage("Tree_Item_Drop");
		break;
	case ITEM_TYPE::ROCK:
		img = ImageManager::GetSingleton()->FindImage("Rock_Item_Drop");
		break;
	}

	SetInit();

	return S_OK;
}

void Item::Release()
{
}

void Item::Update()
{
	if (isMove)
	{
		pos.x += dir * 50 * TimeManager::GetSingleton()->GetElapsedTime();
		pos.y = incline * pow(pos.x - destPos.x + 56 - dir * 15, 2) + destPos.y - 56 - maxHeight;
		
		if(pos.y >= destPos.y)
			isMove = false;
	}
}

void Item::Render(HDC hdc, FPOINT cameraPos)
{
	img->Render(hdc, int(pos.x - cameraPos.x), int(pos.y - cameraPos.y));
}

void Item::UseItem()
{
}
