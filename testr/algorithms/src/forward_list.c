#include <stdlib.h>
#include <stdio.h>

#include "../headers/forward_list.h"
#include "../headers/hash.h"

Node *node_construct(data_type value, Node *next)
{
    Node *node = (Node *)malloc(sizeof(Node));

    node->value = value;
    node->next = next;

    return node;
}

data_type node_value(Node *node)
{
    return node->value;
}

Node *node_next(Node *node)
{
    return node->next;
}

void node_destroy(Node *node)
{
    free(node);
}

ForwardList *forward_list_construct()
{
    ForwardList *list = (ForwardList *)calloc(1, sizeof(ForwardList));

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;

    return list;
}

void forward_list_push_front(ForwardList *list, data_type value)
{
    Node *node = node_construct(value, list->head);

    if (list->size == 0)
    {
        list->tail = list->head = node;
    } else {
        list->head = node;
    }

    list->size++;
}

void forward_list_push_back(ForwardList *list, data_type value)
{
    Node *node = node_construct(value, NULL);

    if (list->size == 0)
    {
        list->head = list->tail = node;

    } else {
        list->tail = list->tail->next = node;
    }

    list->size++;
}

void forward_list_print(ForwardList *list, void (*print_fn)(data_type))
{
    Node *node = list->head;

    while (node != NULL)
    {
        print_fn(node->value);
        node = node->next;
    }
}

void forward_list_remove(ForwardList *list, data_type value)
{
    Node *node = list->head;
    Node *prev = node;

    while (node != NULL)
    {
        if (node->value == value)
        {
            if (node == list->head && node->next == NULL) list->head = NULL;
            prev->next = node->next;

            node_destroy(node);
            list->size--;
            return;
        } else {
            prev = node;
            node = node->next;
        }
    }
}

void forward_list_destroy(ForwardList *list)
{
    Node *node = list->head;

    while (node != NULL)
    {
        Node *next = node->next;

        node_destroy(node);
        node = next;
    }

    free(list);
}

Node *forward_list_head(ForwardList *l)
{
    return l->head;
}

ForwardListIterator *forward_list_iterator_construct(ForwardList *l)
{
    ForwardListIterator *it = (ForwardListIterator *)malloc(sizeof(ForwardListIterator));

    it->current = l->head;

    return it;
}

void *forward_list_iterator_next(ForwardListIterator *it)
{
    Node *node = it->current;

    it->current = it->current->next;

    return node->value;
}

bool forward_list_iterator_is_over(ForwardListIterator *it)
{
    if (it->current == NULL)
    {
        return 1;
    }

    return 0;
}

void forward_list_iterator_destroy(ForwardListIterator *it)
{
    free(it);
}