#include "Fruit.h"
#include "Image.h"

HRESULT Fruit::Init(int typeNum)
{
	img = ImageManager::GetSingleton()->FindImage("Fruit");
	this->typeNum = typeNum;

	return S_OK;
}

void Fruit::Release()
{
}

void Fruit::Update()
{
}

void Fruit::Render(HDC hdc, FPOINT pos)
{
	img->FrameRender(hdc, int(900 - pos.x), int(900 - pos.y), 0, 0);
}
