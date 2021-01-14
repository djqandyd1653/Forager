#include "Tree.h"
#include "Image.h"
#include "Item.h"

HRESULT Tree::Init(int typeNum)
{
	Object::Init(typeNum);
	img = ImageManager::GetSingleton()->FindImage("Tree");
	this->typeNum = typeNum;
	itemType = ITEM_TYPE::TREE;
	maxHp = 5;
	currHp = maxHp;
	EXP = 30; // 7

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
	rc.left = LONG(pos.x + 20);
	rc.top = LONG(pos.y + 25);
	rc.right = LONG(pos.x + 36);
	rc.bottom = LONG(pos.y + 56);
}
