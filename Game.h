#pragma once
#include "Box.h"
#include "Ball.h"
#include "PowerUp.h"
#include <vector>

class Game
{
    Ball ball;
    Box paddle;
    std::vector<Box> bricks;
    std::vector<PowerUp> powerUps;

    bool gameWon = false;
    bool gameLost = false;
    int currentLevel = 1;
    int score = 0;
    int lives = 3;

    int widePaddleTimer = 0;
    int fireBallTimer = 0;
    int slowBallTimer = 0;
    bool slowToggle = false;

    static constexpr int DefaultPaddleWidth = 12;
    static constexpr int WidePaddleWidth = 20;

public:
    Game();
    bool Update();
    void Render() const;
    void Reset();
    void ResetBall();
    void CheckCollision();
    void LoadLevel(int level);
    void DrawHUD() const;
    void SpawnPowerUp(int x, int y);
    void UpdatePowerUps();
    void CollectPowerUp(const PowerUp& p);
};
