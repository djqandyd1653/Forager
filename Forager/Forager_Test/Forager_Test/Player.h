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

	POINT pos;				// ��ġ
	RECT rc;				// Rect
	POINT rcCenter;			// Rect center��ġ
	int sizeX;				// �̹��� ���� ũ��
	int sizeY;				// �̹��� ���� ũ��
	float speed;			// �ӵ�
	float moveAngleX;		// X�� ������ ����
	float moveAngleY;		// Y�� ������ ����
	int maxLife;			// �ִ� ���
	int currLife;			// ���� ���
	int maxStamina;			// �ִ� ü��
	int currStamina;		// ���� ü��
	int maxEXP;				// �ִ� ����ġ
	int currEXP;			// ���� ����ġ
	int level;				// ����
	int currFrameX;			// x ������
	float frameTime;		// ������ üũ Ÿ��
	bool isLeft;			// ������ �ٶ󺸴°�?
	bool ableAttack;		// ���� �����Ѱ�?

	PLAYER_STATE state;		// �÷��̾� ����

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