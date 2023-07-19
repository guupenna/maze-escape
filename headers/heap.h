
#ifndef _HEAP_H_
#define _HEAP_H_

#include "hash.h"

typedef struct Heap Heap;

// a funcao de comparacao para o heap está dentro da hash table
Heap *heap_construct(HashTable *h);

void *heap_push(Heap *heap, void *data, double priority);

bool heap_empty(Heap *heap);

void *heap_min(Heap *heap);

double heap_min_priority(Heap *heap);

void *heap_pop(Heap *heap);

void heap_destroy(Heap *heap);

void heap_print(Heap *heap, void (*print_generic)(void *));

#endif