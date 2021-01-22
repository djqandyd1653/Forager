#include "SewingMachine.h"

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
}
