#pragma once
#include "GameNode.h"

enum class ITEM_TYPE
{
	CONSUM = 0,
	ETC = 100
};

enum class ITEM_NAME_LIST
{
	// consum
	FRUIT = 1,

	// etc
	TREE = 101,
	ROCK
};

class Item : public GameNode
{
protected:
	FPOINT pos;
	RECT rc;

	Image* img;
	ITEM_TYPE type;
	ITEM_NAME_LIST listNum;
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc, FPOINT cameraPos);

	/*
		case 0:
		img = ImageManager::GetSingleton()->FindImage("Tree_Item_Drop");
		break;
	case 1:
		img = ImageManager::GetSingleton()->FindImage("Rock_Item_Drop");
		break;
	case 2:
		img = ImageManager::GetSingleton()->FindImage("Fruit_Item_Drop");
		break;
	*/
};

