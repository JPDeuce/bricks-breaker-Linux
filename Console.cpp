#include "Common.h"
#include "Console.h"

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <csignal>

#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>

// ---------------------------------------------------------------------------
// Terminal state management
// ---------------------------------------------------------------------------
static struct termios orig_termios;
static bool termios_saved = false;

static void restore_termios()
{
	if (termios_saved)
		tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
}

static void handle_sigint(int)
{
	restore_termios();
	_exit(128 + SIGINT);
}

static void setup_termios()
{
	if (!termios_saved)
	{
		tcgetattr(STDIN_FILENO, &orig_termios);
		termios_saved = true;

		// Switch to raw mode once and leave it until exit
		// (prevents escape sequences from being echoed between frames)
		struct termios raw = orig_termios;
		raw.c_lflag &= ~(ECHO | ICANON);
		raw.c_cc[VMIN] = 0;
		raw.c_cc[VTIME] = 0;
		tcsetattr(STDIN_FILENO, TCSANOW, &raw);

		std::signal(SIGINT, handle_sigint);
		atexit(restore_termios);
	}
}

// ---------------------------------------------------------------------------
// Static state
// ---------------------------------------------------------------------------
int Console::defFG = 7;
int Console::defBG = 0;

static int curFG = 7;
static int curBG = 0;

static bool keyState[256] = { false };
static bool keyJust[256] = { false };

// ---------------------------------------------------------------------------
// Console output helpers
// ---------------------------------------------------------------------------
void Console::Show(wchar_t symbol)
{
	// Encode as UTF-8 and output via cout (avoid mixing std::wcout / std::cout)
	if (symbol < 0x80)
	{
		std::cout << static_cast<char>(symbol);
	}
	else if (symbol < 0x800)
	{
		std::cout << static_cast<char>(0xC0 | (symbol >> 6));
		std::cout << static_cast<char>(0x80 | (symbol & 0x3F));
	}
	else
	{
		std::cout << static_cast<char>(0xE0 | (symbol >> 12));
		std::cout << static_cast<char>(0x80 | ((symbol >> 6) & 0x3F));
		std::cout << static_cast<char>(0x80 | (symbol & 0x3F));
	}
}

void Console::ForegroundColor(WORD attr)
{
	curFG = attr & 0x0F;
	// Standard ANSI: 30-37 for dim, 90-97 for bright
	std::cout << "\033[" << (attr < 8 ? 30 + attr : 90 + attr - 8) << "m";
}

WORD Console::ForegroundColor()
{
	return static_cast<WORD>(curFG);
}

void Console::BackgroundColor(WORD attr)
{
	curBG = attr & 0x0F;
	std::cout << "\033[" << (attr < 8 ? 40 + attr : 100 + attr - 8) << "m";
}

WORD Console::BackgroundColor()
{
	return static_cast<WORD>(curBG);
}

void Console::ResetColor()
{
	curFG = defFG;
	curBG = defBG;
	std::cout << "\033[0m";
}

// ---------------------------------------------------------------------------
// Window / cursor
// ---------------------------------------------------------------------------
int Console::WindowWidth()
{
	struct winsize w;
	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == 0)
		return w.ws_col;
	return 80;
}

int Console::WindowHeight()
{
	struct winsize w;
	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == 0)
		return w.ws_row;
	return 24;
}

void Console::SetWindowSize(int columns, int rows)
{
	(void)columns; (void)rows;
}

void Console::SetBufferSize(int columns, int rows)
{
	(void)columns; (void)rows;
}

void Console::CursorVisible(bool visible)
{
	std::cout << (visible ? "\033[?25h" : "\033[?25l");
}

void Console::Clear()
{
	std::cout << "\033[2J\033[H";
}

static int cursX = 0, cursY = 0;

int Console::CursorColumn()
{
	return cursX;
}

int Console::CursorRow()
{
	return cursY;
}

void Console::SetCursorPosition(int X, int Y)
{
	cursX = X;
	cursY = Y;
	std::cout << "\033[" << (Y + 1) << ";" << (X + 1) << "H";
}

// ---------------------------------------------------------------------------
// Misc
// ---------------------------------------------------------------------------
void Console::Lock(bool lock)
{
	if (!lock)
		std::cout.flush();
}

void Console::EOLWrap(bool on)
{
	(void)on;
}

void Console::FlushKeys()
{
	tcflush(STDIN_FILENO, TCIFLUSH);
	for (int i = 0; i < 256; ++i)
		keyState[i] = keyJust[i] = false;
}

// ---------------------------------------------------------------------------
// Show at position
// ---------------------------------------------------------------------------
void Console::Show(int x, int y, wchar_t symbol)
{
	SetCursorPosition(x, y);
	Show(symbol);
}

// ---------------------------------------------------------------------------
// Box drawing (uses Unicode box-drawing chars – works fine with UTF-8)
// ---------------------------------------------------------------------------
void Console::DrawBox(int left, int top, int width, int height, bool dbl)
{
	wchar_t const* SingleLine = L"┌─┐│└┘";
	wchar_t const* DoubleLine = L"╔═╗║╚╝";
	wchar_t const* Set = dbl ? DoubleLine : SingleLine;

	Show(left, top, Set[0]);
	for (int col = 0; col < width - 2; col++)
		Show(Set[1]);
	Show(Set[2]);

	int x = left + width - 1, y = top + 1;
	for (int row = 0; row < height - 2; row++, y++)
	{
		Show(left, y, Set[3]);
		Show(x, y, Set[3]);
	}

	y = top + height - 1;
	Show(left, y, Set[4]);
	for (int col = 0; col < width - 2; col++)
		Show(Set[1]);
	Show(Set[5]);
}

// ---------------------------------------------------------------------------
// RandomName
// ---------------------------------------------------------------------------
char const* Console::RandomName()
{
	const int Min = 3, Max = 7;
	static char name[Max + 1];

	char const* Cons = "bcdfghjklmnpqrstvwxyz";
	char const* Vows = "aeiouy";
	int NumCons = static_cast<int>(strlen(Cons));
	int NumVows = static_cast<int>(strlen(Vows));

	int nameLen = rand() % (Max - Min + 1) + Min;
	bool putAConsHere = rand() % 2 != 0;
	for (int i = 0; i < nameLen; i++, putAConsHere = !putAConsHere)
		name[i] = putAConsHere ? Cons[rand() % NumCons] : Vows[rand() % NumVows];

	name[nameLen] = '\0';
	name[0] = name[0] - 'a' + 'A';
	return name;
}

// ---------------------------------------------------------------------------
// WordWrap
// ---------------------------------------------------------------------------
void Console::WordWrap(int x, int y, int w, char const* const t)
{
	auto count = strlen(t);
	for (decltype(count) i = 0, j; i < count; i = j)
	{
		for (j = i + w; j < count && ' ' != t[j]; --j);
		if (j > count)
			j = count;

		Console::SetCursorPosition(x, y++);
		for (auto k = i; k < j; ++k)
			std::cout << t[k];
		for (; ' ' == t[j]; ++j);
	}
}

// ---------------------------------------------------------------------------
// Keyboard input processing
// ---------------------------------------------------------------------------
void Console::ProcessInput()
{
	// Clear just-pressed flags from the last frame
	memset(keyJust, 0, sizeof(keyJust));

	// Save previous state for transition detection
	bool prevState[256];
	memcpy(prevState, keyState, sizeof(keyState));
	memset(keyState, 0, sizeof(keyState));

	setup_termios();

	char buf[64];
	int n;
	while ((n = static_cast<int>(read(STDIN_FILENO, buf, sizeof(buf)))) > 0)
	{
		for (int i = 0; i < n; i++)
		{
			unsigned char ch = static_cast<unsigned char>(buf[i]);

			if (ch == 0x1B && i + 2 < n && buf[i + 1] == '[')
			{
				switch (buf[i + 2])
				{
				case 'A': keyState[VK_UP] = true; break;
				case 'B': keyState[VK_DOWN] = true; break;
				case 'C': keyState[VK_RIGHT] = true; break;
				case 'D': keyState[VK_LEFT] = true; break;
				}
				i += 2;
			}
			else if (ch == 0x1B)
			{
				keyState[VK_ESCAPE] = true;
			}
			else if (ch == ' ')
			{
				keyState[VK_SPACE] = true;
			}
			else if (ch == 'r' || ch == 'R')
			{
				keyState['R'] = true;
			}
		}
	}
	clearerr(stdin);

	// Compute just-pressed transitions
	for (int i = 0; i < 256; i++)
	{
		if (keyState[i] && !prevState[i])
			keyJust[i] = true;
	}
}

// ---------------------------------------------------------------------------
// GetAsyncKeyState – reads from the state tables updated by ProcessInput
// ---------------------------------------------------------------------------
short GetAsyncKeyState(int vKey)
{
	short result = 0;
	if (keyState[vKey])            result |= static_cast<short>(0x8000);
	if (keyJust[vKey])             result |= 0x0001;
	return result;
}
