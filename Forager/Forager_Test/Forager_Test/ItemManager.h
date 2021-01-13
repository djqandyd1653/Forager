#pragma once
#include "pch.h"

class Item;
class FruitItemFactory;
class EtcFactory;

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

	Item* newItem(int itemListNum);

	void CreateItemList(int itemListNum, int cnt);
	Item* PopItem(int itemListNum);
	void CreateAcObj(int itemListNum, FPOINT objPos);
	void DeleteAcObj(Item* item);

	list<Item*> GetAcItemList() { return acItemList; }
};

class FruitItemFactory : public ItemManager{};

class EtcFactory : public ItemManager{};

