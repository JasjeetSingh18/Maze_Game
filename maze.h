#ifndef MAZE_H
#define MAZE_H

// Function Declerations
#define ROWS 25
#define COLS 25

extern char mazes[3][ROWS][COLS];
extern char maze[ROWS][COLS];

int load_mazes(const char *filename);
void pick_random_maze(char maze[ROWS][COLS]);

#endif