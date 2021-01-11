#include "ObjectFactory.h"
#include "Object.h"
#include "Tree.h"
#include "Rock.h"
#include "Fruit.h"

list<Object*> ObjectFactory::acList;
TreeFactory ObjectFactory::treeFactory;
RockFactory ObjectFactory::rockFactory;
FruitFactory ObjectFactory::fruitFactory;

HRESULT ObjectFactory::Init()
{
	treeFactory.CreateObjList(OBJ_TYPE::TREE, 30);
	rockFactory.CreateObjList(OBJ_TYPE::ROCK, 30);
	fruitFactory.CreateObjList(OBJ_TYPE::FRUIT, 30);
	return S_OK;
}

void ObjectFactory::Release()
{

}

void ObjectFactory::Update()
{
	itOdj = acList.begin();

	while (itOdj != acList.end())
	{
		(*itOdj)->Update();
		itOdj++;
	}
}

void ObjectFactory::Render(HDC hdc, FPOINT pos)
{
	itOdj = acList.begin();

	while (itOdj != acList.end())
	{
		(*itOdj)->Render(hdc, pos);
		itOdj++;
	}
}

Object* ObjectFactory::newObj(OBJ_TYPE name)
{
	switch (name)
	{
	case OBJ_TYPE::TREE:
		return new Tree;
	case OBJ_TYPE::ROCK:
		return new Rock;
	case OBJ_TYPE::FRUIT:
		return new Fruit;
	case OBJ_TYPE::COUNT:
		return nullptr;
	}
}

void ObjectFactory::CreateObjList(OBJ_TYPE name, int cnt)
{
	for (int i = 0; i < cnt; i++)
	{
		Object* obj = newObj(name);
		obj->Init(int(name));
		objList.push_back(obj);
	}
}

Object * ObjectFactory::PopObj(Object* obj, int num)
{
	Object* tempObj;

	itOdj = objList.begin();

	if (objList.empty())
	{
		Object* newObj = obj;
		newObj->Init(num);
		tempObj = newObj;
	}
	else
	{
		tempObj = *itOdj;
		itOdj = objList.erase(itOdj);
	}

	return tempObj;
}

Object* ObjectFactory::CreateAcObj(float& currTime, float createTime, int maxCnt, FPOINT tilePos)
{
	if (acList.size() >= maxCnt)
		return nullptr;

	currTime += TimeManager::GetSingleton()->GetElapsedTime();

	if (currTime < createTime)
		return nullptr;

	currTime = 0;

	int randNum = rand() % int(OBJ_TYPE::COUNT);

	Object* tempObj = nullptr;

	switch (OBJ_TYPE(randNum))
	{
	case OBJ_TYPE::TREE:
		tempObj = treeFactory.PopObj(newObj(OBJ_TYPE(randNum)), randNum);
		break;
	case OBJ_TYPE::ROCK:
		tempObj = rockFactory.PopObj(newObj(OBJ_TYPE(randNum)), randNum);
		break;
	case OBJ_TYPE::FRUIT:
		tempObj = fruitFactory.PopObj(newObj(OBJ_TYPE(randNum)), randNum);
		break;
	}

	acList.push_back(tempObj);
	acList.back()->SetPos(tilePos);
	acList.back()->UpdateRect();
	return acList.back();
}

void ObjectFactory::DeleteAcObj(Object* obj)
{
	list<Object*>::iterator it = acList.begin();

	while (it != acList.end())
	{
		if ((*it)->GetPos().x == obj->GetPos().x && (*it)->GetPos().y == obj->GetPos().y)
		{
			break;
		}

		it++;
	}

	switch (OBJ_TYPE((*it)->GetTypeNum()))
	{
	case OBJ_TYPE::TREE:
		treeFactory.objList.push_back(*it);
		break;
	case OBJ_TYPE::ROCK:
		rockFactory.objList.push_back(*it);
		break;
	case OBJ_TYPE::FRUIT:
		fruitFactory.objList.push_back(*it);
		break;
	}

	it = acList.erase(it);
}