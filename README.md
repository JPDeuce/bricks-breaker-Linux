# Bricks Breaker

A classic breakout-style arcade game that runs entirely in the Linux terminal, written in C++11.

Break bricks by bouncing a ball off your paddle — clear all bricks to advance through 5 levels.

![C++11](https://img.shields.io/badge/C%2B%2B-11-green) ![License](https://img.shields.io/badge/license-MIT-yellow) [![Build](https://github.com/JPDeuce/bricks-breaker-Linux/actions/workflows/build.yml/badge.svg)](https://github.com/JPDeuce/bricks-breaker-Linux/actions/workflows/build.yml)

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
- **Bricks**: Each brick dims on hit; after enough hits it disappears
- **Lives**: 3 lives per game — ball falling costs one life
- **Score**: 100 points per brick × current level
- **HUD**: Shows current level, score, and lives remaining
- **Levels**: 5 levels loaded from `levels/levelN.txt` files
- **Win**: Clear all bricks on level 5
- **Lose**: Run out of lives

## Build

### Prerequisites

- A C++11 compiler (g++ or clang++)
- GNU Make

### Compile

```bash
make            # debug build
make release    # optimized build with -O2
```

This produces the `bricks` executable.

### Test

```bash
make test
```

### Run

```bash
./bricks
```

### Clean

```bash
make clean
```

## Level files

Levels are stored as plain text in `levels/levelN.txt`. Each line defines one brick:

```
x y width height color doubleThick
```

Lines starting with `#` are ignored. Color values are 0–15 matching standard terminal colors. If the files are missing, the game falls back to built-in level data.

## Architecture

```
Main.cpp          Game loop, timing, frame-rate control
Game.h / .cpp     Game state, collision detection, level loading, rendering, HUD
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
