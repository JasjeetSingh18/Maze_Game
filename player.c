#include "player.h"
#include "maze.h"
#include "stdlib.h"
#include "stdio.h"

int player_row = 0;
int player_col = 0;
int end_row = 0;
int end_col = 0;

void get_start(char maze[ROWS][COLS])
{
    int found = 0;
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (maze[i][j] == 'S')
            {
                player_row = i;
                player_col = j;
                found = 1;
                break;
            }
        }
        if (found == 1)
            break;
    }
}

void get_end(char maze[ROWS][COLS])
{
    int found = 0;
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (maze[i][j] == 'E')
            {
                printf("Found!");
                end_row = i;
                end_col = j;
                found = 1;
                break;
            }
        }
        if (found == 1)
            break;
    }
}

int check_valid_move(char maze[ROWS][COLS], int row, int col)
{
    if (maze[row][col] == '#')
        return 0;
    else
        return 1;
}

void get_move(char maze[ROWS][COLS])
{
    char input;
    int valid_move = 0;
    printf("Please enter where you would like to move: ");

    do
    {
        scanf("%c", &input);
        getchar();
        printf("\n");

        if (input == 'W' || input == 'w')
        {
            valid_move = check_valid_move(maze, player_row - 1, player_col);
            if (valid_move == 1)
            {
                maze[player_row][player_col] = '.';
                player_row = player_row - 1;
            }
            else
                printf("Invalid! Please try again: ");
        }
        else if (input == 'S' || input == 's')
        {
            valid_move = check_valid_move(maze, player_row + 1, player_col);
            if (valid_move == 1)
            {
                maze[player_row][player_col] = '.';
                player_row = player_row + 1;
            }
            else
                printf("Invalid! Please try again: ");
        }
        else if (input == 'A' || input == 'a')
        {
            valid_move = check_valid_move(maze, player_row, player_col - 1);
            if (valid_move == 1)
            {
                maze[player_row][player_col] = '.';
                player_col = player_col - 1;
            }
            else
                printf("Invalid! Please try again: ");
        }
        else if (input == 'D' || input == 'd')
        {
            valid_move = check_valid_move(maze, player_row, player_col + 1);
            if (valid_move == 1)
            {
                maze[player_row][player_col] = '.';
                player_col = player_col + 1;
            }
            else
                printf("Invalid! Please try again: ");
        }
        else
            printf("Invalid! Please try again: ");
    } while (valid_move == 0);

    maze[player_row][player_col] = '^';
}

int check_finish(char maze[ROWS][COLS], int end_row, int end_col)
{
    int player_row, player_col;

    int found = 0;
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (maze[i][j] == '^')
            {
                player_row = i;
                player_col = j;
                found = 1;
                break;
            }
        }
        if (found == 1)
            break;
    }

    if (end_row == player_row && end_col == player_col)
        return 1;
    return 0;
}