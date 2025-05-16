#include "maze.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

char mazes[3][25][25];
char maze[25][25];
int maze_count = 0;

int load_mazes(const char *filename)
{
    FILE *f = fopen(filename, "r");
    if (!f)
    {
        perror("fopen");
        return 0;
    }

    char line[COLS + 2]; // room for newline + '\0'
    int row = 0;
    while (fgets(line, sizeof(line), f))
    {
        // blank line = end of one maze
        if (line[0] == '\n' || line[0] == '\r')
        {
            if (row == ROWS)
            {
                maze_count++;
                row = 0;
                if (maze_count >= 10)
                    break;
            }
            continue;
        }
        // strip newline
        line[COLS] = '\0';
        // copy into current maze
        if (row < ROWS && maze_count < 10)
        {
            strcpy(mazes[maze_count][row], line);
            row++;
        }
    }
    // last maze (if no blank line at end)
    if (row == ROWS && maze_count < 10)
        maze_count++;
    fclose(f);
    return maze_count;
}

// Picks one at random into the live maze[][]
void pick_random_maze(char maze[ROWS][COLS])
{
    if (maze_count == 0)
        return;
    srand((unsigned)time(NULL));
    int pick = rand() % maze_count;
    for (int r = 0; r < ROWS; r++)
    {
        strcpy(maze[r], mazes[pick][r]);
    }
}
