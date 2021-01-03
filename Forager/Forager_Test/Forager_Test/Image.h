#pragma once
#include "pch.h"

class Animation;

class Image
{
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE,			//리소스로 로딩
		LOAD_FILE,				//파일로 로딩
		LOAD_EMPTY,				//빈비트맵 로딩
		LOAD_END
	};

	typedef struct tagImage
	{
		DWORD		resID;				// 리소스 ID
		HDC			hMemDC;				// 메모리 DC
		HBITMAP		hBit;				// 비트맵
		HBITMAP		hOBit;				// 올드비트맵
		int			width;				// 이미지 가로크기
		int			height;				// 이미지 세로크기
		BYTE		loadType;			// 이미지 로드타입

		// Animation
		int			currFrameX;			// 현재 프레임x
		int			currFrameY;			// 현재 프레임y
		int			maxFrameX;			// 최대 x프레임 갯수
		int			maxFrameY;			// 최대 y프레임 갯수
		int			frameWidth;			// 1프레임의 가로길이
		int			frameHeight;		// 1프레임의 세로길이	
		float		x, y;				// Animation 적용 시 위치

		// Blend
		HDC			hBlendDC;
		HBITMAP		hBlendBitmap;
		HBITMAP		hOldBlendBit;

		tagImage()	//생성자 = 초기화
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
	LPIMAGE_INFO	imageInfo;		// 이미지 정보
	CHAR*			fileName;		// 파일 이름
	BOOL			isTrans;		// 배경색 없애기(마젠타)
	COLORREF		transColor;		// 제거할 RGB(255, 0, 255) (마젠타)
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

