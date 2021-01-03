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
	// 이미지 추가
	Image* AddImage(string key, const char* fileName, int width, int height, bool isTrans = true, COLORREF color = RGB(255, 0, 255));
	Image* AddImage(string key, const char* fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTrans = true, COLORREF color = RGB(255, 0, 255));
	// 이미지 검색
	Image* FindImage(string key);
	void Release();
	// 이미지 제거
	void DeleteImg(string key);
	// 이미지 전체 제거
	void DeleteAll();
};

