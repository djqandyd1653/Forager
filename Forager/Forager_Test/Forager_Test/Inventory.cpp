#include "Inventory.h"
#include "Image.h"
#include "Item.h"

HRESULT Inventory::Init()
{
	tempSlotIdx = -1;
	relocateItem = NULL;
	slotSize = 88;
	isRelocateItem = false;

	background = ImageManager::GetSingleton()->FindImage("Inventory_Back");

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			int idx = i + 8 * j;
			slot[idx].idx = idx;
			slot[idx].img = ImageManager::GetSingleton()->FindImage("Inventory_Slot");
			slot[idx].pos = { 235 + 100 * i, 262 + 100 * j };
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
	background->AlphaRender(hdc, 0, 0, 170);
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
		item->GetImg()->Render(hdc, item->GetPos().x, item->GetPos().y);

		// ������ ����
		char c[12];
		wsprintf(c, "%d", item->GetItemCnt());
		TextOut(hdc, item->GetPos().x, item->GetPos().y, c, strlen(c));
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
			// �������� ������
		}

		// ������ ���� ��
		if (item->GetItemCnt() == 0)
		{
			item->SetInit();
			invenItemData.erase(key);
		}
	}
	else
	{
		// �������� ����
	}
}