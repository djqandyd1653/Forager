#include "PlayScene.h"
#include "GameNode.h"
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
#include "Menu.h"
#include "BuildManager.h"

HRESULT CollisionCheckor::Init(Player * player, TileMap * tileMap, ObjectFactory * objFactory, ItemManager* itemMgr, Inventory* inven, Menu* menu, BuildManager* buildMgr, multimap<int, GameNode*>* map)
{
	this->player = player;
	this->tileMap = tileMap;
	this->objFactory = objFactory;
	this->itemMgr = itemMgr;
	this->inven = inven;
	this->menu = menu;
	this->buildMgr = buildMgr;
	renderMap = map;

	tile = tileMap->GetTile();

	return S_OK;
}

void CollisionCheckor::Update(FPOINT cameraPos)
{
	if (menu->GetCurrMode() == GAME_MODE::PLAY)
	{
		CheckCollisionPO();					// 플레이어와 오브젝트 충돌검사
		CheckCollisionMO(cameraPos);		// 마우스와 오브젝트 충돌검사
	}

	if (menu->GetCurrMode() == GAME_MODE::INVENTORY)
		ChekckCollisionMS();

	if (menu->GetCurrMode() == GAME_MODE::BUILD)
	{
		CheckCreateBuilding(cameraPos);
		CheckCollisionMT(cameraPos);
		CheckCollisionMBB();
	}
		

	//if (currMode == GAME_MODE::LAND_PURCHASSE)
	//if (currMode == GAME_MODE::SETTING)

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
							
							multimap<int, GameNode*>::iterator itTemp = (*renderMap).begin();

							while (itTemp != (*renderMap).end())
							{
								if (tile[tileNum].obj == (*itTemp).second)
								{
									(*renderMap).erase(itTemp);
									break;
								}

								itTemp++;
							}

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
void CollisionCheckor::ChekckCollisionMS()
{
	SLOT_INFO* slot = inven->GetSlot();

	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
	{
		CheckCollisionMB();

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
}

// 마우스와 메뉴버튼 충돌검사
void CollisionCheckor::CheckCollisionMB()
{
	MENU_BUTTON_INFO* button = menu->GetMenuButton();

	for (int i = 1; i < 3; i++)
	{
		if (PtInRect(&button[i].rc, g_ptMouse))
		{
			menu->SetLastMode();
			menu->SetCurrMode(GAME_MODE(i));
			changeMode = true;
			if (i == 1)
			{
				buildMgr->SetSelectBuild(false);
			}
			break;
		}
	}
}

// 마우스와 건설메뉴버튼 충돌검사
void CollisionCheckor::CheckCollisionMBB()
{
	BUILD_BUTTON_INFO* button = buildMgr->GetBuildButton();

	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
	{
		CheckCollisionMB();

		for (int i = 0; i < 3; i++)
		{
			if (PtInRect(&button[i].rc, g_ptMouse))
			{
				// 조건 추가(재료가 다 있으면)
				map<string, int>::iterator itTemp = button[i].material.begin();
				map<string, Item*> itInven = inven->GetInvenItDate();

				if (!itInven.empty())
				{
					while (itTemp != button[i].material.end())
					{
						string key = (*itTemp).first;
						int cnt = (*itTemp).second;

						if (itInven[key] == nullptr || itInven[key]->GetItemCnt() < cnt)
						{
							buildMgr->SetSelectBuild(false);
							break;
						}
						else
						{
							buildMgr->SetSelectBuild(true);
							buildMgr->SetBuildKey(button[i].buildingKey);
						}

						itTemp++;
					}
				}
			}
		}
	}
}

// 마우스와 타일 (건물 설치 가능지역인지 아닌지)
void CollisionCheckor::CheckCollisionMT(FPOINT cameraPos)
{
	if (buildMgr->GetSelectBuild())
	{
		tagTile* tile = tileMap->GetTile();
		POINT mousePoint = { int(g_ptMouse.x + cameraPos.x), int(g_ptMouse.y + cameraPos.y) };
		int num = mousePoint.x / TILE_SIZE + (mousePoint.y / TILE_SIZE) * MAP_SIZE;

		buildMgr->SetRenderPos({ int(tile[num].rc.left - cameraPos.x), int(tile[num].rc.top - cameraPos.y) });

		if (tile[num].ableBuild && tile[num + 1].ableBuild &&
			tile[num + MAP_SIZE].ableBuild && tile[num + MAP_SIZE + 1].ableBuild)
		{
			RECT rc1 = player->GetRect();
			RECT rc2 = { tile[num].rc.left, tile[num].rc.top, tile[num + MAP_SIZE + 1].rc.right, tile[num + MAP_SIZE + 1].rc.bottom };
			RECT rc3;

			if (IntersectRect(&rc3, &rc1, &rc2))
			{
				buildMgr->SetAbleBuild(false);
			}
			else
				buildMgr->SetAbleBuild(true);
		}
		else
		{
			buildMgr->SetAbleBuild(false);
		}
	}
}

void CollisionCheckor::CheckCreateBuilding(FPOINT cameraPos)
{
	if (buildMgr->GetAbleBuild())
	{
		if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
		{
			tagTile* tile = tileMap->GetTile();
			POINT mousePoint = { int(g_ptMouse.x + cameraPos.x), int(g_ptMouse.y + cameraPos.y) };
			int num = mousePoint.x / TILE_SIZE + (mousePoint.y / TILE_SIZE) * MAP_SIZE;

			// 건물생성 (create함수)
			GameNode* building = buildMgr->CreateAcBuilding( {tile[num].rc.left, tile[num].rc.top});

			// 건물 렌더맵에 추가
			(*renderMap).insert(make_pair(tile[num].rc.top, building));

			// 타일 건설불가지역으로 지정
			tile[num].ableBuild = false;
			tile[num + 1].ableBuild = false;
			tile[num + MAP_SIZE].ableBuild = false;
			tile[num + MAP_SIZE + 1].ableBuild = false;

			buildMgr->SetAbleBuild(false);
			buildMgr->SetSelectBuild(false);

			// 인벤토리 아이템 제거

			// 메뉴 끄기
		}
	}
}
