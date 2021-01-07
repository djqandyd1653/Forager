#pragma once
#include "pch.h"

class Object;
//class Tree;
//class Rock;
//class Fruit;

class ObjectFactory
{
private:
	list<Object*> objList;
protected:

public:
	HRESULT Init();
	void newObj();
	template <class T>
	Object* CreateObj(T);
	//virtual Object* CreateObj() = 0;
};

class TreeFactory : public ObjectFactory
{
private:
	virtual Object* CreateObj();
};

class RockFactory : public ObjectFactory
{
	virtual Object* CreateObj();
};

class FruitFactory : public ObjectFactory
{
	virtual Object* CreateObj();
};

template<class T>
inline Object * ObjectFactory::CreateObj(T)
{
	return NULL;
}
