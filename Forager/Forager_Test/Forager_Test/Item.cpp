#include "Item.h"

HRESULT Item::Init()
{
	switch (listNum)
	{
	case ITEM_NAME_LIST::FRUIT:
		img = ImageManager::GetSingleton()->FindImage("Fruit_Item_Drop");
		break;
	case ITEM_NAME_LIST::TREE:
		img = ImageManager::GetSingleton()->FindImage("Tree_Item_Drop");
		break;
	case ITEM_NAME_LIST::ROCK:
		img = ImageManager::GetSingleton()->FindImage("Rock_Item_Drop");
		break;
	}
	return S_OK;
}

void Item::Release()
{
}

void Item::Update()
{
}

void Item::Render(HDC hdc, FPOINT cameraPos)
{
}
