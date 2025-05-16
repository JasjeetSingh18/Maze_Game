#ifndef SOLVER_H
#define SOLVER_H
#include "maze.h"
#include "BFS_queue.h"
#include "helper_functions.h"

//Function Decleration
typedef struct node 
{
    int position;
    struct node *next;
} node;

void maze_to_graph(char maze[ROWS][COLS], node *maze_list[ROWS*COLS]);

int find_path(node *maze_list[ROWS*COLS], int start_id, int end_id);

#endif