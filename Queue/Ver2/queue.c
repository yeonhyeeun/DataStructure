#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "queue.h"

#define TRUE 1
#define FALSE 0

queue *create_queue(int capacity, int unit)
{
    queue *que = (queue *)malloc(sizeof(queue));
    que->capacity = capacity;
    que->unit = unit;
    que->buffer = calloc(capacity, unit);
    que->front = 0;
    que->rear = 0;
    que->full = FALSE;
    return que;
}

void delete_queue(queue *que)
{
    if (que->buffer != 0x0)
        free(que->buffer);

    free(que);
}

int enqueue(queue *que, void *elem)
{
    if (is_full(que))
        return FALSE;

    memcpy(que->buffer + que->rear * que->unit, elem, que->unit);
    que->rear = (que->rear + 1) % que->capacity;

    if (que->rear == que->front)
        que->full = TRUE;

    return TRUE;
}

int dequeue(queue *que, void *elem)
{
    if (is_empty(que))
        return FALSE;
    
    memcpy(elem, que->buffer + que->front * que->unit, que->unit);
    que->front = (que->front + 1) % que->capacity;
    que->full = FALSE;

    return TRUE;
}

int is_empty(queue *que)
{
    return (que->front == que->rear) && !(que->full);
}

int is_full(queue *que)
{
    return que->full;
}

void print_queue(queue *que, void (*print_element)(void *element))
{
    int i;
    for (i = que->front; i != que->rear; i = (i + 1) % que->capacity)
    {
        printf("[");
        print_element(que->buffer + i * que->unit);
        printf("] ");
    }
    printf("\n");
}