#include "Common.h"
#include "BaseObject.h"

void BaseObject::Draw() const
{
	Console::SetCursorPosition(x_position, y_position);
	Console::ForegroundColor(static_cast<WORD>(color));
	std::cout << visage;
}