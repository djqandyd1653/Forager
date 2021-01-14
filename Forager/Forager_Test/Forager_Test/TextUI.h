#pragma once
#include "pch.h"
class TextUI
{
private:
	string text;
	int fontSize;
	int align;
	COLORREF color;
public:
	HRESULT Init();
	void Render(HDC hdc, float posX, float posY);

	void SetText(string text) { this->text = text; }
	void SetFontSize(int fontSize) { this->fontSize = fontSize; }
	void SetAlign(int align) { this->align = align; }
	void SetColor(COLORREF color) { this->color = color; }

	TextUI();
};

