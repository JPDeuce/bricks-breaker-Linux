#include "Common.h"
#include "Game.h"
#include <chrono>
#include <thread>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std::chrono;

int main()
{
	float frameTimer = 1000.0f / FRAMES_PER_SECOND;
	std::srand(static_cast<unsigned>(std::time(nullptr)));
	Game game;
	while (true)
	{
		auto start = steady_clock::now();

		Console::ProcessInput();

		if (game.Update() == false)
			break;
		game.Render();

		if (GetAsyncKeyState(VK_UP) & 0x1)
			frameTimer -= 5;

		if (GetAsyncKeyState(VK_DOWN) & 0x1)
			frameTimer += 5;

		auto end = steady_clock::now();
		auto durationMS = duration_cast<milliseconds>(end - start);
		auto timeLeft = std::max(0.0f, frameTimer - static_cast<float>(durationMS.count()));
		std::this_thread::sleep_for(milliseconds(static_cast<int>(timeLeft)));
	}
}
