#pragma once
#include "pch.h"

class Image;
class Building;
class BlastFurnaceFactory;
class AnvilFactory;
class SewingMachineFactory;

typedef struct tagBuildButton
{
	POINT pos;
	RECT rc;
	Image* img;
	string buildingKey;
	map<string, int> material;
}BUILD_BUTTON_INFO;

class BuildManager
{
private:
	static BlastFurnaceFactory blastFurnaceFactory;
	static AnvilFactory anvilFactory;
	static SewingMachineFactory sewingMachineFactory;

	list<Building*> buildingList;
	static list<Building*> acBuildingList;
	list<Building*>::iterator itBuilding;

	BUILD_BUTTON_INFO button[3];
	bool selectBuild;				// 건설할 건물을 선택했는가?
	bool ableBuild;					// 건물을 건설할 수 있는가?
	Image* selectBuildImg;
	POINT renderPos;
	string buildKey;
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	Building* NewBuilding(string key);

	void CreateBuildingList(string key, int cnt);
	Building* PopBuilding(string key);
	GameNode* CreateAcBuilding(POINT pos);
	//void DeleteAcObj(Building* item);

	list<Building*> GetAcItemList() { return acBuildingList; }
	BUILD_BUTTON_INFO* GetBuildButton() { return button; }
	
	bool GetSelectBuild() { return selectBuild; }
	void SetSelectBuild(bool selectBuild) { this->selectBuild = selectBuild; }

	void SetAbleBuild(bool ableBuild) { this->ableBuild = ableBuild; }

	void SetSelectBuildImg();

	void SetRenderPos(POINT pos) { renderPos = pos; }

	void SetBuildKey(string key) { buildKey = key; }

	bool GetAbleBuild() { return ableBuild; }
};

class BlastFurnaceFactory : public BuildManager {};
class AnvilFactory : public BuildManager {};
class SewingMachineFactory : public BuildManager {};

