#include "Tree.h"
#include "Image.h"

HRESULT Tree::Init(int typeNum)
{
	Object::Init(typeNum);
	img = ImageManager::GetSingleton()->FindImage("Tree");
	this->typeNum = typeNum;
	maxHp = 5;
	currHp = maxHp;

	return S_OK;
}

void Tree::Release()
{
}

void Tree::Render(HDC hdc, FPOINT cameraPos)
{
	Object::Render(hdc, cameraPos);
	img->FrameRender(hdc, int(pos.x - cameraPos.x), int(pos.y - cameraPos.y) - 112, frameCnt, 0);	// 112 = tile_size(56) * 2
	//Rectangle(hdc, rc.left - cameraPos.x, rc.top - cameraPos.y, rc.right - cameraPos.x, rc.bottom - cameraPos.y);
}

void Tree::UpdateRect()
{
	rc.left = pos.x + 20;
	rc.top = pos.y + 25;
	rc.right = pos.x + 36;
	rc.bottom = pos.y + 56;
}
