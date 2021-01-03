#pragma once
#include "GameNode.h"

struct tagTile;

class TestScene : public GameNode
{
private:
	tagTile* tile;
	int startNumX;
	int startNumY;
	int endNumX;
	int endNumY;

	HBRUSH myBrush;
	HBRUSH oldBrush;

	Image* img;
	//Image* border;

	//vector<tagTile> vecGrassTile;
	//vector<tagTile>::iterator itTile;
	float time;
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void LoadMap(int mapNum, int posNum);

	TestScene();
	~TestScene();
};

