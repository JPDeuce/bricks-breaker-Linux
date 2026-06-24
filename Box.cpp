#include "Common.h"
#include "Box.h"

void Box::Draw() const
{
	Console::ForegroundColor(static_cast<WORD>(color));
	Console::DrawBox(x_position, y_position, width, height, doubleThick);
}

bool Box::Contains(int x, int y) const
{
	if (x_position <= x && x_position + width > x && y_position <= y && y_position + height > y)
		return true;
	else
		return false;
}