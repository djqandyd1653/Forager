#include "Pickaxe.h"
#include "Image.h"

HRESULT Pickaxe::Init()
{
	img = ImageManager::GetSingleton()->FindImage("Pickaxe");
	return E_NOTIMPL;
}

void Pickaxe::Release()
{
}

void Pickaxe::Update()
{
}

void Pickaxe::Render(HDC hdc)
{
	img->Render(hdc, 0, 0);
}
