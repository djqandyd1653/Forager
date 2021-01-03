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

	POINT pos;				// ��ġ
	RECT rc;				// Rect
	int size;				// �̹��� ũ��
	float speed;			// �ӵ�
	int life;				// ���
	float stamina;			// ü��
	int exp;				// ����ġ

	PLAYER_STATE state;		// �÷��̾� ����

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

