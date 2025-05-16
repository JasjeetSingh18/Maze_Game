#include "BFS_queue.h"
#include <stdlib.h>

queue *new_queue (int position)
{
    queue *temp_queue_node = NULL;
    temp_queue_node = (queue *)calloc(1, sizeof(queue));
    
    if (temp_queue_node == NULL) return NULL;
    temp_queue_node->position = position;
    temp_queue_node->next = NULL;

    return temp_queue_node;
}

queue *enqueue(queue *head_queue, queue *newQueue)
{
    if (head_queue == NULL) return newQueue; 
    queue *traversal = head_queue; 

    while (traversal->next != NULL) traversal = traversal->next;

    traversal->next = newQueue;

    return head_queue;
}

queue *dequeue(queue *head, int *position_out) {
    if (!head) return NULL;
    *position_out = head->position;
    queue *next = head->next;
    free(head);
    return next;
}

void freeQueue (queue *head_queue)
{
    queue *traverse = head_queue;
    queue *temp = NULL;
    while(traverse != NULL)
    {
        temp = traverse->next;
        free(traverse);
        traverse = temp;
    }
}