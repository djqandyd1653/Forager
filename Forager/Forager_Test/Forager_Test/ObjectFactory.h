#pragma once
#include "pch.h"

enum class OBJ_TYPE
{
	TREE,
	ROCK,
	FRUIT,
	COUNT
};

class Object;
class TreeFactory;
class RockFactory;
class FruitFactory;
//class Tree;
//class Rock;
//class Fruit;

class ObjectFactory
{
private:
	static TreeFactory	treeFactory;
	static RockFactory	rockFactory;
	static FruitFactory	fruitFactory;

	list<Object*> objList;			// ������ Object ���� ����Ʈ
	static list<Object*> acList;	// ���� Update�� Object�� ����Ʈ
	list<Object*>::iterator itOdj;	// iterator
public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc, FPOINT pos);

	Object* newObj(OBJ_TYPE name);

	void CreateObjList(OBJ_TYPE name, int cnt);
	Object* PopObj(Object* obj, int num);

	Object* CreateAcObj(float& currTime, float createTime, int maxCnt, FPOINT tilePos);
	void DeleteAcObj(Object* obj);

	list<Object*> GetAcList() { return acList; }
};

class TreeFactory : public ObjectFactory
{
};

class RockFactory : public ObjectFactory
{
};

class FruitFactory : public ObjectFactory
{
};