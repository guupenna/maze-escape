
#ifndef _MY_FORWARD_LIST_H_
#define _MY_FORWARD_LIST_H_

#include "types.h"

typedef void *data_type;

typedef struct Node
{
    data_type value;
    struct Node *next;
} Node;

Node *node_construct(data_type value, Node *next);

data_type node_value(Node *n);

Node *node_next(Node *node);

void node_destroy(Node *n);

typedef struct
{
    Node *head;
    Node *tail;
    int size;
} ForwardList;

typedef struct
{
    Node *current;
} ForwardListIterator;

ForwardList *forward_list_construct();

int forward_list_size(ForwardList *l);

data_type forward_list_find(ForwardList *l, void *key, int (*cmp_fn)(data_type data, void *key));

void forward_list_push_front(ForwardList *l, data_type data);

void forward_list_push_back(ForwardList *l, data_type data);

void forward_list_print(ForwardList *l, void (*print_fn)(data_type));

void forward_list_remove(ForwardList *l, data_type data);

void forward_list_destroy(ForwardList *l);

Node *forward_list_head(ForwardList *l);

ForwardListIterator *forward_list_iterator_construct(ForwardList *l);

void *forward_list_iterator_next(ForwardListIterator *it);

bool forward_list_iterator_is_over(ForwardListIterator *it);

void forward_list_iterator_destroy(ForwardListIterator *it);

// data_type forward_list_get(ForwardList *l, int i);

// data_type forward_list_pop_front(ForwardList *l);

// ForwardList *forward_list_reverse(ForwardList *l);

// void forward_list_clear(ForwardList *l);

// void forward_list_unique(ForwardList *l);

// void forward_list_cat(ForwardList *l, ForwardList *m);

// forward_list_sort(ForwardList *l);

#endif