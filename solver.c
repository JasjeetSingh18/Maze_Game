#include "solver.h"
#include <stdlib.h>
#include <stdio.h>

node *newNode(int position)
{
    node *temp = NULL;

    // Construct the new node
    temp = (node *)calloc(1, sizeof(node));
    if (temp == NULL)
        return NULL;

    // Add the correct cotents of the node
    temp->position = position;
    temp->next = NULL;

    return temp;
}

node *insertNode(node *head, node *new_node)
{
    node *traverse = head;
    if (head == NULL)
        return new_node;

    while (traverse->next != NULL)
    {
        traverse = traverse->next;
    }
    traverse->next = new_node;
    return head;
}

void maze_to_graph(char maze[ROWS][COLS], node *maze_list[ROWS * COLS])
{
    node *temp = NULL;
    int current_id;
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (maze[i][j] == '#')
                continue;
            current_id = i * COLS + j;
            if (i - 1 >= 0 && maze[i - 1][j] != '#')
            {
                temp = newNode((i - 1) * COLS + j);
                maze_list[current_id] = insertNode(maze_list[current_id], temp);
            }
            if (j + 1 < COLS && maze[i][j + 1] != '#')
            {
                temp = newNode((i)*COLS + j + 1);
                maze_list[current_id] = insertNode(maze_list[current_id], temp);
            }
            if (i + 1 < ROWS && maze[i + 1][j] != '#')
            {
                temp = newNode((i + 1) * COLS + j);
                maze_list[current_id] = insertNode(maze_list[current_id], temp);
            }
            if (j - 1 >= 0 && maze[i][j - 1] != '#')
            {
                temp = newNode((i)*COLS + j - 1);
                maze_list[current_id] = insertNode(maze_list[current_id], temp);
            }
        }
    }
}

int find_path(node *maze_list[ROWS * COLS], int start_id, int end_id)
{
    int current;

    int visited[ROWS * COLS];
    int distance[ROWS * COLS];

    // Clear both lists to ensure no junk is left
    clear_list(visited, ROWS * COLS, 0);
    clear_list(distance, ROWS * COLS, -1);

    // New Queue
    queue *head_queue = NULL;
    head_queue = enqueue(head_queue, new_queue(start_id));

    visited[start_id] = 1;
    distance[start_id] = 0;

    node *head_node = NULL;

    while (head_queue != NULL)
    {
        head_queue = dequeue(head_queue, &current);
        head_node = maze_list[current];

        while (head_node != NULL)
        {
            if (visited[head_node->position] != 1)
            {
                visited[head_node->position] = 1;
                distance[head_node->position] = distance[current] + 1;
                head_queue = enqueue(head_queue, new_queue(head_node->position));
            }
            head_node = head_node->next;
        }

        if (current == end_id)
            break;
    }

    freeQueue(head_queue);
    return distance[end_id];
}