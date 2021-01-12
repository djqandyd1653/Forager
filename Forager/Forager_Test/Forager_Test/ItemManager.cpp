#include "ItemManager.h"
#include "Item.h"
#include "ConsumItem.h"
#include "EtcItem.h"

list<Item*> ItemManager::acItemList;
ConsumFactory ItemManager::consumFactory;
EtcFactory ItemManager::etcFactory;

HRESULT ItemManager::Init()
{
	CreateItemList(int(ITEM_TYPE::CONSUM), 20);
	CreateItemList(int(ITEM_TYPE::ETC), 20);
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
	case ITEM_TYPE::CONSUM:
		return new ConsumItem;
		break;
	case ITEM_TYPE::ETC:
		return new EtcItem;
		break;
	}
}

void ItemManager::CreateItemList(int itemListNum, int cnt)
{
	for (int i = 0; i < cnt; i++)
	{
		Item* tempItem = newItem(itemListNum);
		tempItem->Init();
		itemList.push_back(tempItem);
	}
}
