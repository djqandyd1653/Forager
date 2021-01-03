#include "Player.h"
#include "Image.h"
#include "Animation.h"

HRESULT Player::Init()
{
	pos.x = 0;
	pos.y = 0;
	rc.left = pos.x;
	rc.top = pos.y;
	rc.right = pos.x + size;
	rc.bottom = pos.y + size;
	speed = 370.0f;
	life = 3;
	stamina = 100.0f;

	state = PLAYER_STATE::RUN;
	
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
		anim[i]->SetPlayFrame(true, false);
		anim[i]->SetKeyFrameUpdateTime(0.02f);
	}
	
	
	anim[static_cast<int>(state)]->Start();

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

	anim[static_cast<int>(state)]->UpdateFrame();
}

void Player::Render(HDC hdc)
{
	img[static_cast<int>(state)]->AnimationRender(hdc, pos.x, pos.y, anim[static_cast<int>(state)]);
	//img[static_cast<int>(state)]->FrameRender(hdc, rc.left, rc.top, currFrameX, currFrameY);
}

void Player::Move()
{
	if (KeyManager::GetSingleton()->IsStayKeyDown('W'))
	{
		state = PLAYER_STATE::RUN;
		pos.y -= static_cast<int>(speed * TimeManager::GetSingleton()->GetElapsedTime());
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown('A'))
	{
		state = PLAYER_STATE::RUN;
		pos.x -= static_cast<int>(speed * TimeManager::GetSingleton()->GetElapsedTime());
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown('S'))
	{
		state = PLAYER_STATE::RUN;
		pos.y += static_cast<int>(speed * TimeManager::GetSingleton()->GetElapsedTime());
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown('D'))
	{
		state = PLAYER_STATE::RUN;
		pos.x += static_cast<int>(speed * TimeManager::GetSingleton()->GetElapsedTime());
	}
}

void Player::RectUpdate()
{
	rc.left = pos.x;
	rc.top = pos.y;
	rc.right = pos.x + size;
	rc.bottom = pos.y + size;
}
