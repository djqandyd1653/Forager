#pragma once
#include "pch.h"

class Item;
class ConsumFactory;
class EtcFactory;

class ItemManager
{
private:
	static ConsumFactory consumFactory;
	static EtcFactory etcFactory;

	list<Item*> itemList;
	static list<Item*> acItemList;
	list<Item*>::iterator itItem;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc, FPOINT cameraPos);

	Item* newItem(int itemListNum);

	void CreateItemList(int itemListNum, int cnt);
	//Item* CreateAcObj();
	//void DeleteAcObj(Object* obj);
};

class ConsumFactory : public ItemManager
{

};

class EtcFactory : public ItemManager
{

};

