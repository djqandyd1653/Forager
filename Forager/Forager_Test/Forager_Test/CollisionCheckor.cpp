#include "CollisionCheckor.h"
#include "Player.h"
#include "TileMap.h"
#include "TileMapToolScene.h"
#include "ObjectFactory.h"
#include "Object.h"
#include "Camera.h"

HRESULT CollisionCheckor::Init(Player * player, TileMap * tileMap, ObjectFactory * objFactory)
{
	this->player = player;
	this->tileMap = tileMap;
	this->objFactory = objFactory;

	tile = tileMap->GetTile();

	return S_OK;
}

void CollisionCheckor::Update(FPOINT cameraPos)
{
	CheckCollisionPO();		// �÷��̾�� ������Ʈ �浹�˻�
	CheckCollisionMO(cameraPos);		// ���콺�� ������Ʈ �浹�˻�
}

void CollisionCheckor::CheckCollisionPO()
{
	// �÷��̾� �ָ� 8���� Ÿ��
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
				// �� �Ʒ�
				if (rcTemp.right - rcTemp.left > rcTemp.bottom - rcTemp.top)
				{
					// �÷��̾ ��
					if (rc1.top < rc2.top)
					{
						player->SetPosY(rc2.top - 56);
					}
					else
					{
						player->SetPosY(rc2.bottom - 32);
					}
				}
				// �� ��
				else if (rcTemp.right - rcTemp.left < rcTemp.bottom - rcTemp.top)
				{
					// �÷��̾ ��
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
	POINT mousePoint = { g_ptMouse.x + cameraPos.x, g_ptMouse.y + cameraPos.y };
	int tileNum = mousePoint.x / TILE_SIZE + ((mousePoint.y) / TILE_SIZE) * MAP_SIZE;

	if (PtInRect(&tile[tileNum].rc, mousePoint))
	{
		if (tile[tileNum].obj != nullptr && tile[tileNum].terrain == TERRAIN::GRASS)
		{
			/* 
				Ÿ�Ͽ� Ÿ�� �̹��� ����ϵ��� ���� ����
			*/

			if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LBUTTON))
			{
				//if (player->AbleAttack())
				//{
					tile[tileNum].obj->SetIsFrame(true);
					tile[tileNum].obj->SetRemainHp(1);

					if (tile[tileNum].obj->GetCurrHp() <= 0)
					{
						objFactory->DeleteAcObj(tile[tileNum].obj);
						tile[tileNum].obj->SetPos({ 0.0f, 0.0f });
						tile[tileNum].obj->SetCurrHp(tile[tileNum].obj->GetMaxHp());
						tile[tileNum].obj = nullptr;
					}
				//}
			}
		}
	}
}