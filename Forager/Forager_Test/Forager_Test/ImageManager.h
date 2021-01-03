#pragma once
#include "pch.h"
#include "Singleton.h"

class Image;

class ImageManager : public Singleton<ImageManager>
{
private:
	map<string, Image*> imageData;
	map<string, Image*>::iterator itImage;

public:
	// �̹��� �߰�
	Image* AddImage(string key, const char* fileName, int width, int height, bool isTrans = true, COLORREF color = RGB(255, 0, 255));
	Image* AddImage(string key, const char* fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTrans = true, COLORREF color = RGB(255, 0, 255));
	// �̹��� �˻�
	Image* FindImage(string key);
	void Release();
	// �̹��� ����
	void DeleteImg(string key);
	// �̹��� ��ü ����
	void DeleteAll();
};

