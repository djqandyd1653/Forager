#pragma once
#include "GameNode.h"

enum class PLAYER_STATE
{
	IDLE,
	RUN,
	ROLL,
	COUNT
};

class Image;
class Animation;

class Player : public GameNode
{
private:

	POINT pos;				// 위치
	RECT rc;				// Rect
	int size;				// 이미지 크기
	float speed;			// 속도
	int life;				// 목숨
	float stamina;			// 체력
	int exp;				// 경험치

	PLAYER_STATE state;		// 플레이어 상태

	Image* img[static_cast<int>(PLAYER_STATE::COUNT)];
	Animation* anim[static_cast<int>(PLAYER_STATE::COUNT)];

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void Move();
	void RectUpdate();
};

