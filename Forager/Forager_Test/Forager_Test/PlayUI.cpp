#include "PlayUI.h"
#include "Image.h"
#include "Player.h"
#include "TextUI.h"

HRESULT PlayUI::Init(Player * player)
{
	this->player = player;
	levelText = new TextUI;

	isBack = false;
	lifeFrameX = 0;
	lifeFrameTime = 0.0f;
	cnt = 1;

	EXP[0] = ImageManager::GetSingleton()->FindImage("EXP_Bar");
	EXP[1] = ImageManager::GetSingleton()->FindImage("EXP_Back");
	life[0] = ImageManager::GetSingleton()->FindImage("Life"); 
	life[1] = ImageManager::GetSingleton()->FindImage("Life_Back");
	stamina[0] = ImageManager::GetSingleton()->FindImage("Stamina");
	stamina[1] = ImageManager::GetSingleton()->FindImage("Stamina_Back");

	
	return S_OK;
}

void PlayUI::Release()
{
	delete levelText;
}

void PlayUI::Update()
{
	lifeFrameTime += TimeManager::GetSingleton()->GetElapsedTime();

	if (lifeFrameTime > 0.2f)
	{
		lifeFrameX += cnt;

		if (lifeFrameX >= 5 || lifeFrameX <= 0)
			cnt *= -1;
		lifeFrameTime = 0.0f;
	}
}

void PlayUI::Render(HDC hdc)
{
	// EXP
	EXP[1]->Render(hdc, 242, 3);
	EXP[0]->Render(hdc, 246, 7, 0, 0, (player->GetCurrEXP() * 792) / player->GetMaxEXP(), 22);

	// level and EXP text
	levelText->SetText("���� " + to_string(player->GetLevel()) + " ( " + to_string(player->GetCurrEXP()) + " / " + to_string(player->GetMaxEXP()) + " )");
	levelText->SetFontSize(22);
	levelText->SetColor(RGB(0, 0, 0));
	levelText->Render(hdc, 579, 7);
	levelText->Render(hdc, 581, 7);
	levelText->Render(hdc, 580, 8);
	levelText->Render(hdc, 580, 6);
	levelText->SetColor(RGB(255, 255, 255));
	levelText->Render(hdc, 580, 7);
	//char cc[256];
	//wsprintf(cc, "���� %d ( %d / %d )", player->GetLevel(), player->GetCurrEXP(), player->GetMaxEXP());
	//TextOut(hdc, 580, 7, cc, strlen(cc));

	// Life
	for (int i = 0; i < player->GetMaxLife(); i++)
	{
		if (i < player->GetCurrLife() - 1)
			life[0]->Render(hdc, 3 + i * 38, 5, 0, 0, 42, 38);
		else if (i == player->GetCurrLife() - 1)
			life[0]->FrameRender(hdc, 3 + i * 38, 5, lifeFrameX, 0);
		else
			life[1]->AlphaRender(hdc, 3 + i * 38, 5, 120);
	}

	// Stamina
	stamina[1]->Render(hdc, 3, 45);
	stamina[0]->Render(hdc, 8, 50, 0, 0, (player->GetCurrStamina() * 63) / player->GetMaxStamina(), 16);
}
