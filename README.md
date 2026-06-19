# Bricks Breaker

A classic breakout-style arcade game that runs entirely in the Linux terminal, written in C++11.

Break bricks by bouncing a ball off your paddle — clear all bricks to advance through 5 levels.

![Screenshot](https://img.shields.io/badge/platform-Linux-blue) ![C++11](https://img.shields.io/badge/C%2B%2B-11-green) ![License](https://img.shields.io/badge/license-MIT-yellow)

## Gameplay

| Key            | Action                 |
|----------------|------------------------|
| ← / →         | Move paddle            |
| Space          | Launch / pause ball    |
| Up / Down      | Speed up / slow down   |
| R              | Restart game           |
| Escape         | Quit                   |

- **Paddle**: 12-wide box at the bottom of the screen
- **Ball**: Bounces off walls, paddle, and bricks
- **Bricks**: Each brick has a color that dims on hit; after enough hits it disappears
- **Levels**: 5 levels with increasingly complex brick layouts
- **Win condition**: Clear all bricks on level 5
- **Lose condition**: Ball falls below the paddle

## Build

### Prerequisites

- A C++11 compiler (g++ or clang++)
- GNU Make

### Compile

```bash
make
```

This produces the `bricks` executable.

### Run

```bash
./bricks
```

### Clean

```bash
make clean
```

## Architecture

```
Main.cpp          Game loop, timing, frame-rate control
Game.h / .cpp     Game state, collision detection, level loading, rendering
Ball.h / .cpp     Ball movement and wall bouncing
Box.h / .cpp      Paddle and brick drawing, hitbox containment
BaseObject.h/.cpp Base class with position, color, and character display
Console.h / .cpp  Terminal abstraction — ANSI escape rendering, Unicode box-drawing,
                  raw-mode keyboard input with cross-platform GetAsyncKeyState
Common.h          Constants: window size (80×40), frame rate (15 FPS)
```

The `Console` class provides a Windows-like console API backed by ANSI escape sequences, making the game feel native on Linux while keeping the rendering code platform-independent.

## License

MIT
