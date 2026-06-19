#include "Common.h"
#include "Game.h"

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

void Game::CheckCollision()
{
	int nextX = ball.x_position + ball.x_velocity;
	int nextY = ball.y_position + ball.y_velocity;

	for (size_t i = 0; i < bricks.size(); i++)
	{
		if (bricks[i].Contains(nextX, nextY) || bricks[i].Contains(ball.x_position, nextY) || bricks[i].Contains(nextX, ball.y_position))
		{
			if (bricks[i].color > ConsoleColor::Black)
				bricks[i].color = static_cast<ConsoleColor>(bricks[i].color - 1);

			if (ball.x_position <= bricks[i].x_position || ball.x_position >= bricks[i].x_position + bricks[i].width)
				ball.x_velocity *= -1;

			if (ball.y_position <= bricks[i].y_position || ball.y_position >= bricks[i].y_position + bricks[i].height)
				ball.y_velocity *= -1;

			if (bricks[i].color == ConsoleColor::Black)
			{
				bricks.erase(bricks.begin() + i);
				i--;
			}
			else
			{
				break;
			}
		}
	}

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
	}

	if (paddle.Contains(nextX, nextY))
	{
		float ratio = static_cast<float>(ball.x_position - paddle.x_position) / paddle.width;
		ball.x_velocity = static_cast<int>((ratio - 0.5f) * 4.0f);
		if (ball.x_velocity == 0)
			ball.x_velocity = (rand() % 2) ? -1 : 1;
		ball.y_velocity = -1;
	}

	if (nextY >= WINDOW_HEIGHT - 1)
	{
		ball.moving = false;
		gameLost = true;
	}
}
