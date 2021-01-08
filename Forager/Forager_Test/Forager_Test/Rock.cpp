#include "Rock.h"
#include "Image.h"

HRESULT Rock::Init(int typeNum)
{
	img = ImageManager::GetSingleton()->FindImage("Rock");
	this->typeNum = typeNum;

	return S_OK;
}

void Rock::Release()
{
}

void Rock::Update()
{
}

void Rock::Render(HDC hdc, FPOINT pos)
{
	img->FrameRender(hdc, int(1200 - pos.x), int(1200 - pos.y), 0, 0);
}
