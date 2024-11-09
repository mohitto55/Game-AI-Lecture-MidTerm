#include "gameCursor.h"
#include "util.h"

void gameCursor::Draw() {
	const wchar_t* Img = L"бу";
	SetColor(10);
	ScreenPrint(x, y, Img);
	SetColor(15);
}