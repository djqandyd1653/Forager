#pragma once
#include "pch.h"

class Animation;

class Image
{
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE,			//���ҽ��� �ε�
		LOAD_FILE,				//���Ϸ� �ε�
		LOAD_EMPTY,				//���Ʈ�� �ε�
		LOAD_END
	};

	typedef struct tagImage
	{
		DWORD		resID;				// ���ҽ� ID
		HDC			hMemDC;				// �޸� DC
		HBITMAP		hBit;				// ��Ʈ��
		HBITMAP		hOBit;				// �õ��Ʈ��
		int			width;				// �̹��� ����ũ��
		int			height;				// �̹��� ����ũ��
		BYTE		loadType;			// �̹��� �ε�Ÿ��

		// Animation
		int			currFrameX;			// ���� ������x
		int			currFrameY;			// ���� ������y
		int			maxFrameX;			// �ִ� x������ ����
		int			maxFrameY;			// �ִ� y������ ����
		int			frameWidth;			// 1�������� ���α���
		int			frameHeight;		// 1�������� ���α���	
		float		x, y;				// Animation ���� �� ��ġ

		// Blend
		HDC			hBlendDC;
		HBITMAP		hBlendBitmap;
		HBITMAP		hOldBlendBit;

		tagImage()	//������ = �ʱ�ȭ
		{
			resID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
			width = 0;
			height = 0;
			loadType = LOAD_EMPTY;

			hBlendDC = NULL;
			hBlendBitmap = NULL;
			hOldBlendBit = NULL;

			currFrameX = 0;
			currFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
		}
	}IMAGE_INFO, *LPIMAGE_INFO;

private:
	LPIMAGE_INFO	imageInfo;		// �̹��� ����
	CHAR*			fileName;		// ���� �̸�
	BOOL			isTrans;		// ���� ���ֱ�(����Ÿ)
	COLORREF		transColor;		// ������ RGB(255, 0, 255) (����Ÿ)
	BLENDFUNCTION	blendFunc;

public:

	HRESULT Init(int width, int height);
	HRESULT Init(const char* fileName, int width, int height, bool isTrans, COLORREF color);
	HRESULT Init(const char* fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTrans, COLORREF color);

	void Release();

	void Render(HDC hdc, int destX, int destY);
	void Render(HDC hdc, int destX, int destY, int srcX, int srcY, int srcWidth, int srcHeight);
	void FrameRender(HDC hdc, int destX, int destY, int currFrameX, int currFrameY);
	void AlphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void AlphaFrameRender(HDC hdc, int destX, int destY, int srcX, int srcY, int srcWidth, int srcHeight, BYTE alpha);
	void AnimationRender(HDC hdc, int destX, int destY, Animation* ani);

	HDC GetMemDC() { return imageInfo->hMemDC; }

	int GetWidth() { return imageInfo->width; }
	int GetHeight() { return imageInfo->height; }
	int GetFrameWidth() { return imageInfo->frameWidth; }
	int GetFrameHeight() { return imageInfo->frameHeight; }

	Image();
	~Image();
};

