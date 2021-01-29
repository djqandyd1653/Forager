#include "SewingMachine.h"
#include "Image.h"

HRESULT SewingMachine::Init()
{
	img = ImageManager::GetSingleton()->FindImage("Sewing_Machine_Possible");
	return S_OK;
}

void SewingMachine::Release()
{
}

void SewingMachine::Update()
{
}

void SewingMachine::Render(HDC hdc, FPOINT cameraPos)
{
	img->Render(hdc, pos.x - cameraPos.x, pos.y - cameraPos.y - 56);
	Rectangle(hdc, rc.left - cameraPos.x, rc.top - cameraPos.y, rc.right - cameraPos.x, rc.bottom - cameraPos.y - 56);
}

void SewingMachine::SetRect()
{
	rc.left = pos.x;
	rc.top = pos.y;
	rc.right = pos.x + 112;
	rc.bottom = pos.y + 160;
}
