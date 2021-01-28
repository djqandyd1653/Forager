#include "BlastFurnace.h"
#include "Image.h"

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
	img->Render(hdc, pos.x - cameraPos.x, pos.y - cameraPos.y);
	Rectangle(hdc, rc.left - cameraPos.x, rc.top - cameraPos.y, rc.right - cameraPos.x, rc.bottom - cameraPos.y);
}

void BlastFurnace::SetRect()
{
	rc.left = pos.x;
	rc.top = pos.y;
	rc.right = pos.x + 112;
	rc.bottom = pos.y + 160;
}
