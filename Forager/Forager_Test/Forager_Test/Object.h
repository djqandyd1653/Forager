#pragma once
#include "GameNode.h"

class Image;

class Object : public GameNode
{
private:

protected:
	FPOINT pos;
	RECT rc;
	int typeNum;
	Image* img;
	
public:
	virtual HRESULT Init(int typeNum);
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc, FPOINT pos);

	void SetPos();

	int GetTypeNum() { return typeNum; }
};