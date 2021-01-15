#include "BuildManager.h"
#include "Building.h"

list<Building*> BuildManager::acBuildingList;
BlastFurnaceFactory BuildManager::blastFurnaceFactory;
AnvilFactory BuildManager::anvilFactory;
SewingMachineFactory BuildManager::sewingMachineFactory;

HRESULT BuildManager::Init()
{
	return S_OK;
}

void BuildManager::Release()
{
	for (itBuilding = acBuildingList.begin(); itBuilding != acBuildingList.end(); itBuilding++)
	{
		if (*itBuilding)
		{
			(*itBuilding)->Release();
		}
		delete *itBuilding;
	}

	for (itBuilding = blastFurnaceFactory.buildingList.begin(); itBuilding != blastFurnaceFactory.buildingList.end(); itBuilding++)
	{
		if (*itBuilding)
		{
			(*itBuilding)->Release();
		}
		delete *itBuilding;
	}

	for (itBuilding = anvilFactory.buildingList.begin(); itBuilding != anvilFactory.buildingList.end(); itBuilding++)
	{
		if (*itBuilding)
		{
			(*itBuilding)->Release();
		}
		delete *itBuilding;
	}

	for (itBuilding = sewingMachineFactory.buildingList.begin(); itBuilding != sewingMachineFactory.buildingList.end(); itBuilding++)
	{
		if (*itBuilding)
		{
			(*itBuilding)->Release();
		}
		delete *itBuilding;
	}

	acBuildingList.clear();
	blastFurnaceFactory.buildingList.clear();
	anvilFactory.buildingList.clear();
	sewingMachineFactory.buildingList.clear();
}

void BuildManager::Update()
{
	itBuilding = acBuildingList.begin();

	while (itBuilding != acBuildingList.end())
	{
		(*itBuilding)->Update();
		itBuilding++;
	}
}

void BuildManager::Render(HDC hdc, FPOINT cameraPos)
{
	itBuilding = acBuildingList.begin();

	while (itBuilding != acBuildingList.end())
	{
		(*itBuilding)->Render(hdc, cameraPos);
		itBuilding++;
	}
}
