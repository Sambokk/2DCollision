#include "pch.h"
#include "Table.h"

#include "GameEngine.h"
#include "DRD2DEngine.h"

void Table::render(ID2D1HwndRenderTarget* _renderTarget)
{
	_renderTarget->FillRectangle(
		D2D1_RECT_F{ 100,100,1300,700 },
		gameEngine->getD2DEngine()->getBrush(COLOR::CadetBlue));
}
