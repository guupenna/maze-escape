
#include <stdio.h>
#include <stdlib.h>

#include "deque.h"

#define BLOCKS_GROWTH 5
#define ARRAY_SIZE 10

struct Deque {
    data_type **blocks;
    int blockStart, blockEnd;
    int itemStart, itemEnd;
    int size;
    int allocd;
};

Deque *deque_construct()
{
    Deque *deque = (Deque *)malloc(sizeof(Deque));

    deque->blocks = (data_type **)calloc(BLOCKS_GROWTH, sizeof(data_type *));

    deque->blockStart = deque->blockEnd = BLOCKS_GROWTH/2;
    deque->itemStart = deque->itemEnd = 0;
    deque->size = 0;
    deque->allocd = BLOCKS_GROWTH;

    return deque;
}

void deque_push_back(Deque *d, void *value)
{
    if ((d->blockEnd >= d->allocd) && (d->itemEnd == 0))
    {
        if (d->blockStart > 0)
        {
            int diff = (d->allocd - (d->blockEnd - d->blockStart) + 1) / 2;

            for (int i = d->blockStart; i < d->blockEnd; i++)
            {
                d->blocks[i - diff] = d->blocks[i];
            }

            d->blockStart -= diff;
            d->blockEnd -= diff;

            for (int i = d->blockEnd; i < d->allocd; i++) d->blocks[i] = NULL;
        }
        else deque_realloc(d);
    }

    if (d->blocks[d->blockEnd] == NULL)
    {
        d->blocks[d->blockEnd] = (data_type *)calloc(ARRAY_SIZE, sizeof(data_type));
    }

    d->blocks[d->blockEnd][d->itemEnd] = value;
    d->itemEnd = (d->itemEnd+1) % ARRAY_SIZE;

    if (d->itemEnd == 0) d->blockEnd++;
    d->size++;
}

void deque_push_front(Deque *d, void *value)
{
    if ((d->blockStart == 0) && (d->itemStart == 0))
    {
        if (d->blockEnd < d->allocd-1)
        {
            int diff = (d->allocd - (d->blockEnd - d->blockStart) + 1) / 2;

            for (int i = d->blockEnd; i >= d->blockStart; i--)
            {
                d->blocks[i + diff] = d->blocks[i];
            }

            d->blockStart += diff;
            d->blockEnd += diff;

            for (int i = 0; i < d->blockStart; i++) d->blocks[i] = NULL;
        }
        else deque_realloc(d);
    }

    if (d->itemStart == 0)
    {
        d->blockStart--;
        d->itemStart = ARRAY_SIZE-1;
    } else d->itemStart--;

    if (d->blocks[d->blockStart] == NULL)
    {
        d->blocks[d->blockStart] = (data_type *)calloc(ARRAY_SIZE, sizeof(data_type));
    }

    d->blocks[d->blockStart][d->itemStart] = value;
    d->size++;
}

void deque_realloc(Deque *d)
{
    d->allocd += BLOCKS_GROWTH;

    data_type **newBlocks = (data_type **)calloc(d->allocd, sizeof(data_type *));

    int diff = BLOCKS_GROWTH/2;

    for (int i = d->blockStart; i <= d->blockEnd; i++)
    {
        if (i == d->blockEnd && d->itemEnd == 0) break;

        newBlocks[i + diff] = d->blocks[i];
    }

    free(d->blocks);
    d->blocks = newBlocks;

    d->blockStart += diff;
    d->blockEnd += diff;
}

void *deque_pop_back(Deque *d)
{

    if (d->itemEnd == 0)
    {
        d->itemEnd = ARRAY_SIZE-1;
        d->blockEnd--;
    }
    else d->itemEnd--;

    d->size--;

    data_type value = d->blocks[d->blockEnd][d->itemEnd];

    return value;
}

void *deque_pop_front(Deque *d)
{
    data_type value = d->blocks[d->blockStart][d->itemStart];

    if (d->itemStart == ARRAY_SIZE-1)
    {
        free(d->blocks[d->blockStart]);
        d->blocks[d->blockStart] = NULL;
        d->itemStart = 0;
        d->blockStart++;
    }
    else d->itemStart++;

    d->size--;
    
    return value;
}

int deque_size(Deque *d)
{
    return d->size;
}

void *deque_get(Deque *d, int idx)
{
    int count = 0;

    for (int i = d->blockStart; i <= d->blockEnd; i++)
    {
        int start = 0, end = ARRAY_SIZE;

        if (i == d->blockStart) start = d->itemStart;
        if (i == d->blockEnd) end = d->itemEnd;

        for (int j = start; j < end; j++)
        {
            if (count == idx) return d->blocks[i][j];

            count++;
        }
    }

    return NULL;
}

void deque_destroy(Deque *d)
{
    for (int i = d->blockStart; i <= d->blockEnd; i++)
    {
        if (i == d->blockEnd && d->itemEnd == 0)
        {
            free(d->blocks[i]);
            break;
        }

        if (d->size > 0)
        {
            int start = 0, end = ARRAY_SIZE;

            if (i == d->blockStart) start = d->itemStart;
            if (i == d->blockEnd) end = d->itemEnd;

            for (int j = start; j < end; j++)
            {
                free(d->blocks[i][j]);
            }
        }

        free(d->blocks[i]);
    }

    free(d->blocks);
    free(d);
}

void deque_print(Deque *d, void (*print_generic)(void *))
{
    printf("blockstart: %d - blockend: %d - start: %d - end: %d - size: %d\n", d->blockStart, d->blockEnd, d->itemStart, d->itemEnd, d->size);

    for (int i = d->blockStart; i <= d->blockEnd; i++)
    {
        printf("bloco %d:\n", i);
        int start = 0, end = ARRAY_SIZE;

        if (i == d->blockStart) start = d->itemStart;
        if (i == d->blockEnd) end = d->itemEnd;

        for (int j = start; j < end; j++)
        {
            print_generic(d->blocks[i][j]);
        }
    }
}