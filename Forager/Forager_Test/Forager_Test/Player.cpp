#include "Player.h"
#include "Image.h"
#include "Animation.h"

HRESULT Player::Init()
{
	pos.x = WINSIZE_X / 2;
	pos.y = WINSIZE_Y / 2;
	sizeX = 56;
	sizeY = 56;
	rc.left = pos.x;
	rc.top = pos.y;
	rc.right = pos.x + sizeX;
	rc.bottom = pos.y + sizeY;
	speed = 300.0f;
	moveAngleX = 0.0f;
	moveAngleY = 0.0f;
	life = 3;
	stamina = 100.0f;
	currFrameX = 0;
	frameTime = 0.0f;
	isLeft = false;

	state = PLAYER_STATE::IDLE;
	
	for (int i = 0; i < static_cast<int>(PLAYER_STATE::COUNT); i++)
	{
		img[i] = new Image;
	}
	
	img[static_cast<int>(PLAYER_STATE::IDLE)] = ImageManager::GetSingleton()->FindImage("Player_Idle");
	img[static_cast<int>(PLAYER_STATE::RUN)] = ImageManager::GetSingleton()->FindImage("Player_Run");
	img[static_cast<int>(PLAYER_STATE::ROLL)] = ImageManager::GetSingleton()->FindImage("Player_Roll");


	for (int i = 0; i < static_cast<int>(PLAYER_STATE::COUNT); i++)
	{
		anim[i] = new Animation;
		anim[i]->Init(
			img[i]->GetWidth(),
			img[i]->GetHeight(),
			img[i]->GetFrameWidth(),
			img[i]->GetFrameHeight()
		);
		anim[i]->SetPlayFrame(isLeft * img[i]->GetMaxFrame() / 2, (isLeft + 1) * img[i]->GetMaxFrame() / 2, true, false);
		anim[i]->SetKeyFrameUpdateTime(0.1f);
	}
	
	
	//anim[static_cast<int>(state)]->Start();

	return S_OK;
}

void Player::Release()
{
	ImageManager::GetSingleton()->DeleteImg("Player_Idle");
	ImageManager::GetSingleton()->DeleteImg("Player_Run");
}

void Player::Update()
{
	Move();
	RectUpdate();
	DirUpdate();

	if (KeyManager::GetSingleton()->IsOnceKeyDown('K'))
	{
		if (state != PLAYER_STATE::IDLE)
		{
			anim[static_cast<int>(state)]->Stop();
			state = PLAYER_STATE::IDLE;
			anim[static_cast<int>(state)]->Start();
		}
	}

	if (KeyManager::GetSingleton()->IsOnceKeyDown('L'))
	{
		if (state != PLAYER_STATE::RUN)
		{
			anim[static_cast<int>(state)]->Stop();
			state = PLAYER_STATE::RUN;
			anim[static_cast<int>(state)]->Start();
		}
	}

	if (KeyManager::GetSingleton()->IsOnceKeyDown('J'))
	{
		if (state != PLAYER_STATE::ROLL)
		{
			anim[static_cast<int>(state)]->Stop();
			state = PLAYER_STATE::ROLL;
			anim[static_cast<int>(state)]->Start();
		}
	}

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


	//anim[static_cast<int>(state)]->UpdateFrame();
}

void Player::Render(HDC hdc)
{
	//img[static_cast<int>(state)]->AnimationRender(hdc, pos.x, pos.y, anim[static_cast<int>(state)]);
	img[static_cast<int>(state)]->FrameRender(hdc, pos.x, pos.y, currFrameX, isLeft);
	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
}

void Player::Move()
{
	moveAngleX = 0.0f;
	moveAngleY = 0.0f;

	if (KeyManager::GetSingleton()->IsStayKeyDown('W'))
	{
		if (state != PLAYER_STATE::RUN)
		{
			state = PLAYER_STATE::RUN;
			currFrameX = 0;
		}
		moveAngleY = 90.0f;
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown('A'))
	{
		if (state != PLAYER_STATE::RUN)
		{
			state = PLAYER_STATE::RUN;
			currFrameX = 0;
		}
		moveAngleX = 180.0f;
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown('S'))
	{
		if (state != PLAYER_STATE::RUN)
		{
			state = PLAYER_STATE::RUN;
			currFrameX = 0;
		}
		moveAngleY = 270.0f;
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown('D'))
	{
		if (state != PLAYER_STATE::RUN)
		{
			state = PLAYER_STATE::RUN;
			currFrameX = 0;
		}
		moveAngleX = 360.0f;
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
}

void Player::DirUpdate()
{
	if (g_ptMouse.x < pos.x + sizeX / 2)
	{
		isLeft = true;
	}
	else 
		isLeft = false;
}
