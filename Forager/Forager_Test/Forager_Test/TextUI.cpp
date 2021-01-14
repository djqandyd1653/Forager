#include "TextUI.h"

HRESULT TextUI::Init()
{
	return E_NOTIMPL;
}

void TextUI::Render(HDC hdc, float posX, float posY)
{
	HFONT hFont, hOldFont;

	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, color);
	SetTextAlign(hdc, align);
	font.lfHeight = fontSize;

	hFont = CreateFontIndirect(&font);
	hOldFont = (HFONT)SelectObject(hdc, hFont);
	TextOut(hdc, int(posX), int(posY), text.c_str(), strlen(text.c_str()));

	SelectObject(hdc, hOldFont);
	DeleteObject(hFont);
}

TextUI::TextUI():
	fontSize(24),
	text(""),
	color(RGB(255, 255, 255)),
	align(TA_LEFT)
{
}
