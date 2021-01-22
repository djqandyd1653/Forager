#include "Anvil.h"

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
}
