# 🎮 Maze Game

[![forthebadge](https://forthebadge.com/images/badges/made-with-c.svg)](http://forthebadge.com)
[![forthebadge](http://forthebadge.com/images/badges/built-with-love.svg)](http://forthebadge.com)

A `terminal-born` maze solver reborn as an `SDL2-powered` graphical game! Race from **S** (Start) to **E** (Exit), matching the computer’s `BFS solution` in as few moves as possible.

<div align="center">
  <img src="https://github.com/user-attachments/assets/8b780717-cc5b-487c-9373-35479f171c93" width="500">
</div>

# Table of contents
1. [Features](#features)  
2. [Prerequisites](#prerequisites)  
3. [Installation & Build](#installation--build)  
4. [Running the Game](#running-the-game)  
5. [Gameplay](#gameplay)  
6. [Controls](#controls)
7. [License](#license)  

---

# Features

- **Random & Predefined Mazes**  
  Load built-in puzzles or any text-based maze file from `mazes.txt`.  
- **BFS Solver**  
  Watch the computer compute the optimal path; then try to match it.  
- **Move Counter**  
  You get exactly as many moves as the BFS solution; track them in real time.  
- **Win/Lose Pop-Ups**  
  Instant feedback when you reach the exit—or run out of moves.  
- **Colorful SDL2 Graphics**  
  Walls, paths, start/end, and player are all color-coded.  
- **Cross-Platform Builds**  
  One-step `make run` on Linux/macOS or a simple batch script on Windows.

[(Back to top)](#table-of-contents)

---

## Prerequisites

- A C compiler (GCC, MinGW, MSYS2, etc.)  
- **SDL2** development libraries  
- **SDL2_ttf** (for rendering on-screen text)  
- A POSIX-style shell (Linux/macOS) or **MSYS2** on Windows  

[(Back to top)](#table-of-contents)

---

## Installation & Build

### Windows (MSYS2 + MinGW64)

1. Install MSYS2: https://www.msys2.org/  
2. Open the **MSYS2 MinGW-64** shell and run:
   ```bash
   pacman -Syu
   pacman -S base-devel mingw-w64-x86_64-toolchain \
     mingw-w64-x86_64-SDL2 mingw-w64-x86_64-SDL2_ttf
3. Clone & build
   ```bash
   git clone https://github.com/<YOUR_USER>/maze-game.git
   cd maze-game
   make run
   ```
   Or use `build.bat` if you prefer

### Linux / macOS

1. Install dependencies:
   ```bash
   # Debian / Ubuntu
   sudo apt-get update
   sudo apt-get install build-essential libsdl2-dev libsdl2-ttf-dev

   # macOS (Homebrew)
   brew install sdl2 sdl2_ttf
2. Clone & build:
   ```bash
   git clone https://github.com/<YOUR_USER>/maze-game.git
   cd maze-game
   make run
   
[(Back to top)](#table-of-contents)

---
## Running the Game

After building, the game launches automatically. To run manually:
```bash
./maze_game      # Linux/macOS
maze_game.exe    # Windows
```
[(Back to top)](#table-of-contents)

---

## Gameplay
- Objective: Navigate from S (green) to E (green) before your moves run out.
- Move Limit: You have exactly the same number of moves as the BFS solver’s shortest path.
- Winning: Reach E with ≥ 0 moves remaining → You win.
- Losing: Moves drop below zero before reaching <b>E</b> → You lose.

[(Back to top)](#table-of-contents)

---

## Controls
| Key | Action     |
| --- | ---------- |
| W   | Move Up    |
| A   | Move Left  |
| S   | Move Down  |
| D   | Move Right |
| Esc | Quit Game  |


[(Back to top)](#table-of-contents)

---

## License

The MIT License (MIT) 2017. Please have a look at the [LICENSE.md](LICENSE.md) for more details.

[(Back to top)](#table-of-contents)
