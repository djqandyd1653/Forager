#include "Fruit.h"
#include "Image.h"

HRESULT Fruit::Init()
{
	img = ImageManager::GetSingleton()->FindImage("Fruit");
	return E_NOTIMPL;
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
