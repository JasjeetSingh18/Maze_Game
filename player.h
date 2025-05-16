#ifndef PLAYER_H
#define PLAYER_H
#include "maze.h"

//Function Declerations
extern int player_row, player_col;
extern int end_row, end_col;

void get_start (char maze[ROWS][COLS]);   

void get_end(char maze[ROWS][COLS]);

int check_valid_move(char maze[ROWS][COLS], int player_row, int player_col);

void get_move (char maze[ROWS][COLS]);

int check_finish (char maze[ROWS][COLS], int end_row, int end_col);

#endif