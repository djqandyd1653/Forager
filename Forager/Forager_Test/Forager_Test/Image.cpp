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
	// ���ʱ�ȭ ������, �̹��� ������ ���� ��� �ִٸ� ������ ����
	if (imageInfo != NULL) this->Release();

	// DC ��������
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

	// ���ҽ� ��µ� ���� �� ����
	if (imageInfo->hBit == NULL)
	{
		this->Release();
		return E_FAIL;
	}

	blendFunc.AlphaFormat = 0;	// AC_SRC_ALPHA;
	blendFunc.BlendFlags = 0;
	blendFunc.BlendOp = AC_SRC_OVER;
	blendFunc.SourceConstantAlpha = 0;

	// DC ����
	ReleaseDC(g_hWnd, hdc);

	return S_OK;
}

HRESULT Image::Init(const char * fileName, int width, int height, bool isTrans, COLORREF color)
{
	// ���ʱ�ȭ ������, �̹��� ������ ���� ��� �ִٸ� ������ ����
	if (imageInfo != NULL) this->Release();

	// DC ��������
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

	// ���ҽ� ��µ� ���� �� ����
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

	// DC ����
	ReleaseDC(g_hWnd, hdc);

	return S_OK;
}

HRESULT Image::Init(const char * fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTrans, COLORREF color)
{
	// ���ʱ�ȭ ������, �̹��� ������ ���� ��� �ִٸ� ������ ����
	if (imageInfo != NULL) this->Release();

	// DC ��������
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

	// ���ҽ� ��µ� ���� �� ����
	if (imageInfo->hBit == NULL)
	{
		this->Release();
		return E_FAIL;
	}

	// DC ����
	ReleaseDC(g_hWnd, hdc);

	return S_OK;
}

void Image::Release()
{
	//�̹��� ������ ���� �ִٸ� ���� ���Ѷ�
	if (imageInfo)
	{
		//�̹��� ����
		SelectObject(imageInfo->hMemDC, imageInfo->hOBit);
		DeleteObject(imageInfo->hBit);
		DeleteDC(imageInfo->hMemDC);

		//������ ����
		SAFE_DELETE(imageInfo);
		SAFE_DELETE_ARRAY(fileName);

		//���� �÷�Ű �ʱ�ȭ
		isTrans = FALSE;
		transColor = RGB(0, 0, 0);
	}
}

void Image::Render(HDC hdc, int destX, int destY)
{
	//GdiTransparentBlt: ��Ʈ���� Ư�������� �����ϰ� ��Ӻ��� ���ִ� �Լ�
	if (isTrans)
	{
		GdiTransparentBlt(
			hdc,									// ������ ����� DC
			destX, destY,							// ����� ����� x, y ��ǥ
			imageInfo->width, imageInfo->height,	// ����� �̹����� ����, ���� ũ��
			imageInfo->hMemDC,						// ������ ��� DC
			0, 0,									// ���� ���� ������(���� ������ġ)
			imageInfo->width, imageInfo->height,	// ���� ���� ����, ���� ũ��
			transColor								// ���� �� ������ ����
		);
	}
	else
	{
		BitBlt(hdc,									// ������ ����� DC
			destX, destY,							// ����� ����� x, y ��ǥ
			imageInfo->width, 						// ����� �̹����� ���� ũ�� 
			imageInfo->height,						// ����� �̹����� ���� ũ��
			imageInfo->hMemDC,						// ������ ��� DC
			0, 0,									// ���� ���� ������(���� ������ġ)
			SRCCOPY									// ���� �ɼ�
		);										
	}
}

void Image::Render(HDC hdc, int destX, int destY, int srcX, int srcY, int srcWidth, int srcHeight)
{
	if (isTrans)
	{
		GdiTransparentBlt(
			hdc,						// ������ ����� DC
			destX, destY,				// ����� ����� x, y ��ǥ
			srcWidth,					// ����� �̹��� ����ũ��
			srcHeight,					// ����� �̹��� ����ũ��
			imageInfo->hMemDC,			// ����� ��� DC
			srcX, srcY,					// ���� ��������
			srcWidth, srcHeight,		// ���� ���� ����ũ��, ����ũ��
			transColor					// �����Ҷ� ������ ���� (����Ÿ)
		);				
	}									
	else
	{
		BitBlt(
			hdc,						// ���� ������ DC
			destX, destY,				// ���� ���� ��ġ
			srcWidth, srcHeight,		// �������� ����� ����, ���� ũ��
			imageInfo->hMemDC,			// ���� DC
			srcX, srcY,					// ���� ���� ������(���� ������ġ)
			SRCCOPY						// ���� �ɼ�
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

	//GdiTransparentBlt: ��Ʈ���� Ư�������� �����ϰ� ��Ӻ��� ���ִ� �Լ�
	if (isTrans)
	{
		GdiTransparentBlt(
			hdc,											// ������ ����� DC
			destX, destY,									// ����� ����� x, y ��ǥ
			imageInfo->frameWidth, imageInfo->frameHeight,	// ����� �̹����� ����, ���� ũ��
			imageInfo->hMemDC,								// ������ ��� DC
			imageInfo->currFrameX * imageInfo->frameWidth,	// ���� ���� ������(����) (���� ������ġ)
			imageInfo->currFrameY * imageInfo->frameHeight,	// ���� ���� ������(����) (���� ������ġ)
			imageInfo->frameWidth, imageInfo->frameHeight,	// ���� ���� ����, ���� ũ�� 
			transColor										// ���� �� ������ ����
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
		// ���� �۾� : blendDC, blendBitmap�� �غ�

		// 1. ������ DC�� �׷��� �ִ� ������ blendDC�� ����
		BitBlt(
			imageInfo->hBlendDC,
			0, 0,
			imageInfo->width, 
			imageInfo->height,
			hdc, 
			destX, destY, 
			SRCCOPY);

		// 2. ����� �̹���DC�� blendDC�� ������ ������ �����ϸ鼭 ����
		GdiTransparentBlt(
			imageInfo->hBlendDC,					// ������ ����� DC
			0, 0,									// ����� ����� x, y ��ǥ
			imageInfo->width, imageInfo->height,	// ����� �̹����� ����, ���� ũ��
			imageInfo->hMemDC, 						// ������ ��� DC
			0, 0,									// ���� ���� ������ ���� ���� (���� ������ġ)
			imageInfo->width, imageInfo->height,	// ���� ���� ����, ���� ũ�� 
			transColor);							// ���� �� ������ ����
													
		// 3. blendDC�� ������ ������ DC�� ���� ���� �Լ��� ���� 
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
		// ���� �۾� : blendDC, blendBitmap�� �غ�

		// 1. ������ DC�� �׷��� �ִ� ������ blendDC�� ����
		BitBlt(
			imageInfo->hBlendDC,
			0, 0,
			srcWidth, srcHeight,
			hdc,
			destX, destY,
			SRCCOPY);

		// 2. ����� �̹���DC�� blendDC�� ������ ������ �����ϸ鼭 ����
		GdiTransparentBlt(
			imageInfo->hBlendDC,			// ������ ����� DC
			0, 0,							// ����� ����� x, y ��ǥ
			srcWidth, srcHeight,			// ����� �̹����� ����, ���� ũ��
			imageInfo->hMemDC, 				// ������ ��� DC
			srcX, srcY,						// ���� ���� ������ ���� ���� (���� ������ġ)
			srcWidth, srcHeight,			// ���� ���� ����, ���� ũ�� 
			transColor);					// ���� �� ������ ����

		// 3. blendDC�� ������ ������ DC�� ���� ���� �Լ��� ���� 
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
