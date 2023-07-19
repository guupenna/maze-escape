#include <stdlib.h>
#include <stdio.h>

#include "heap.h"

#define HEAP_GROWTH 20

typedef struct
{
    void *data;
    double priority;
} HeapNode;

struct Heap
{
    HashTable *hash;
    HeapNode *nodes;
    int size;
    int capacity;
};

int _heapify_up(Heap *heap, int index)
{
    int child = index;
    int parent = (int)((child - 1)/2);

    while (heap->nodes[parent].priority > heap->nodes[child].priority)
    {
        HeapNode aux = heap->nodes[parent];
        heap->nodes[parent] = heap->nodes[child];
        heap->nodes[child] = aux;

        int *ptrChild = (int *)malloc(sizeof(int));
        *ptrChild = child;
        int *ptrChildDestroy = hash_table_set(heap->hash, heap->nodes[child].data, ptrChild);
        free(ptrChildDestroy);

        child = parent;
        parent = (int)((child - 1)/2);

        if (child == 0) break;
    }

    return child;
}

int _heapify_down(Heap *heap)
{
    int parent = 0, left = 1, right = 2, child = 0;

    while ((heap->nodes[parent].priority > heap->nodes[left].priority) || (heap->nodes[parent].priority > heap->nodes[right].priority))
    {
        if (heap->nodes[left].priority <= heap->nodes[right].priority)
        {
            child = left;
        }
        else if (heap->nodes[right].priority < heap->nodes[left].priority)
        {
            child = right;
        }
        
        HeapNode aux = heap->nodes[parent];
        heap->nodes[parent] = heap->nodes[child];
        heap->nodes[child] = aux;

        int *ptrParent = (int *)malloc(sizeof(int));
        *ptrParent = parent;
        int *ptrParentDestroy = hash_table_set(heap->hash, heap->nodes[parent].data, ptrParent);
        free(ptrParentDestroy);

        parent = child;
        left = 2*parent + 1;
        right = 2*parent + 2;

        if (left >= heap->size-1) break;
    }

    return child;
}

Heap *heap_construct(HashTable *h)
{
    Heap *heap = (Heap *)malloc(sizeof(Heap));

    heap->nodes = (HeapNode *)calloc(HEAP_GROWTH, sizeof(HeapNode));
    heap->size = 0;
    heap->capacity = HEAP_GROWTH;
    heap->hash = h;

    return heap;
}

void *heap_push(Heap *heap, void *data, double priority)
{
    int *index = hash_table_get(heap->hash, data);

    if (index == NULL)
    {
        heap->nodes[heap->size].data = data;
        heap->nodes[heap->size].priority = priority;

        index = (int *)malloc(sizeof(int));
        *index = _heapify_up(heap, heap->size);
        heap->size++;
        
        hash_table_set(heap->hash, data, index);

        if (heap->size == heap->capacity)
        {
            heap->capacity += HEAP_GROWTH;
            heap->nodes = (HeapNode *)realloc(heap->nodes, heap->capacity * sizeof(HeapNode));
        }

        return NULL;
    }

    if (priority < heap->nodes[*index].priority)
    {
        heap->nodes[*index].priority = priority;
        *index = _heapify_up(heap, *index);
        hash_table_set(heap->hash, data, index);
    }

    return data;
}

double heap_min_priority(Heap *heap)
{
    return heap->nodes[0].priority;
}

void *heap_pop(Heap *heap)
{
    HeapNode node = heap->nodes[0];

    int *indexPop = hash_table_pop(heap->hash, node.data);
    free(indexPop);
    
    heap->nodes[0] = heap->nodes[heap->size-1];

    heap->size--;

    int *index = (int *)malloc(sizeof(int));
    *index = _heapify_down(heap);
    int *indexDestroy = hash_table_set(heap->hash, heap->nodes[*index].data, index);
    free(indexDestroy);

    return node.data;
}

bool heap_empty(Heap *heap)
{
    if (heap->size == 0) return 1;

    return 0;
}

void heap_destroy(Heap *heap)
{
    free(heap->nodes);
    free(heap);
}

// void heap_print(Heap *heap, void (*print_generic)(void *))
// {
//     for (int i = 0; i < heap->size; i++)
//     {
//         printf("indice: %d\n", i);
//         printf("cel -> ");
//         print_generic(heap->nodes[i].data);
//         printf("prio -> %.2lf\n\n", heap->nodes[i].priority);
//     }

//     printf("hash:\n");
//     hash_table_print(heap->hash, print_generic);
// }