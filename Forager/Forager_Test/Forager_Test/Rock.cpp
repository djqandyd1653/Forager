#include "Rock.h"
#include "Image.h"

HRESULT Rock::Init()
{
	img = ImageManager::GetSingleton()->FindImage("Rock");
	return E_NOTIMPL;
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
