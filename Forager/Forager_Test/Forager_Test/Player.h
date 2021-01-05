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

struct tagTile;

class Player : public GameNode
{
private:

	POINT pos;				// ��ġ
	RECT rc;				// Rect
	int sizeX;				// �̹��� ���� ũ��
	int sizeY;				// �̹��� ���� ũ��
	float speed;			// �ӵ�
	float moveAngleX;		// X�� ������ ����
	float moveAngleY;		// Y�� ������ ����
	int life;				// ���
	float stamina;			// ü��
	int exp;				// ����ġ
	int currFrameX;			// x ������
	float frameTime;		// ������ üũ Ÿ��
	bool isLeft;			// ������ �ٶ󺸴°�?

	PLAYER_STATE state;		// �÷��̾� ����

	Image* img[static_cast<int>(PLAYER_STATE::COUNT)];
	Animation* anim[static_cast<int>(PLAYER_STATE::COUNT)];
	tagTile* tile;

public:
	virtual HRESULT Init(tagTile* tile);
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void Move();
	void RectUpdate();
	void DirUpdate();

	POINT GetPos() { return pos; }
	void SetPosX(int x) { pos.x = x; }
	void SetPosY(int y) { pos.y = y; }
};

