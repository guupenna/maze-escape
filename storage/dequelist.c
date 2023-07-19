
#include <stdlib.h>
#include <stdio.h>

#include "../headers/deque.h"

typedef struct Node {
    struct Node *next;
    struct Node *prev;
    void *value;
} Node;

struct Deque {
    Node *head;
    Node *tail;
    int size;
};

Node *_node_construct(Node *next, Node *prev, void *value)
{
    Node *node = (Node *)malloc(sizeof(Node));

    node->next = next;
    node->prev = prev;
    node->value = value;

    return node;
}

void _node_destroy(Node *node)
{
    free(node->value);
    free(node);
}

Deque *deque_construct()
{
    Deque *deque = (Deque *)calloc(1, sizeof(Deque));

    deque->head = NULL;
    deque->tail = NULL;
    deque->size = 0;

    return deque; 
}

void deque_push_back(Deque *deque, void *value)
{
    Node *node = _node_construct(NULL, deque->tail, value);

    if (deque->tail == NULL)
    {
        deque->head = deque->tail = node;
    } else {
        deque->tail->next = node;

        deque->tail = node;
    }

    deque->size++;
}

void deque_push_front(Deque *deque, void *value)
{
    Node *node = _node_construct(deque->head, NULL, value);

    if (deque->head == NULL)
    {
        deque->head = deque->tail = node;
    } else {
        deque->head->prev = node;

        deque->head = node;
    }

    deque->size++;
}

void *deque_pop_back(Deque *deque)
{
    Node *node = deque->tail;

    if (deque->tail == NULL)
    {
        exit(printf("ERRO: Não foi possível executar o pop pois o deque está vazio.\n"));
    }

    deque->tail = deque->tail->prev;

    if (deque->tail == NULL)
    {
        deque->head = deque->tail;
    } else {
        deque->tail->next = NULL;
    }

    deque->size--;

    void *value = node->value;

    // diferencia o endereço value a ser retornado do armazenado no node, para poder liberá-lo sem afetar value
    node->value = NULL;
    _node_destroy(node);

    return value;
}

void *deque_pop_front(Deque *deque)
{
    Node *node = deque->head;

    if (deque->head == NULL)
    {
        exit(printf("ERRO: Não foi possível executar o pop pois o deque está vazio.\n"));
    }

    deque->head = deque->head->next;

    if (deque->head == NULL)
    {
        deque->tail = deque->head;
    } else {
        deque->head->prev = NULL;
    }
    
    deque->size--;

    void *value = node->value;

    node->value = NULL;

    _node_destroy(node);

    return value;
}

int deque_size(Deque *deque)
{
    return deque->size;
}

void deque_destroy(Deque *deque)
{
    Node *node = deque->head;

    while (node != NULL)
    {
        Node *aux = node->next;

        _node_destroy(node);
        node = aux;
    }

    free(deque);
}

void deque_print(Deque *deque, void (*print_generic)(void *))
{
    Node *node = deque->head;

    while (node != NULL)
    {
        void *p = node->value;
        print_generic(p);

        node = node->next;
    }
    printf("\n");
}