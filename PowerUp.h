#pragma once
#include "Console.h"

enum class PowerUpType
{
    WidePaddle,
    ExtraLife,
    FireBall,
    SlowBall,
    Count
};

class PowerUp
{
public:
    PowerUpType type;
    int x_position;
    int y_position;
    int width = 3;
    int height = 1;
    int fallSpeed = 1;

    PowerUp(PowerUpType type, int x, int y);
    void Update();
    void Draw() const;
    bool Overlaps(int rx, int ry, int rw, int rh) const;

private:
    char GetChar() const;
    ConsoleColor GetColor() const;
};
