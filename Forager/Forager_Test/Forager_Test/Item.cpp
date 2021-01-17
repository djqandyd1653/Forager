#include "Item.h"
#include "Image.h"

HRESULT Item::Init(ITEM_TYPE itemType)
{
	switch (itemType)
	{
	case ITEM_TYPE::FRUIT:
		dropImg = ImageManager::GetSingleton()->FindImage("Fruit_Item_Drop");
		invenImg = ImageManager::GetSingleton()->FindImage("Fruit_Item");
		itemKey = "Fruit";
		break;
	case ITEM_TYPE::TREE:
		dropImg = ImageManager::GetSingleton()->FindImage("Tree_Item_Drop");
		invenImg = ImageManager::GetSingleton()->FindImage("Tree_Item");
		itemKey = "Tree";
		break;
	case ITEM_TYPE::ROCK:
		dropImg = ImageManager::GetSingleton()->FindImage("Rock_Item_Drop");
		invenImg = ImageManager::GetSingleton()->FindImage("Rock_Item");
		itemKey = "Rock";
		break;
	}

	img = dropImg;

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
		
		if (pos.y >= destPos.y)
		{
			isMove = false;

			rc.left = LONG(pos.x);
			rc.top = LONG(pos.y);
			rc.right = LONG(pos.x + 56);
			rc.bottom = LONG(pos.y + 56);
		}		
	}
}

void Item::Render(HDC hdc, FPOINT cameraPos)
{
	// 화면 밖이면 렌더 X
	if (pos.x - cameraPos.x > WINSIZE_X || pos.y - cameraPos.y > WINSIZE_Y || pos.x + 56 - cameraPos.x < 0 || pos.y + 56 - cameraPos.y < 0)
		return;

	img->Render(hdc, int(pos.x - cameraPos.x), int(pos.y - cameraPos.y));
	Rectangle(hdc, int(rc.left - cameraPos.x), int(rc.top - cameraPos.y), int(rc.right - cameraPos.x), int(rc.bottom - cameraPos.y));
}

void Item::UseItem()
{
}
