
#include <stdlib.h>
#include <stdio.h>

#include "../headers/queue.h"
#include "../headers/deque.h"

struct Queue {
    Deque *deque;
};

Queue *queue_construct()
{
    Queue *queue = (Queue *)calloc(1, sizeof(Queue));

    queue->deque = deque_construct();

    return queue;
}

void queue_push(Queue *queue, void *data)
{
    deque_push_back(queue->deque, data);
}

bool queue_empty(Queue *queue)
{
    if (deque_size(queue->deque) == 0)
    {
        return 1;
    }

    return 0;
}

int queue_size(Queue *queue)
{
    return deque_size(queue->deque);
}

void *queue_pop(Queue *queue)
{
    if (queue_empty(queue))
    {
        exit(printf("ERRO: Não foi possível dar pop pois a fila está vazia.\n"));
    }

    void *value = deque_pop_front(queue->deque);

    return value;
}

void queue_destroy(Queue *queue)
{
    deque_destroy(queue->deque);
    free(queue);
}