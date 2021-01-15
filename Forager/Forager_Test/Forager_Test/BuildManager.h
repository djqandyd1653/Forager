#pragma once
#include "pch.h"

class Building;
class BlastFurnaceFactory;
class AnvilFactory;
class SewingMachineFactory;

class BuildManager
{
private:
	static BlastFurnaceFactory blastFurnaceFactory;
	static AnvilFactory anvilFactory;
	static SewingMachineFactory sewingMachineFactory;

	list<Building*> buildingList;
	static list<Building*> acBuildingList;
	list<Building*>::iterator itBuilding;
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc, FPOINT cameraPos);

	//Building* newItem(ITEM_TYPE itemType);

	//void CreateItemList(ITEM_TYPE itemType, int cnt);
	//Building* PopItem(ITEM_TYPE itemType);
	//void CreateAcObj(ITEM_TYPE itemType, FPOINT objPos);
	//void DeleteAcObj(Building* item);

	list<Building*> GetAcItemList() { return acBuildingList; }
};

class BlastFurnaceFactory : public BuildManager {};
class AnvilFactory : public BuildManager {};
class SewingMachineFactory : public BuildManager {};

