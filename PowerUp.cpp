#include "Common.h"
#include "PowerUp.h"

PowerUp::PowerUp(PowerUpType t, int x, int y)
    : type(t), x_position(x), y_position(y)
{
}

void PowerUp::Update()
{
    y_position += fallSpeed;
}

void PowerUp::Draw() const
{
    Console::ForegroundColor(static_cast<WORD>(GetColor()));
    Console::SetCursorPosition(x_position, y_position);
    std::cout << '[' << GetChar() << ']';
}

bool PowerUp::Overlaps(int rx, int ry, int rw, int rh) const
{
    return x_position < rx + rw
        && x_position + width > rx
        && y_position < ry + rh
        && y_position + height > ry;
}

char PowerUp::GetChar() const
{
    switch (type)
    {
    default: return '?';
    case PowerUpType::WidePaddle: return 'W';
    case PowerUpType::ExtraLife:  return 'L';
    case PowerUpType::FireBall:   return 'F';
    case PowerUpType::SlowBall:   return 'S';
    }
}

ConsoleColor PowerUp::GetColor() const
{
    switch (type)
    {
    default: return ConsoleColor::White;
    case PowerUpType::WidePaddle: return ConsoleColor::Green;
    case PowerUpType::ExtraLife:  return ConsoleColor::Red;
    case PowerUpType::FireBall:   return ConsoleColor::Yellow;
    case PowerUpType::SlowBall:   return ConsoleColor::Cyan;
    }
}
