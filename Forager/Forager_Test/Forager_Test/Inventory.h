#pragma once
#include "pch.h"

class Image;
class Item;

typedef struct tagSlot
{
	int idx;
	Image* img;
	POINT pos;
	RECT rc;
	Item* InvenItem;
}SLOT_INFO;

class Inventory
{
private:
	map<string, Item*> invenItemData;
	map<string, Item*>::iterator itInvenItem;

	Image* background;
	SLOT_INFO slot[16];

	int tempSlotIdx;		// ������ ��ġ �ٲٴ� ���� �ε��� �ӽ����� ����
	Item* relocateItem;		// ���� ��ġ �ٲٴ� ������
	int slotSize;			// ���� ũ��
	bool isRelocateItem;		// 
public:
	HRESULT Init();
	void Render(HDC hdc);

	void AddItem(Item* item);
	Item* FindItem(string key);
	void DeleteItem(string key, int cnt = 1);

	SLOT_INFO* GetSlot() { return slot; }

	int GetTempSlotIdx() { return tempSlotIdx; }
	void SetTempSlotIdx(int idx) { tempSlotIdx = idx; }

	Item* GetRelocateItem() { return relocateItem; }
	void SetRelocateItem(Item* item) { relocateItem = item; }

	bool GetIsRelocateItem() { return isRelocateItem; }
	void SetIsRelocateItem(bool isRelocateItem) {  this->isRelocateItem = isRelocateItem; }
};

