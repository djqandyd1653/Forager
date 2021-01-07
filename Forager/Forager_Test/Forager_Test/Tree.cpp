#include "Tree.h"
#include "Image.h"

HRESULT Tree::Init()
{
	img = ImageManager::GetSingleton()->FindImage("Tree");
	return E_NOTIMPL;
}

void Tree::Release()
{
}

void Tree::Update()
{
}

void Tree::Render(HDC hdc, FPOINT pos)
{
	img->FrameRender(hdc, int(1000 - pos.x), int(1000 - pos.y), 0, 0);
}
