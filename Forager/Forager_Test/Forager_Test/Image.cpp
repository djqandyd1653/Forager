#include "Image.h"
#include "Animation.h"

Image::Image() : imageInfo(NULL), fileName(NULL), isTrans(FALSE), transColor(RGB(0, 0, 0))
{
}

Image::~Image()
{
}

HRESULT Image::Init(int width, int height)
{
	// 재초기화 방지용, 이미지 정보에 값이 들어 있다면 릴리즈 선행
	if (imageInfo != NULL) this->Release();

	// DC 가져오기
	HDC hdc = GetDC(g_hWnd);

	imageInfo = new IMAGE_INFO;
	imageInfo->resID = 0;
	imageInfo->hMemDC = CreateCompatibleDC(hdc);
	imageInfo->hBit = CreateCompatibleBitmap(hdc, width, height);
	imageInfo->hOBit = (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBit);
	imageInfo->width = width;
	imageInfo->height = height;
	imageInfo->loadType = LOAD_EMPTY;

	imageInfo->hBlendDC = CreateCompatibleDC(hdc);
	imageInfo->hBlendBitmap = CreateCompatibleBitmap(hdc, width, height);
	imageInfo->hOldBlendBit = (HBITMAP)SelectObject(imageInfo->hBlendDC, imageInfo->hBlendBitmap);

	// 리소스 얻는데 실패 시 종료
	if (imageInfo->hBit == NULL)
	{
		this->Release();
		return E_FAIL;
	}

	blendFunc.AlphaFormat = 0;	// AC_SRC_ALPHA;
	blendFunc.BlendFlags = 0;
	blendFunc.BlendOp = AC_SRC_OVER;
	blendFunc.SourceConstantAlpha = 0;

	// DC 해제
	ReleaseDC(g_hWnd, hdc);

	return S_OK;
}

HRESULT Image::Init(const char * fileName, int width, int height, bool isTrans, COLORREF color)
{
	// 재초기화 방지용, 이미지 정보에 값이 들어 있다면 릴리즈 선행
	if (imageInfo != NULL) this->Release();

	// DC 가져오기
	HDC hdc = GetDC(g_hWnd);

	imageInfo = new IMAGE_INFO;
	imageInfo->resID = 0;
	imageInfo->hMemDC = CreateCompatibleDC(hdc);
	imageInfo->hBit = (HBITMAP)LoadImage(g_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	imageInfo->hOBit = (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBit);
	imageInfo->width = width;
	imageInfo->height = height;
	imageInfo->loadType = LOAD_FILE;

	// Blend
	imageInfo->hBlendDC = CreateCompatibleDC(hdc);
	imageInfo->hBlendBitmap = CreateCompatibleBitmap(hdc, width, height);
	imageInfo->hOldBlendBit = (HBITMAP)SelectObject(imageInfo->hBlendDC, imageInfo->hBlendBitmap);

	this->isTrans = isTrans;
	transColor = color;

	// 리소스 얻는데 실패 시 종료
	if (imageInfo->hBit == NULL)
	{
		this->Release();
		return E_FAIL;
	}

	// Blend
	blendFunc.AlphaFormat = 0;	// AC_SRC_ALPHA;
	blendFunc.BlendFlags = 0;
	blendFunc.BlendOp = AC_SRC_OVER;
	blendFunc.SourceConstantAlpha = 0;

	// DC 해제
	ReleaseDC(g_hWnd, hdc);

	return S_OK;
}

HRESULT Image::Init(const char * fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTrans, COLORREF color)
{
	// 재초기화 방지용, 이미지 정보에 값이 들어 있다면 릴리즈 선행
	if (imageInfo != NULL) this->Release();

	// DC 가져오기
	HDC hdc = GetDC(g_hWnd);

	imageInfo = new IMAGE_INFO;
	imageInfo->resID = 0;
	imageInfo->hMemDC = CreateCompatibleDC(hdc);
	imageInfo->hBit = (HBITMAP)LoadImage(g_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	imageInfo->hOBit = (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBit);
	imageInfo->width = width;
	imageInfo->height = height;
	imageInfo->loadType = LOAD_FILE;

	// Animation
	imageInfo->maxFrameX = maxFrameX - 1;
	imageInfo->maxFrameY = maxFrameY - 1;
	imageInfo->currFrameX = 0;
	imageInfo->currFrameY = 0;
	imageInfo->frameWidth = width / maxFrameX;
	imageInfo->frameHeight = height / maxFrameY;

	this->isTrans = isTrans;
	transColor = color;

	// 리소스 얻는데 실패 시 종료
	if (imageInfo->hBit == NULL)
	{
		this->Release();
		return E_FAIL;
	}

	// DC 해제
	ReleaseDC(g_hWnd, hdc);

	return S_OK;
}

void Image::Release()
{
	//이미지 정보가 남아 있다면 해제 시켜라
	if (imageInfo)
	{
		//이미지 삭제
		SelectObject(imageInfo->hMemDC, imageInfo->hOBit);
		DeleteObject(imageInfo->hBit);
		DeleteDC(imageInfo->hMemDC);

		//포인터 삭제
		SAFE_DELETE(imageInfo);
		SAFE_DELETE_ARRAY(fileName);

		//투명 컬러키 초기화
		isTrans = FALSE;
		transColor = RGB(0, 0, 0);
	}
}

void Image::Render(HDC hdc, int destX, int destY)
{
	//GdiTransparentBlt: 비트맵의 특정색상을 제외하고 고속복사 해주는 함수
	if (isTrans)
	{
		GdiTransparentBlt(
			hdc,									// 복사할 장소의 DC
			destX, destY,							// 복사될 장소의 x, y 좌표
			imageInfo->width, imageInfo->height,	// 복사될 이미지의 가로, 세로 크기
			imageInfo->hMemDC,						// 복사할 대상 DC
			0, 0,									// 복사 시작 프레임(복사 시작위치)
			imageInfo->width, imageInfo->height,	// 복사 영역 가로, 세로 크기
			transColor								// 복사 시 제외할 색상
		);
	}
	else
	{
		BitBlt(hdc,									// 복사할 장소의 DC
			destX, destY,							// 복사될 장소의 x, y 좌표
			imageInfo->width, 						// 복사될 이미지의 가로 크기 
			imageInfo->height,						// 복사될 이미지의 세로 크기
			imageInfo->hMemDC,						// 복사할 대상 DC
			0, 0,									// 복사 시작 프레임(복사 시작위치)
			SRCCOPY									// 복사 옵션
		);										
	}
}

void Image::Render(HDC hdc, int destX, int destY, int srcX, int srcY, int srcWidth, int srcHeight)
{
	if (isTrans)
	{
		GdiTransparentBlt(
			hdc,						// 복사할 장소의 DC
			destX, destY,				// 복사될 장소의 x, y 좌표
			srcWidth,					// 복사될 이미지 가로크기
			srcHeight,					// 복사될 이미지 세로크기
			imageInfo->hMemDC,			// 복사될 대상 DC
			srcX, srcY,					// 복사 시작지점
			srcWidth, srcHeight,		// 복사 영역 가로크기, 세로크기
			transColor					// 복사할때 제외할 색상 (마젠타)
		);				
	}									
	else
	{
		BitBlt(
			hdc,						// 복사 목적지 DC
			destX, destY,				// 복사 시작 위치
			srcWidth, srcHeight,		// 원본에서 복사될 가로, 세로 크기
			imageInfo->hMemDC,			// 원본 DC
			srcX, srcY,					// 복사 시작 프레임(복사 시작위치)
			SRCCOPY						// 복사 옵션
		);
	}

}

void Image::FrameRender(HDC hdc, int destX, int destY, int currFrameX, int currFrameY)
{
	if (imageInfo->maxFrameX < currFrameX || imageInfo->maxFrameY < currFrameY)
	{
		imageInfo->currFrameX = imageInfo->maxFrameX;
		imageInfo->currFrameY = imageInfo->maxFrameY;
	}
	else
	{
		imageInfo->currFrameX = currFrameX;
		imageInfo->currFrameY = currFrameY;
	}

	//GdiTransparentBlt: 비트맵의 특정색상을 제외하고 고속복사 해주는 함수
	if (isTrans)
	{
		GdiTransparentBlt(
			hdc,											// 복사할 장소의 DC
			destX, destY,									// 복사될 장소의 x, y 좌표
			imageInfo->frameWidth, imageInfo->frameHeight,	// 복사될 이미지의 가로, 세로 크기
			imageInfo->hMemDC,								// 복사할 대상 DC
			imageInfo->currFrameX * imageInfo->frameWidth,	// 복사 시작 프레임(가로) (복사 시작위치)
			imageInfo->currFrameY * imageInfo->frameHeight,	// 복사 시작 프레임(세로) (복사 시작위치)
			imageInfo->frameWidth, imageInfo->frameHeight,	// 복사 영역 가로, 세로 크기 
			transColor										// 복사 시 제외할 색상
		);
	}
	else
	{
		BitBlt(hdc, destX, destY,
			imageInfo->frameWidth, imageInfo->frameHeight,
			imageInfo->hMemDC,
			imageInfo->currFrameX * imageInfo->frameWidth,
			imageInfo->currFrameY * imageInfo->frameHeight,
			SRCCOPY
		);
	}
}

void Image::AlphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	blendFunc.SourceConstantAlpha = alpha;

	if (isTrans)
	{
		// 선행 작업 : blendDC, blendBitmap을 준비

		// 1. 목적지 DC에 그려져 있는 내용을 blendDC에 복사
		BitBlt(
			imageInfo->hBlendDC,
			0, 0,
			imageInfo->width, 
			imageInfo->height,
			hdc, 
			destX, destY, 
			SRCCOPY);

		// 2. 출력할 이미지DC를 blendDC에 지정한 색상을 제외하면서 복사
		GdiTransparentBlt(
			imageInfo->hBlendDC,					// 복사할 장소의 DC
			0, 0,									// 복사될 장소의 x, y 좌표
			imageInfo->width, imageInfo->height,	// 복사될 이미지의 가로, 세로 크기
			imageInfo->hMemDC, 						// 복사할 대상 DC
			0, 0,									// 복사 시작 프레임 가로 세로 (복사 시작위치)
			imageInfo->width, imageInfo->height,	// 복사 영역 가로, 세로 크기 
			transColor);							// 복사 시 제외할 색상
													
		// 3. blendDC의 내용을 목적지 DC에 알파 블렌드 함수로 복사 
		AlphaBlend(
			hdc,
			destX, destY,
			imageInfo->width, imageInfo->height,
			imageInfo->hBlendDC, 
			0, 0,
			imageInfo->width, imageInfo->height,
			blendFunc);
	}
	else
	{
		AlphaBlend(
			hdc, 
			destX, destY, 
			imageInfo->width, imageInfo->height,
			imageInfo->hMemDC, 
			0, 0,
			imageInfo->width, imageInfo->height,
			blendFunc);
	}
}

void Image::AlphaFrameRender(HDC hdc, int destX, int destY, int srcX, int srcY, int srcWidth, int srcHeight, BYTE alpha)
{
	blendFunc.SourceConstantAlpha = alpha;

	if (isTrans)
	{
		// 선행 작업 : blendDC, blendBitmap을 준비

		// 1. 목적지 DC에 그려져 있는 내용을 blendDC에 복사
		BitBlt(
			imageInfo->hBlendDC,
			0, 0,
			srcWidth, srcHeight,
			hdc,
			destX, destY,
			SRCCOPY);

		// 2. 출력할 이미지DC를 blendDC에 지정한 색상을 제외하면서 복사
		GdiTransparentBlt(
			imageInfo->hBlendDC,			// 복사할 장소의 DC
			0, 0,							// 복사될 장소의 x, y 좌표
			srcWidth, srcHeight,			// 복사될 이미지의 가로, 세로 크기
			imageInfo->hMemDC, 				// 복사할 대상 DC
			srcX, srcY,						// 복사 시작 프레임 가로 세로 (복사 시작위치)
			srcWidth, srcHeight,			// 복사 영역 가로, 세로 크기 
			transColor);					// 복사 시 제외할 색상

		// 3. blendDC의 내용을 목적지 DC에 알파 블렌드 함수로 복사 
		AlphaBlend(
			hdc,
			destX, destY,
			srcWidth, srcHeight,
			imageInfo->hBlendDC,
			0, 0,
			srcWidth, srcHeight,
			blendFunc);
	}
	else
	{
		AlphaBlend(
			hdc,
			destX, destY,
			imageInfo->width, imageInfo->height,
			imageInfo->hMemDC,
			0, 0,
			imageInfo->width, imageInfo->height,
			blendFunc);
	}
}

void Image::AnimationRender(HDC hdc, int destX, int destY, Animation * ani)
{
	Render(hdc, destX, destY, ani->GetFramePoint().x, ani->GetFramePoint().y, imageInfo->frameWidth, imageInfo->frameHeight);
}
