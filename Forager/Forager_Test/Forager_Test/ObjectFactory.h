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

protected:
	list<Object*> objList;			// ������ Object ���� ����Ʈ
	static list<Object*> acList;	// ���� Update�� Object�� ����Ʈ
	list<Object*>::iterator itOdj;	// iterator
public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc, FPOINT pos);

	Object* newObj(OBJ_TYPE name);

	virtual void CreateObjList(OBJ_TYPE name, int cnt);
	//virtual void 
	virtual Object* PopObj(Object* obj, int num);

	void CreateAcObj(float& currTime, float createTime, int& currCnt, int maxCnt);
	list<Object*>::iterator DeleteAcObj(list<Object*>::iterator it);
};

class TreeFactory : public ObjectFactory
{
	//virtual void CreateObj(int cnt);
	//virtual Object* PopObj(Object* obj);
};

class RockFactory : public ObjectFactory
{
	//virtual void CreateObj(int cnt);
	//virtual Object* PopObj(Object* obj);
};

class FruitFactory : public ObjectFactory
{
	//virtual void CreateObj(int cnt);
	//virtual Object* PopObj(Object* obj);
};