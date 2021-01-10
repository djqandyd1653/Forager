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
	virtual void Render(HDC hdc, FPOINT cameraPos);
	virtual void UpdateRect() = 0;

	void SetPos(FPOINT pos) { this->pos = pos; };

	int GetTypeNum() { return typeNum; }
};