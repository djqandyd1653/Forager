#include "ItemManager.h"
#include "Item.h"
#include "FruitItem.h"
#include "EtcItem.h"

list<Item*> ItemManager::acItemList;
FruitItemFactory ItemManager::fruitItemFactory;
EtcFactory ItemManager::etcFactory;

HRESULT ItemManager::Init()
{
	CreateItemList(int(ITEM_TYPE::FRUIT), 20);
	CreateItemList(int(ITEM_TYPE::TREE), 20);
	CreateItemList(int(ITEM_TYPE::ROCK), 10);
	return E_NOTIMPL;
}

void ItemManager::Release()
{
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

Item * ItemManager::newItem(int itemListNum)
{
	
	switch (ITEM_TYPE(itemListNum))
	{
	case ITEM_TYPE::FRUIT:
		return new FruitItem;
	case ITEM_TYPE::TREE:
		return new EtcItem;
	case ITEM_TYPE::ROCK:
		return new EtcItem;
	}
}

void ItemManager::CreateItemList(int itemListNum, int cnt)
{
	for (int i = 0; i < cnt; i++)
	{
		Item* tempItem = newItem(itemListNum);
		tempItem->Init(itemListNum);
		itemList.push_back(tempItem);
	}
}

Item * ItemManager::PopItem(int itemListNum)
{
	Item* tempItem;

	itItem = itemList.begin();

	if (itemList.empty())
	{
		tempItem = newItem(itemListNum);
		tempItem->Init(itemListNum);
	}
	else
	{
		tempItem = *itItem;
		itItem = acItemList.erase(itItem);
	}

	return tempItem;
}

void ItemManager::CreateAcObj(int itemListNum, FPOINT objPos)
{
	Item* tempItem;

	switch (ITEM_TYPE(itemListNum))
	{
	case ITEM_TYPE::FRUIT:
		tempItem = fruitItemFactory.PopItem(itemListNum);
		break;
	case ITEM_TYPE::TREE:
		tempItem = etcFactory.PopItem(itemListNum);
		break;
	case ITEM_TYPE::ROCK:
		tempItem = etcFactory.PopItem(itemListNum);
		break;
	}

	acItemList.push_back(tempItem);
	acItemList.back()->SetPos(objPos);
	acItemList.back()->SetIsMove(true);
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
