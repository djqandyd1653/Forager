#include "ImageManager.h"
#include "Image.h"

Image * ImageManager::AddImage(string key, const char * fileName, int width, int height, bool isTrans, COLORREF color)
{
	Image* img = FindImage(key);
	// �̹��� ã���� �̹��� ��ȯ
	if (img)
	{
		return img;
	}

	img = new Image();

	if (FAILED(img->Init(fileName, width, height, isTrans, color)))
	{
		// ���� �� �Ҵ� ����
		img->Release();
		delete img;
		return nullptr;
	}

	imageData.insert(make_pair(key, img));
	return img;
}

Image * ImageManager::AddImage(string key, const char * fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTrans, COLORREF color)
{
	Image* img = FindImage(key);
	// �̹��� ã���� �̹��� ��ȯ
	if (img)
	{
		return img;
	}

	img = new Image();

	if (FAILED(img->Init(fileName, width, height, maxFrameX, maxFrameY, isTrans, color)))
	{
		// ���� �� �Ҵ� ����
		img->Release();
		delete img;
		return nullptr;
	}

	imageData.insert(make_pair(key, img));
	return img;
}

Image * ImageManager::FindImage(string key)
{
	itImage = imageData.find(key);

	if (itImage != imageData.end())
	{
		return itImage->second;
	}

	return NULL;
}

void ImageManager::Release()
{
	DeleteAll();
}

void ImageManager::DeleteImg(string key)
{
	// Ű�� �̹��� �˻�
	itImage = imageData.find(key);

	// �̹��� ã���� �Ҵ� ����
	if (itImage != imageData.end())
	{
		SAFE_RELEASE(itImage->second);
		SAFE_DELETE(itImage->second);
		imageData.erase(itImage);
	}
}

void ImageManager::DeleteAll()
{
	itImage = imageData.begin();
	while (itImage != imageData.end())
	{
		// �̹��� ������ �̹��� ����
		if (itImage->second != NULL)
		{
			SAFE_RELEASE(itImage->second);
			SAFE_DELETE(itImage->second);
			itImage = imageData.erase(itImage);
		}
		else
		{
			itImage++;
		}
	}

	imageData.clear();
}
