#include "Anvil.h"
#include "Image.h"

HRESULT Anvil::Init()
{
	img = ImageManager::GetSingleton()->FindImage("Anvil_Possible");
	return S_OK;
}

void Anvil::Release()
{
}

void Anvil::Update()
{
}

void Anvil::Render(HDC hdc, FPOINT cameraPos)
{
	img->Render(hdc, pos.x - cameraPos.x, pos.y - cameraPos.y);
	Rectangle(hdc, rc.left - cameraPos.x, rc.top - cameraPos.y, rc.right - cameraPos.x, rc.bottom - cameraPos.y);
}

void Anvil::SetRect()
{
	rc.left = pos.x;
	rc.top = pos.y;
	rc.right = pos.x + 100;
	rc.bottom = pos.y + 90;
}
