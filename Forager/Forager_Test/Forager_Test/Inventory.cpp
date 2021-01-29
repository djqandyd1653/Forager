#include "Inventory.h"
#include "Image.h"
#include "Item.h"
#include "Menu.h"
#include "TextUI.h"

HRESULT Inventory::Init()
{
	relocateItem = NULL;
	itemCntTxt = new TextUI;

	tempSlotIdx = -1;
	slotSize = 88;
	isRelocateItem = false;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			int idx = i + 8 * j;
			slot[idx].idx = idx;
			slot[idx].img = ImageManager::GetSingleton()->FindImage("Inventory_Slot");
			slot[idx].pos = { 237 + 100 * i, 262 + 100 * j };
			slot[idx].rc.left = slot[idx].pos.x;
			slot[idx].rc.top = slot[idx].pos.y;
			slot[idx].rc.right = slot[idx].pos.x + slotSize;
			slot[idx].rc.bottom = slot[idx].pos.y + slotSize;
			slot[idx].InvenItem = NULL;
		}
	}
	
	return S_OK;
}

void Inventory::Render(HDC hdc)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			int idx = i + 8 * j;
			//Rectangle(hdc, slot[idx].rc.left, slot[idx].rc.top, slot[idx].rc.right, slot[idx].rc.bottom);
			slot[idx].img->Render(hdc, slot[idx].pos.x, slot[idx].pos.y);
		}	
	}

	if (invenItemData.empty())
		return;

	itInvenItem = invenItemData.begin();

	while (itInvenItem != invenItemData.end())
	{
		Item* item = (*itInvenItem).second;
		item->GetImg()->Render(hdc, int(item->GetPos().x), int(item->GetPos().y));

		// 아이템 개수
		itemCntTxt->SetText(to_string(item->GetItemCnt()));
		itemCntTxt->SetFontSize(27);
		itemCntTxt->SetAlign(TA_RIGHT);
		itemCntTxt->SetColor(RGB(255, 255, 255));
		itemCntTxt->Render(hdc, item->GetPos().x + 65, item->GetPos().y + 25);

		itInvenItem++;
	}
}

void Inventory::AddItem(Item* item)
{
	string key = item->GetItemKey();
	Item* tempItem = FindItem(key);

	if (tempItem)
	{
		int cnt = item->GetItemCnt();
		tempItem->PlusItemCnt(cnt);
	}
	else
	{
		invenItemData.insert(make_pair(key, item));

		for (int i = 0; i < 16; i++)
		{
			if (slot[i].InvenItem == NULL)
			{
				slot[i].InvenItem = invenItemData[key];
				invenItemData[key]->SetPos({ float(slot[i].pos.x + 10), float(slot[i].pos.y + 10) });
				invenItemData[key]->SetItemCnt(1);
				invenItemData[key]->SetInvenImg();
				break;
			}
		}
	}
}

Item* Inventory::FindItem(string key)
{
	itInvenItem = invenItemData.find(key);

	while (itInvenItem != invenItemData.end())
	{
		return itInvenItem->second;
	}

	return NULL;
}

void Inventory::DeleteItem(string key, int cnt)
{
	Item* item = FindItem(key);

	if (item)
	{
		if(item->GetItemCnt() >= cnt)
			item->MinusItemCnt(cnt);
		else
		{
			// 아이템이 부족함
		}

		// 아이템 빼기 후
		if (item->GetItemCnt() == 0)
		{
			item->SetInit();
			invenItemData.erase(key);
		}
	}
	else
	{
		// 아이템이 없음
	}
}
