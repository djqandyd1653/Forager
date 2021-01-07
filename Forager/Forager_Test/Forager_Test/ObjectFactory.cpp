#include "ObjectFactory.h"
#include "Object.h"
#include "Tree.h"
#include "Rock.h"
#include "Fruit.h"

HRESULT ObjectFactory::Init()
{
	return E_NOTIMPL;
}

void ObjectFactory::newObj()
{
	//Object* obj = CreateObj(T);
	//objList.push_back(obj);
}

//template <class T>
//Object * ObjectFactory::CreateObj(T)
//{
//	return nullptr;
//}

Object * TreeFactory::CreateObj()
{
	return new Tree;
}

Object * RockFactory::CreateObj()
{
	return new Rock;
}

Object * FruitFactory::CreateObj()
{
	return new Fruit;
}
