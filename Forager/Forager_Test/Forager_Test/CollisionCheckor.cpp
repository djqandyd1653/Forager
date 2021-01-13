#include "CollisionCheckor.h"
#include "Player.h"
#include "TileMap.h"
#include "TileMapToolScene.h"
#include "ObjectFactory.h"
#include "Object.h"
#include "Camera.h"
#include "ItemManager.h"
#include "Item.h"

HRESULT CollisionCheckor::Init(Player * player, TileMap * tileMap, ObjectFactory * objFactory, ItemManager* itemMgr)
{
	this->player = player;
	this->tileMap = tileMap;
	this->objFactory = objFactory;
	this->itemMgr = itemMgr;

	tile = tileMap->GetTile();

	return S_OK;
}

void CollisionCheckor::Update(FPOINT cameraPos)
{
	CheckCollisionPO();					// 플레이어와 오브젝트 충돌검사
	CheckCollisionMO(cameraPos);		// 마우스와 오브젝트 충돌검사
	CheckCollisionIPIM(cameraPos);				// 아이템과 플레이어 또는 아이템과 마우스
}

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
							itemMgr->CreateAcObj(tile[tileNum].obj->GetItemNum(), tile[tileNum].obj->GetPos());
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

		if (PtInRect(&rc2, ptMouse))
		{
			itemMgr->DeleteAcObj(*it);
			return;
		}
		it++;
	}
}
