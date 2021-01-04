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
	int sizeX;				// 이미지 가로 크기
	int sizeY;				// 이미지 세로 크기
	float speed;			// 속도
	float moveAngleX;		// X축 움직임 각도
	float moveAngleY;		// Y축 움직임 각도
	int life;				// 목숨
	float stamina;			// 체력
	int exp;				// 경험치
	int currFrameX;			// x 프레임
	float frameTime;		// 프레임 체크 타임
	bool isLeft;			// 왼쪽을 바라보는가?

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
	void DirUpdate();

	POINT GetPos() { return pos; }
	void SetPosX(float x) { pos.x = x; }
	void SetPosY(float y) { pos.y = y; }
};

