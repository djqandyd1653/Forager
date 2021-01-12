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
class WeaponManager;

typedef struct tagTile TILE_INFO;

class Player : public GameNode
{
private:

	POINT pos;				// 위치
	RECT rc;				// Rect
	POINT rcCenter;			// Rect center위치
	int sizeX;				// 이미지 가로 크기
	int sizeY;				// 이미지 세로 크기
	float speed;			// 속도
	float moveAngleX;		// X축 움직임 각도
	float moveAngleY;		// Y축 움직임 각도
	int maxLife;			// 최대 목숨
	int currLife;			// 현재 목숨
	int maxStamina;			// 최대 체력
	int currStamina;		// 현재 체력
	int maxEXP;				// 최대 경험치
	int currEXP;			// 현재 경험치
	int level;				// 레벨
	int currFrameX;			// x 프레임
	float frameTime;		// 프레임 체크 타임
	bool isLeft;			// 왼쪽을 바라보는가?
	bool ableAttack;		// 공격 가능한가?

	PLAYER_STATE state;		// 플레이어 상태

	Image* img[static_cast<int>(PLAYER_STATE::COUNT)];
	//Animation* anim[static_cast<int>(PLAYER_STATE::COUNT)];
	tagTile* tile;
	WeaponManager* weaponMgr;

public:
	virtual HRESULT Init(tagTile* tile);
	virtual void Release();
	virtual void Update(FPOINT cameraPos);
	virtual void Render(HDC hdc, FPOINT cameraPos);

	void Move();
	void RectUpdate();
	void DirUpdate(FPOINT cameraPos);
	void LevelUp();

	POINT GetPos() { return pos; }
	POINT GetRcCenter() { return rcCenter; }
	void SetPosX(int x) { pos.x = x; }
	void SetPosY(int y) { pos.y = y; }

	RECT GetRect() { return rc; }

	int GetMaxLife() { return maxLife; }
	int GetCurrLife() { return currLife; }

	int GetMaxStamina() { return maxStamina; }
	int GetCurrStamina() { return currStamina; }

	int GetCurrEXP() { return currEXP; }
	int GetMaxEXP() { return maxEXP; }
	void GetEXP(int EXP);

	bool AbleAttack() { return ableAttack; }
};