#pragma once
#include "Console.h"

class BaseObject
{
public:

	ConsoleColor color = ConsoleColor::White;			
	int x_position = 0;
	int y_position = 0;
	char visage = '.';

	virtual void Draw() const;
};