#pragma once
#include "pch.h"

enum class GAME_MODE;
class Image;
class Item;
class TextUI;

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

	Item* relocateItem;		// ���� ��ġ �ٲٴ� ������
	TextUI* itemCntTxt;		// ������ ���� �ؽ�Ʈ

	int tempSlotIdx;		// ������ ��ġ �ٲٴ� ���� �ε��� �ӽ����� ����
	int slotSize;			// ���� ũ��
	bool isRelocateItem;	// ������ ��ġ�� �ٲ���°�

	
public:
	HRESULT Init();
	void Render(HDC hdc);

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

