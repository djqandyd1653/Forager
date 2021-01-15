#include "ItemManager.h"
#include "Item.h"
#include "FruitItem.h"
#include "EtcItem.h"

list<Item*> ItemManager::acItemList;
FruitItemFactory ItemManager::fruitItemFactory;
EtcFactory ItemManager::etcFactory;

HRESULT ItemManager::Init()
{
	CreateItemList(ITEM_TYPE::FRUIT, 20);
	CreateItemList(ITEM_TYPE::TREE, 20);
	CreateItemList(ITEM_TYPE::ROCK, 10);
	return E_NOTIMPL;
}

void ItemManager::Release()
{
	for (itItem = acItemList.begin(); itItem != acItemList.end(); itItem++)
	{
		if (*itItem)
		{
			(*itItem)->Release();
		}
		delete *itItem;
	}

	for (itItem = fruitItemFactory.itemList.begin(); itItem != fruitItemFactory.itemList.end(); itItem++)
	{
		if (*itItem)
		{
			(*itItem)->Release();
		}
		delete *itItem;
	}

	for (itItem = etcFactory.itemList.begin(); itItem != etcFactory.itemList.end(); itItem++)
	{
		if (*itItem)
		{
			(*itItem)->Release();
		}
		delete *itItem;
	}

	acItemList.clear();
	fruitItemFactory.itemList.clear();
	etcFactory.itemList.clear();
}

void ItemManager::Update()
{
	itItem = acItemList.begin();

	while (itItem != acItemList.end())
	{
		(*itItem)->Update();
		itItem++;
	}
}

void ItemManager::Render(HDC hdc, FPOINT cameraPos)
{
	itItem = acItemList.begin();

	while (itItem != acItemList.end())
	{
		(*itItem)->Render(hdc, cameraPos);
		itItem++;
	}
}

Item * ItemManager::newItem(ITEM_TYPE itemType)
{
	
	switch (ITEM_TYPE(itemType))
	{
	case ITEM_TYPE::FRUIT:
		return new FruitItem;
	case ITEM_TYPE::TREE:
		return new EtcItem;
	case ITEM_TYPE::ROCK:
		return new EtcItem;
	}
}

void ItemManager::CreateItemList(ITEM_TYPE itemType, int cnt)
{
	for (int i = 0; i < cnt; i++)
	{
		Item* tempItem = newItem(itemType);
		tempItem->Init(itemType);
		itemList.push_back(tempItem);
	}
}

Item * ItemManager::PopItem(ITEM_TYPE itemType)
{
	Item* tempItem;

	itItem = itemList.begin();

	if (itemList.empty())
	{
		tempItem = newItem(itemType);
		tempItem->Init(itemType);
	}
	else
	{
		tempItem = *itItem;
		itItem = acItemList.erase(itItem);
	}

	return tempItem;
}

void ItemManager::CreateAcObj(ITEM_TYPE itemType, FPOINT objPos)
{
	Item* tempItem;

	switch (itemType)
	{
	case ITEM_TYPE::FRUIT:
		tempItem = fruitItemFactory.PopItem(itemType);
		break;
	case ITEM_TYPE::TREE:
		tempItem = etcFactory.PopItem(itemType);
		break;
	case ITEM_TYPE::ROCK:
		tempItem = etcFactory.PopItem(itemType);
		break;
	}

	acItemList.push_back(tempItem);
	acItemList.back()->SetPos(objPos);
	acItemList.back()->SetRandParabola();
}

void ItemManager::DeleteAcObj(Item * item)
{
	itItem = acItemList.begin();

	while (itItem != acItemList.end())
	{
		if (item->GetPos().x == (*itItem)->GetPos().x && item->GetPos().y == (*itItem)->GetPos().y)
			break;

		itItem++;
	}

	switch (item->GetType())
	{
	case ITEM_TYPE::FRUIT:
		fruitItemFactory.itemList.push_back(*itItem);
	case ITEM_TYPE::ETC:
		etcFactory.itemList.push_back(*itItem);
	default:
		break;
	}

	(*itItem)->SetInit();
	acItemList.erase(itItem);
}
