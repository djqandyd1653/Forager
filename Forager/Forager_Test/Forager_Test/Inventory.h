#pragma once
#include "pch.h"

enum class GAME_MODE;
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

	SLOT_INFO slot[16];

	int tempSlotIdx;		// 아이템 위치 바꾸는 슬롯 인덱스 임시저장 변수
	Item* relocateItem;		// 슬롯 위치 바꾸는 아이템
	int slotSize;			// 슬롯 크기
	bool isRelocateItem;		// 
public:
	HRESULT Init();
	void Render(HDC hdc, GAME_MODE& currMode);

	void AddItem(Item* item);
	Item* FindItem(string key);
	void DeleteItem(string key, int cnt = 1);

	map<string, Item*> GetInvenItDate() { return invenItemData; }

	SLOT_INFO* GetSlot() { return slot; }

	int GetTempSlotIdx() { return tempSlotIdx; }
	void SetTempSlotIdx(int idx) { tempSlotIdx = idx; }

	Item* GetRelocateItem() { return relocateItem; }
	void SetRelocateItem(Item* item) { relocateItem = item; }

	bool GetIsRelocateItem() { return isRelocateItem; }
	void SetIsRelocateItem(bool isRelocateItem) {  this->isRelocateItem = isRelocateItem; }
};

