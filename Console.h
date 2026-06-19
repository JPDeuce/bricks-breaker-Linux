#pragma once
#include <iostream>

typedef unsigned short WORD;

// Colors - can be used as Foreground or Background
enum ConsoleColor
{
	Black = 0,
	DarkBlue = 1,
	DarkGreen = 2,
	DarkCyan = 3,
	DarkRed = 4,
	DarkMagenta = 5,
	DarkYellow = 6,
	Gray = 7,
	DarkGray = 8,
	Blue = 9,
	Green = 10,
	Cyan = 11,
	Red = 12,
	Magenta = 13,
	Yellow = 14,
	White = 15,
};

// Virtual key codes (cross-platform, matching Windows convention where useful)
const int VK_UP = 0x26;
const int VK_DOWN = 0x28;
const int VK_LEFT = 0x25;
const int VK_RIGHT = 0x27;
const int VK_ESCAPE = 0x1B;
const int VK_SPACE = 0x20;

class Console
{
	static int defFG;
	static int defBG;

	static void Show(wchar_t symbol);

public:
	static WORD ForegroundColor();
	static void ForegroundColor(WORD attr);
	static WORD BackgroundColor();
	static void BackgroundColor(WORD attr);
	static void ResetColor();
	static int WindowWidth();
	static int WindowHeight();
	static void SetWindowSize(int columns, int rows);
	static void SetBufferSize(int columns, int rows);
	static int CursorColumn();
	static int CursorRow();
	static void SetCursorPosition(int X, int Y);
	static void Clear();
	static void CursorVisible(bool visible);
	static void Lock(bool lock);
	static void EOLWrap(bool on);
	static void FlushKeys();
	static void Show(int x, int y, wchar_t symbol);
	static void DrawBox(int x, int y, int width, int height, bool dbl);
	static char const* RandomName();
	static void WordWrap(int x, int y, int w, char const* const t);

	// Call once per frame to read keyboard input
	static void ProcessInput();
};

// Cross-platform replacement for Windows GetAsyncKeyState
short GetAsyncKeyState(int vKey);
