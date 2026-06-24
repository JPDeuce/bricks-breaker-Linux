#include "Common.h"
#include "Game.h"

#include <cstdio>
#include <cstdlib>

Game::Game()
{
	Reset();
}

void Game::Reset()
{
	Console::SetWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	Console::CursorVisible(false);
	paddle.width = 12;
	paddle.height = 2;
	paddle.x_position = 32;
	paddle.y_position = 30;

	ball.visage = 'O';
	ball.color = ConsoleColor::Cyan;
	ResetBall();
	gameWon = false;
	gameLost = false;
	currentLevel = 1;
	score = 0;
	lives = 3;
	LoadLevel(1);
}

void Game::ResetBall()
{
	ball.x_position = paddle.x_position + paddle.width / 2;
	ball.y_position = paddle.y_position - 1;
	ball.x_velocity = rand() % 2 ? 1 : -1;
	ball.y_velocity = -1;
	ball.moving = false;
}

void Game::LoadLevel(int level)
{
	bricks.clear();
	currentLevel = level;

	// Try loading from a level data file
	char filename[64];
	std::snprintf(filename, sizeof(filename), "levels/level%d.txt", level);

	FILE* f = std::fopen(filename, "r");
	if (f)
	{
		char line[128];
		while (std::fgets(line, sizeof(line), f))
		{
			if (line[0] == '#' || line[0] == '\n' || line[0] == '\r')
				continue;

			int x, y, w, h, color, dbl;
			if (std::sscanf(line, "%d %d %d %d %d %d", &x, &y, &w, &h, &color, &dbl) != 6)
				continue;

			if (x < 1) x = 1;
			if (y < 1) y = 1;
			if (w < 1) w = 1;
			if (h < 1) h = 1;
			if (color < 0) color = 0;
			if (color > 15) color = 15;

			Box brick;
			brick.x_position = x;
			brick.y_position = y;
			brick.width = w;
			brick.height = h;
			brick.color = static_cast<ConsoleColor>(color);
			brick.doubleThick = (dbl != 0);
			bricks.push_back(brick);
		}
		std::fclose(f);
		return;
	}

	// Fallback: hardcoded levels (used if levels/ directory is missing)
	if (level == 1)
	{
		for (int i = 0; i < 5; i++)
		{
			Box brick;
			brick.width = 10;
			brick.height = 2;
			brick.x_position = 3 + i * 16;
			brick.y_position = 6;
			brick.doubleThick = true;
			brick.color = ConsoleColor::DarkGreen;
			bricks.push_back(brick);
		}
	}
	else if (level == 2)
	{
		for (int i = 0; i < 6; i++)
		{
			Box brick;
			brick.width = 10;
			brick.height = 2;
			brick.x_position = 1 + i * 12;
			brick.y_position = 5;
			brick.doubleThick = true;
			brick.color = ConsoleColor::DarkRed;
			bricks.push_back(brick);
		}

		for (int i = 0; i < 6; i++)
		{
			Box brick;
			brick.width = 10;
			brick.height = 2;
			brick.x_position = 7 + i * 12;
			brick.y_position = 8;
			brick.doubleThick = true;
			brick.color = ConsoleColor::DarkMagenta;
			bricks.push_back(brick);
		}
	}
	else if (level == 3)
	{
		for (int i = 0; i < 6; i++)
		{
			Box brick;
			brick.width = 10;
			brick.height = 2;
			brick.x_position = 5 + i * 12;
			brick.y_position = 4;
			brick.doubleThick = true;
			brick.color = ConsoleColor::DarkCyan;
			bricks.push_back(brick);
		}

		for (int i = 0; i < 6; i++)
		{
			Box brick;
			brick.width = 10;
			brick.height = 2;
			brick.x_position = 11 + i * 12;
			brick.y_position = 7;
			brick.doubleThick = true;
			brick.color = ConsoleColor::Cyan;
			bricks.push_back(brick);
		}
	}
	else if (level == 4)
	{
		for (int i = 0; i < 7; i++)
		{
			Box brick;
			brick.width = 10;
			brick.height = 2;
			brick.x_position = 3 + i * 10;
			brick.y_position = 3;
			brick.doubleThick = true;
			brick.color = ConsoleColor::DarkYellow;
			bricks.push_back(brick);
		}

		for (int i = 0; i < 7; i++)
		{
			Box brick;
			brick.width = 10;
			brick.height = 2;
			brick.x_position = 8 + i * 10;
			brick.y_position = 6;
			brick.doubleThick = true;
			brick.color = ConsoleColor::Yellow;
			bricks.push_back(brick);
		}

		for (int i = 0; i < 7; i++)
		{
			Box brick;
			brick.width = 10;
			brick.height = 2;
			brick.x_position = 3 + i * 10;
			brick.y_position = 9;
			brick.doubleThick = true;
			brick.color = ConsoleColor::DarkRed;
			bricks.push_back(brick);
		}
	}
	else if (level == 5)
	{
		for (int i = 0; i < 7; i++)
		{
			Box brick;
			brick.width = 10;
			brick.height = 2;
			brick.x_position = 3 + i * 10;
			brick.y_position = 3;
			brick.doubleThick = true;
			brick.color = ConsoleColor::DarkMagenta;
			bricks.push_back(brick);
		}

		for (int i = 0; i < 7; i++)
		{
			Box brick;
			brick.width = 10;
			brick.height = 2;
			brick.x_position = 8 + i * 10;
			brick.y_position = 6;
			brick.doubleThick = true;
			brick.color = ConsoleColor::Magenta;
			bricks.push_back(brick);
		}

		for (int i = 0; i < 7; i++)
		{
			Box brick;
			brick.width = 10;
			brick.height = 2;
			brick.x_position = 3 + i * 10;
			brick.y_position = 9;
			brick.doubleThick = true;
			brick.color = ConsoleColor::DarkBlue;
			bricks.push_back(brick);
		}

		for (int i = 0; i < 7; i++)
		{
			Box brick;
			brick.width = 10;
			brick.height = 2;
			brick.x_position = 8 + i * 10;
			brick.y_position = 12;
			brick.doubleThick = true;
			brick.color = ConsoleColor::Blue;
			bricks.push_back(brick);
		}
	}
}

bool Game::Update()
{
	if (GetAsyncKeyState(VK_ESCAPE) & 0x1)
		return false;

	if (GetAsyncKeyState(VK_RIGHT) && paddle.x_position < WINDOW_WIDTH - paddle.width - 1)
		paddle.x_position += 2;

	if (GetAsyncKeyState(VK_LEFT) && paddle.x_position > 1)
		paddle.x_position -= 2;

	if (GetAsyncKeyState(VK_SPACE) & 0x1)
		ball.moving = !ball.moving;

	if (GetAsyncKeyState('R') & 0x1)
		Reset();

	CheckCollision();
	ball.Update();
	return true;
}

void Game::Render() const
{
	Console::Lock(true);
	Console::Clear();

	Console::DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, false);

	DrawHUD();

	paddle.Draw();
	ball.Draw();

	for (auto& b : bricks)
		b.Draw();

	if (gameWon)
	{
		Console::SetCursorPosition(WINDOW_WIDTH / 2 - 16, WINDOW_HEIGHT / 2);
		std::cout << "You win! Press 'R' to play again.";
	}

	if (gameLost)
	{
		Console::SetCursorPosition(WINDOW_WIDTH / 2 - 16, WINDOW_HEIGHT / 2);
		std::cout << "You lose. Press 'R' to play again.";
	}

	Console::Lock(false);
}

void Game::DrawHUD() const
{
	Console::ForegroundColor(static_cast<WORD>(ConsoleColor::White));

	char buf[64];
	std::snprintf(buf, sizeof(buf), "Level: %d", currentLevel);
	Console::SetCursorPosition(2, 1);
	std::cout << buf;

	std::snprintf(buf, sizeof(buf), "Score: %d", score);
	Console::SetCursorPosition(WINDOW_WIDTH / 2 - 4, 1);
	std::cout << buf;

	std::snprintf(buf, sizeof(buf), "Lives: %d", lives);
	Console::SetCursorPosition(WINDOW_WIDTH - 12, 1);
	std::cout << buf;
}

void Game::CheckCollision()
{
	int bx = ball.x_position;
	int by = ball.y_position;
	int vx = ball.x_velocity;
	int vy = ball.y_velocity;
	int nextX = bx + vx;
	int nextY = by + vy;

	// --- Brick collisions ---
	for (size_t i = 0; i < bricks.size(); i++)
	{
		Box& brick = bricks[i];
		bool hit = false;
		bool hitX = false;
		bool hitY = false;

		// Determine how the ball enters the brick
		if (brick.Contains(nextX, nextY))
		{
			// Full next position is inside → determine which face(s) were crossed
			hit = true;
			bool outsideX = (bx < brick.x_position || bx >= brick.x_position + brick.width);
			bool outsideY = (by < brick.y_position || by >= brick.y_position + brick.height);
			if (outsideX) hitX = true;
			if (outsideY) hitY = true;
			if (!outsideX && !outsideY)
				hitX = hitY = true;
		}

		if (!hit && brick.Contains(bx, nextY))
		{
			// Only Y changed, X stayed the same → vertical entry
			hit = true;
			hitY = true;
		}

		if (!hit && brick.Contains(nextX, by))
		{
			// Only X changed, Y stayed the same → horizontal entry
			hit = true;
			hitX = true;
		}

		if (!hit)
			continue;

		// Dim the brick
		int c = static_cast<int>(brick.color);
		if (c > static_cast<int>(ConsoleColor::Black))
			brick.color = static_cast<ConsoleColor>(c - 1);

		// Reverse velocity on the appropriate axes
		if (hitX) vx *= -1;
		if (hitY) vy *= -1;

		// Remove brick if fully dimmed
		if (brick.color == ConsoleColor::Black)
		{
			bricks.erase(bricks.begin() + i);
			i--;
			score += 100 * currentLevel;

			// Recalculate next position with updated velocity
			nextX = bx + vx;
			nextY = by + vy;
		}
		else
		{
			break;
		}
	}

	ball.x_velocity = vx;
	ball.y_velocity = vy;

	// --- Level complete? ---
	if (bricks.empty())
	{
		if (currentLevel < 5)
		{
			LoadLevel(currentLevel + 1);
			ResetBall();
		}
		else
		{
			gameWon = true;
			ball.moving = false;
		}
		return;
	}

	// --- Paddle collision ---
	// Recalculate next position with the (possibly updated) velocity
	nextX = ball.x_position + ball.x_velocity;
	nextY = ball.y_position + ball.y_velocity;

	if (paddle.Contains(nextX, nextY)
		|| paddle.Contains(nextX, ball.y_position)
		|| paddle.Contains(ball.x_position, nextY))
	{
		float ratio = static_cast<float>(ball.x_position - paddle.x_position) / paddle.width;
		ball.x_velocity = static_cast<int>((ratio - 0.5f) * 4.0f);
		if (ball.x_velocity == 0)
			ball.x_velocity = (rand() % 2) ? -1 : 1;
		ball.y_velocity = -1;
		ball.y_position = paddle.y_position - 1;
	}

	// --- Ball fell off bottom ---
	nextY = ball.y_position + ball.y_velocity;
	if (nextY >= WINDOW_HEIGHT - 1)
	{
		lives--;
		if (lives > 0)
		{
			ResetBall();
		}
		else
		{
			ball.moving = false;
			gameLost = true;
		}
	}
}
