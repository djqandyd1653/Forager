#pragma once
#include "pch.h"

class Image;
class Item;

typedef struct tagSlot
{
	Image* img;
	POINT pos;
	RECT rc;
	bool haveItem;
}SLOT_INFO;

class Inventory
{
private:
	map<string, Item*> invenItemData;
	map<string, Item*>::iterator itInvenItem;

	Image* background;
	SLOT_INFO slot[16];

	//Image* slot[16];
	//POINT ptSlot[16];
	//RECT rcSlot[16];

	int slotSize;
public:
	HRESULT Init();
	void Render(HDC hdc);

	void AddItem(Item* item);
	Item* FindItem(string key);
	void DeleteItem(string key, int cnt = 1);
};

