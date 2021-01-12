#pragma once
#include "Item.h"

class ConsumItem : public Item
{
public:
	virtual HRESULT Init(int itemListNum);
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc, FPOINT cameraPos);

	void UseItem();
};

