#include "Player.h"
#include "Image.h"
#include "Animation.h"
#include "TileMapToolScene.h"
#include "WeaponManager.h"
#include "Pickaxe.h"

HRESULT Player::Init(tagTile* tile)
{
	pos.x = 1090;
	pos.y = 1090;
	sizeX = 56;
	sizeY = 56;
	speed = 300.0f;
	moveAngleX = 0.0f;
	moveAngleY = 0.0f;
	maxLife = 3;
	currLife = maxLife;
	maxStamina = 100;
	currStamina = maxStamina;
	maxEXP = 100;
	currEXP = 0;
	level = 1;
	currFrameX = 0;
	frameTime = 0.0f;
	isLeft = false;
	ableAttack = true;

	state = PLAYER_STATE::IDLE;
	
	for (int i = 0; i < static_cast<int>(PLAYER_STATE::COUNT); i++)
	{
		img[i] = new Image;
	}

	img[static_cast<int>(PLAYER_STATE::IDLE)] = ImageManager::GetSingleton()->FindImage("Player_Idle");
	img[static_cast<int>(PLAYER_STATE::RUN)] = ImageManager::GetSingleton()->FindImage("Player_Run");
	img[static_cast<int>(PLAYER_STATE::ROLL)] = ImageManager::GetSingleton()->FindImage("Player_Roll");

	//for (int i = 0; i < static_cast<int>(PLAYER_STATE::COUNT); i++)
	//{
	//	anim[i] = new Animation;
	//	anim[i]->Init(
	//		img[i]->GetWidth(),
	//		img[i]->GetHeight(),
	//		img[i]->GetFrameWidth(),
	//		img[i]->GetFrameHeight()
	//	);
	//	anim[i]->SetPlayFrame(isLeft * img[i]->GetMaxFrame() / 2, (isLeft + 1) * img[i]->GetMaxFrame() / 2, true, false);
	//	anim[i]->SetKeyFrameUpdateTime(0.1f);
	//}
	
	//anim[static_cast<int>(state)]->Start();

	this->tile = tile;
	weaponMgr = new WeaponManager;
	weaponMgr->ChangeWeapon(new Pickaxe);

	return S_OK;
}

void Player::Release()
{
	ImageManager::GetSingleton()->DeleteImg("Player_Idle");
	ImageManager::GetSingleton()->DeleteImg("Player_Run");
	SAFE_DELETE(tile);
}

void Player::Update(FPOINT cameraPos)
{
	Move();
	RectUpdate();
	DirUpdate(cameraPos);

	// 공격키 누르면 공격실행
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LBUTTON))
	{
		if(ableAttack)
			ableAttack = false;
	}
	weaponMgr->Attack(ableAttack);

	// 체력 테스트
	if (KeyManager::GetSingleton()->IsOnceKeyDown('H'))
	{
		currLife++;

		if (currLife >= maxLife)
		{
			currLife = maxLife;
		}
	}
	// 체력 테스트
	if (KeyManager::GetSingleton()->IsOnceKeyDown('J'))
	{
		currLife--;

		if (currLife <= 0)
		{
			currLife = 0;
		}
	}
	// 체력 테스트
	if (KeyManager::GetSingleton()->IsOnceKeyDown('K'))
	{
		maxLife++;
		currLife = maxLife;
	}
	// 체력 테스트
	if (KeyManager::GetSingleton()->IsOnceKeyDown('L'))
	{
		maxLife--;
		if (maxLife <= 0)
		{
			maxLife = 0;
		}
		currLife = maxLife;
	}

	// 프레임 계산
	frameTime += TimeManager::GetSingleton()->GetElapsedTime();

	if (frameTime > 0.05f)
	{
		currFrameX++;

		if (currFrameX > img[static_cast<int>(state)]->GetMaxFrameX())
		{
			currFrameX = 0;
		}

		frameTime = 0.0f;
	}
}

void Player::Render(HDC hdc, FPOINT cameraPos)
{
	int cPosX = int(-cameraPos.x);
	int cPosY = int(-cameraPos.y);

	img[static_cast<int>(state)]->FrameRender(hdc, pos.x + cPosX, pos.y + cPosY, currFrameX, isLeft);
	Rectangle(hdc, rc.left + cPosX, rc.top + cPosY, rc.right + cPosX, rc.bottom + cPosY);
	//Rectangle(hdc, pos.x + cPosX, pos.y + cPosY, pos.x + 56 + cPosX, pos.y + 56 + cPosY);
	weaponMgr->Render(hdc, pos, cameraPos, isLeft);
}

void Player::Move()
{
	moveAngleX = 0.0f;
	moveAngleY = 0.0f;

	int tileNum;
	if (KeyManager::GetSingleton()->IsStayKeyDown('W'))
	{
		tileNum = rcCenter.x / TILE_SIZE + (rc.top / TILE_SIZE) * MAP_SIZE;
		if (tile[tileNum].terrain == TERRAIN::GRASS)
		{
			if (state != PLAYER_STATE::RUN)
			{
				state = PLAYER_STATE::RUN;
				currFrameX = 0;
			}
			moveAngleY = 90.0f;
		}
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown('A'))
	{
		tileNum = rc.left / TILE_SIZE + (rcCenter.y / TILE_SIZE) * MAP_SIZE;
		if (tile[tileNum].terrain == TERRAIN::GRASS)
		{
			if (state != PLAYER_STATE::RUN)
			{
				state = PLAYER_STATE::RUN;
				currFrameX = 0;
			}
			moveAngleX = 180.0f;
		}
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown('S'))
	{
		tileNum = rcCenter.x / TILE_SIZE + (rc.bottom / TILE_SIZE) * MAP_SIZE;
		if (tile[tileNum].terrain == TERRAIN::GRASS)
		{
			if (state != PLAYER_STATE::RUN)
			{
				state = PLAYER_STATE::RUN;
				currFrameX = 0;
			}
			moveAngleY = 270.0f;
		}	
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown('D'))
	{
		tileNum = rc.right / TILE_SIZE + (rcCenter.y / TILE_SIZE) * MAP_SIZE;
		if (tile[tileNum].terrain == TERRAIN::GRASS)
		{
			if (state != PLAYER_STATE::RUN)
			{
				state = PLAYER_STATE::RUN;
				currFrameX = 0;
			}
			moveAngleX = 360.0f;
		}
	}

	if (moveAngleX != 0.0f)
		pos.x += static_cast<int>(speed * cos(DEGREE_TO_RADIAN(moveAngleX)) * TimeManager::GetSingleton()->GetElapsedTime());

	if (moveAngleY != 0.0f)
		pos.y -= static_cast<int>(speed * sin(DEGREE_TO_RADIAN(moveAngleY)) * TimeManager::GetSingleton()->GetElapsedTime());

	if (moveAngleX == 0.0f && moveAngleY == 0.0f)
	{
		if (state != PLAYER_STATE::IDLE)
		{
			state = PLAYER_STATE::IDLE;
			currFrameX = 0;
		};
	}
}

void Player::RectUpdate()
{
	rc.left = pos.x + sizeX / 4 + 4;
	rc.top = pos.y + sizeY / 2 + 5;
	rc.right = rc.left + sizeX / 2;
	rc.bottom = pos.y + sizeY;

	rcCenter = {
		(rc.right + rc.left) / 2,
		(rc.bottom + rc.top) / 2
	};
}

void Player::DirUpdate(FPOINT cameraPos)
{
	if (g_ptMouse.x + cameraPos.x < pos.x + sizeX / 2)
	{
		isLeft = true;
	}
	else 
		isLeft = false;
}

void Player::LevelUp()
{
	if (currEXP >= maxEXP)
	{
		int remainEXP = currEXP - maxEXP;
		level++;
		currEXP = remainEXP;
		maxEXP = int(maxEXP * 1.2f);
	}
}

void Player::GetEXP(int EXP)
{
	currEXP += EXP;
	LevelUp();
}
