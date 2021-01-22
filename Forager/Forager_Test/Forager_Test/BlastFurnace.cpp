#include "BlastFurnace.h"

HRESULT BlastFurnace::Init()
{
	img = ImageManager::GetSingleton()->FindImage("Blast_Furnace_Possible");
	return S_OK;
}

void BlastFurnace::Release()
{
}

void BlastFurnace::Update()
{
}

void BlastFurnace::Render(HDC hdc, FPOINT cameraPos)
{
}
