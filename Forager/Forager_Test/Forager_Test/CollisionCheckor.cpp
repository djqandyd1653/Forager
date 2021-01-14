#include "PlayScene.h"
#include "CollisionCheckor.h"
#include "Player.h"
#include "TileMap.h"
#include "TileMapToolScene.h"
#include "ObjectFactory.h"
#include "Object.h"
#include "Camera.h"
#include "ItemManager.h"
#include "Item.h"
#include "Inventory.h"

HRESULT CollisionCheckor::Init(Player * player, TileMap * tileMap, ObjectFactory * objFactory, ItemManager* itemMgr, Inventory* inven)
{
	this->player = player;
	this->tileMap = tileMap;
	this->objFactory = objFactory;
	this->itemMgr = itemMgr;
	this->inven = inven;

	tile = tileMap->GetTile();

	return S_OK;
}

void CollisionCheckor::Update(FPOINT cameraPos, GAME_MODE currMode)
{
	if (currMode == GAME_MODE::PLAY)
	{
		CheckCollisionPO();					// 플레이어와 오브젝트 충돌검사
		CheckCollisionMO(cameraPos);		// 마우스와 오브젝트 충돌검사
	}
	
	if (currMode == GAME_MODE::INVENTORY)
	{
		ChekckCollisionMS(cameraPos);
	}

	CheckCollisionIPIM(cameraPos);			// 아이템과 플레이어 또는 아이템과 마우스
}

// 플레이어와 오브젝트
void CollisionCheckor::CheckCollisionPO()
{
	// 플레이어 주면 8방향 타일
	int tileNum[8];
	tileNum[0] = player->GetRcCenter().x / TILE_SIZE + (player->GetRect().top / TILE_SIZE) * MAP_SIZE;
	tileNum[1] = player->GetRect().left / TILE_SIZE + (player->GetRcCenter().y / TILE_SIZE) * MAP_SIZE;
	tileNum[2] = player->GetRcCenter().x / TILE_SIZE + (player->GetRect().bottom / TILE_SIZE) * MAP_SIZE;
	tileNum[3] = player->GetRect().right / TILE_SIZE + (player->GetRcCenter().y / TILE_SIZE) * MAP_SIZE;
	tileNum[4] = player->GetRect().left / TILE_SIZE + (player->GetRect().top / TILE_SIZE) * MAP_SIZE;
	tileNum[5] = player->GetRect().right / TILE_SIZE + (player->GetRect().top / TILE_SIZE) * MAP_SIZE;
	tileNum[6] = player->GetRect().left / TILE_SIZE + (player->GetRect().bottom / TILE_SIZE) * MAP_SIZE;
	tileNum[7] = player->GetRect().right / TILE_SIZE + (player->GetRect().bottom / TILE_SIZE) * MAP_SIZE;
	
	for (int i = 0; i < 8; i++)
	{
		if (tile[tileNum[i]].obj != nullptr)
		{
			RECT rc1 = player->GetRect();
			RECT rc2 = tile[tileNum[i]].obj->GetRect();
			RECT rcTemp;

			if (IntersectRect(&rcTemp, &rc1, &rc2))
			{
				// 위 아래
				if (rcTemp.right - rcTemp.left > rcTemp.bottom - rcTemp.top)
				{
					// 플레이어가 위
					if (rc1.top < rc2.top)
					{
						player->SetPosY(rc2.top - 56);
					}
					else
					{
						player->SetPosY(rc2.bottom - 32);
					}
				}
				// 좌 우
				else if (rcTemp.right - rcTemp.left < rcTemp.bottom - rcTemp.top)
				{
					// 플레이어가 좌
					if (rc1.left < rc2.left)
					{
						player->SetPosX(rc2.left - 48);
					}
					else
					{
						player->SetPosX(rc2.right - 18);
					}
				}
			}
		}
	}
}

// 마우스와 오브젝트
void CollisionCheckor::CheckCollisionMO(FPOINT cameraPos)
{
	POINT mousePoint = { g_ptMouse.x + int(cameraPos.x), g_ptMouse.y + int(cameraPos.y) };
	int tileNum = mousePoint.x / TILE_SIZE + ((mousePoint.y) / TILE_SIZE) * MAP_SIZE;

	if (PtInRect(&tile[tileNum].rc, mousePoint))
	{
		if (tile[tileNum].obj != nullptr && tile[tileNum].terrain == TERRAIN::GRASS)
		{
			/* 
				타일에 타겟 이미지 출력하도록 설정 변경
			*/

			if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LBUTTON))
			{
				if (player->AbleAttack())
				{ 
					double distance = sqrt(pow((mousePoint.x - player->GetRcCenter().x), 2) + pow((mousePoint.y - player->GetRcCenter().y), 2));
					if (distance <= 100.0f)
					{
						tile[tileNum].obj->SetIsFrame(true);
						tile[tileNum].obj->GetDamage(1);

						if (tile[tileNum].obj->GetCurrHp() <= 0)
						{
							int exp = tile[tileNum].obj->GiveEXP();
							player->GetEXP(exp);
							itemMgr->CreateAcObj(tile[tileNum].obj->GetItemType(), tile[tileNum].obj->GetPos());
							objFactory->DeleteAcObj(tile[tileNum].obj);
							tile[tileNum].obj->SetPos({ 0.0f, 0.0f });
							tile[tileNum].obj->SetCurrHp(tile[tileNum].obj->GetMaxHp());
							tile[tileNum].obj = nullptr;
							tile[tileNum].ableBuild = true;
						}
					}
				}
			}
		}
	}
}

// 마우스와 아이템, 플레이어와 아이템
void CollisionCheckor::CheckCollisionIPIM(FPOINT cameraPos)
{
	list<Item*> itemList = itemMgr->GetAcItemList();
	int a = itemList.size();
	list<Item*>::iterator it = itemList.begin();
	
	while (it != itemList.end())
	{
		RECT rc1 = player->GetRect();
		RECT rc2 = (*it)->GetRect();
		POINT ptMouse = { g_ptMouse.x + int(cameraPos.x), g_ptMouse.y + int(cameraPos.y) };

		if (PtInRect(&rc2, ptMouse) || 
			!(rc1.right < rc2.left || rc1.left > rc2.right ||
			rc1.top > rc2.bottom || rc1.bottom < rc2.top))
		{
			itemMgr->DeleteAcObj(*it);
			inven->AddItem(*it);
			return;
		}
		it++;
	}
}

// 마우스와 인벤토리 슬롯
void CollisionCheckor::ChekckCollisionMS(FPOINT cameraPos)
{
	SLOT_INFO* slot = inven->GetSlot();

	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < 16; i++)
		{
			if (slot[i].InvenItem == NULL)
				continue;
			if (PtInRect(&slot[i].rc, g_ptMouse))
			{
				inven->SetRelocateItem(slot[i].InvenItem);
				inven->SetTempSlotIdx(slot[i].idx);
			}
		}

	}

	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LBUTTON))
	{
		inven->SetIsRelocateItem(true);
	}

	if (inven->GetIsRelocateItem())
	{
		if (!inven->GetRelocateItem())
			return;
		Item* item = inven->GetRelocateItem();
		item->SetPos({ float(g_ptMouse.x), float(g_ptMouse.y) });
	}

	if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_LBUTTON))
	{
		inven->SetIsRelocateItem(false);
		if (inven->GetRelocateItem() == NULL)
			return;

		for (int i = 0; i < 16; i++)
		{
			if (PtInRect(&slot[i].rc, g_ptMouse))
			{
				int idx = inven->GetTempSlotIdx();

				Item* tempItem = slot[i].InvenItem;
				slot[i].InvenItem = slot[idx].InvenItem;
				slot[idx].InvenItem = tempItem;
				
				if(slot[idx].InvenItem)
					slot[idx].InvenItem->SetPos({ float(slot[idx].pos.x + 10), float(slot[idx].pos.y + 10) });
				slot[i].InvenItem->SetPos({ float(slot[i].pos.x + 10), float(slot[i].pos.y + 10) });
				inven->SetTempSlotIdx(-1);
				inven->SetRelocateItem(NULL);
				break;
			}

			if (i == 15)
			{
				Item* item = inven->GetRelocateItem();
				int idx = inven->GetTempSlotIdx();
				item->SetPos({ float(slot[idx].pos.x + 10), float(slot[idx].pos.y + 10) });
				inven->SetTempSlotIdx(-1);
				inven->SetRelocateItem(NULL);
			}
		}
	}

	//for (int i = 0; i < 16; i++)
	//{
	//	if (slot[i].InvenItem == NULL)
	//		continue;

	//	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LBUTTON))
	//	{
	//		if (PtInRect(&slot[i].rc, g_ptMouse))
	//		{
	//			inven->SetIsRelocateItem(true);
	//			slot[i].InvenItem->SetPos({ float(g_ptMouse.x + 10), float(g_ptMouse.y + 10)});
	//		}
	//	}

	//	if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_LBUTTON))
	//	{
	//		if (PtInRect(&slot[i].rc, g_ptMouse))
	//		{
	//			inven->SetIsRelocateItem(false);
	//			slot[i].InvenItem->SetPos({float(slot[i].pos.x + 10), float(slot[i].pos.y + 10)});
	//		}
	//	}
	//}
}