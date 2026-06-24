#pragma once
#include "Box.h"
#include "Ball.h"
#include <vector>

class Game
{
	Ball ball;
	Box paddle;
	std::vector<Box> bricks;

	bool gameWon = false;
	bool gameLost = false;
	int currentLevel = 1;
	int score = 0;
	int lives = 3;

public:
	Game();
	bool Update();
	void Render() const;
	void Reset();
	void ResetBall();
	void CheckCollision();
	void LoadLevel(int level);
	void DrawHUD() const;
};
