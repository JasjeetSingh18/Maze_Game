#ifndef BFS_QUEUE_H
#define BFS_QUEUE_H

typedef struct queue
{
    int position;
    struct queue *next;
} queue;

queue *new_queue (int position);

queue *enqueue(queue *head_queue, queue *newQueue);

queue *dequeue(queue *head, int *position_out);

void freeQueue (queue *head_queue);

#endif