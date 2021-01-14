#pragma once
#include "pch.h"

class Item;
class FruitItemFactory;
class EtcFactory;

enum class ITEM_TYPE;

class ItemManager
{
private:
	static FruitItemFactory fruitItemFactory;
	static EtcFactory etcFactory;

	list<Item*> itemList;
	static list<Item*> acItemList;
	list<Item*>::iterator itItem;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc, FPOINT cameraPos);

	Item* newItem(ITEM_TYPE itemType);

	void CreateItemList(ITEM_TYPE itemType, int cnt);
	Item* PopItem(ITEM_TYPE itemType);
	void CreateAcObj(ITEM_TYPE itemType, FPOINT objPos);
	void DeleteAcObj(Item* item);

	list<Item*> GetAcItemList() { return acItemList; }
};

class FruitItemFactory : public ItemManager{};

class EtcFactory : public ItemManager{};

