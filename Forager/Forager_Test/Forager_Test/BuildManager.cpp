#include "BuildManager.h"
#include "Building.h"
#include "Image.h"

list<Building*> BuildManager::acBuildingList;
BlastFurnaceFactory BuildManager::blastFurnaceFactory;
AnvilFactory BuildManager::anvilFactory;
SewingMachineFactory BuildManager::sewingMachineFactory;

HRESULT BuildManager::Init()
{
	for (int i = 0; i < 3; i++)
	{
		button[i].pos = { 1000, 200 + i * 100 };
		button[i].rc.left = button[i].pos.x;
		button[i].rc.top = button[i].pos.y;
		button[i].rc.right = button[i].pos.x + 220;
		button[i].rc.bottom = button[i].pos.y + 50;
	}

	button[0].img = ImageManager::GetSingleton()->FindImage("Blast_Furnace_Button");
	button[1].img = ImageManager::GetSingleton()->FindImage("Anvil_Button");
	button[2].img = ImageManager::GetSingleton()->FindImage("Sewing_Machine_Button");

	button[0].buildingKey = "BlastFurnce";
	button[1].buildingKey = "Anvil";
	button[2].buildingKey = "SewingMachine";

	button[0].material.insert(make_pair("Rock", 1));  // 10
	button[0].material.insert(make_pair("Tree", 1));   // 5
	button[1].material.insert(make_pair("Rock", 1));  // 20
	button[2].material.insert(make_pair("Rock", 1));  // 15
	button[2].material.insert(make_pair("Fruit", 1)); // 20

	selectBuild = false;
	selectBuildImg = nullptr;
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
	if (selectBuild)
	{
		SetSelectBuildImg();
		if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_ESCAPE))
			selectBuild = false;
	}

	SetSelectBuildImg();

	itBuilding = acBuildingList.begin();

	while (itBuilding != acBuildingList.end())
	{
		(*itBuilding)->Update();
		itBuilding++;
	}
}

void BuildManager::Render(HDC hdc)
{
	if (selectBuild)
	{
		if(selectBuildImg->GetHeight() > 100)
			selectBuildImg->AlphaRender(hdc, renderPos.x, renderPos.y - 56, 170);
		else
			selectBuildImg->AlphaRender(hdc, renderPos.x, renderPos.y, 170);
	}
	else
	{
		for (int i = 0; i < 3; i++)
		{
			button[i].img->Render(hdc, button[i].pos.x, button[i].pos.y);
			Rectangle(hdc, button[i].rc.left, button[i].rc.top, button[i].rc.right, button[i].rc.bottom);
		}
	}
}

void BuildManager::SetSelectBuildImg()
{
	if (ableBuild)
	{
		if (buildKey == "BlastFurnce")
			selectBuildImg = ImageManager::GetSingleton()->FindImage("Blast_Furnace_Possible");
		else if (buildKey == "Anvil")
			selectBuildImg = ImageManager::GetSingleton()->FindImage("Anvil_Possible");
		else if (buildKey == "SewingMachine")
			selectBuildImg = ImageManager::GetSingleton()->FindImage("Sewing_Machine_Possible");
	}
	else
	{
		if (buildKey == "BlastFurnce")
			selectBuildImg = ImageManager::GetSingleton()->FindImage("Blast_Furnace_Impossible");
		else if (buildKey == "Anvil")
			selectBuildImg = ImageManager::GetSingleton()->FindImage("Anvil_Impossible");
		else if (buildKey == "SewingMachine")
			selectBuildImg = ImageManager::GetSingleton()->FindImage("Sewing_Machine_Impossible");
	}

}
