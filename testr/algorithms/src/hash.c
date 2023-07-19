
#include <stdlib.h>
#include <stdio.h>

#include "../headers/hash.h"
#include "../headers/forward_list.h"

struct HashTable {
    ForwardList **buckets;
    HashFunction hash;
    CmpFunction compare;
    int tableSize;
    int numberElements;
};

struct HashTableIterator {
    HashTable *hashTable;
    int currentBucket;
    int currentElement;
    Node *currentNode;
};

void _hash_pair_print(HashTableItem *pair, void (*print_generic)(void *))
{
    printf("cel -> ");
    print_generic(pair->key);

    int *value = (int *)pair->val;
    printf("val -> ");
    printf("%d\n\n", *value);
}

HashTableItem *hash_pair_construct(void *key, void *value)
{
    HashTableItem *pair = (HashTableItem *)calloc(1, sizeof(HashTableItem));

    pair->key = key;
    pair->val = value;

    return pair;
}

HashTableItem *hash_table_get_pair(HashTable *h, void *key)
{
    int index = h->hash(h, key);
    HashTableItem *pairReturn = NULL;
    ForwardListIterator *itList = NULL;

    if (h->buckets[index] != NULL)
    {
        itList = forward_list_iterator_construct(h->buckets[index]);
    } else {
        return NULL;
    }

    while (!forward_list_iterator_is_over(itList))
    {
        HashTableItem *pairCompare = forward_list_iterator_next(itList);

        if (!h->compare(key, pairCompare->key))
        {
            pairReturn = pairCompare;
            break;
        }
    }

    forward_list_iterator_destroy(itList);

    return pairReturn;
}

void hash_pair_destroy(HashTableItem *pair)
{
    free(pair);
}

HashTable *hash_table_construct(int tableSize, HashFunction hash, CmpFunction compare)
{
    HashTable *h = (HashTable *)calloc(1, sizeof(HashTable));

    h->buckets = (ForwardList **)calloc(tableSize, sizeof(ForwardList *));
    h->hash = hash;
    h->compare = compare;
    h->tableSize = tableSize;
    h->numberElements = 0;

    return h;
}

void *hash_table_set(HashTable *h, void *key, void *value)
{
    HashTableItem *pair = hash_table_get_pair(h, key);

    int index = h->hash(h, key);

    if (pair != NULL)
    {
        void *valuePrev = pair->val;
        pair->val = value;
        return valuePrev;
    } else if (h->buckets[index] == NULL) {
        h->buckets[index] = forward_list_construct();
    }

    forward_list_push_front(h->buckets[index], hash_pair_construct(key, value));
    h->numberElements++;

    return NULL;
}

void *hash_table_get(HashTable *h, void *key)
{
    HashTableItem *pair = hash_table_get_pair(h, key);

    if (pair != NULL)
    {
        return pair->val;
    }

    return NULL;
}

void *hash_table_pop(HashTable *h, void *key)
{
    HashTableItem *pair = hash_table_get_pair(h, key);

    if (pair != NULL)
    {
        int index = h->hash(h, key);
        void *value = pair->val;
        forward_list_remove(h->buckets[index], pair);

        if (forward_list_head(h->buckets[index]) == NULL)
        {
            forward_list_destroy(h->buckets[index]);
            h->buckets[index] = NULL;
        }

        h->numberElements--;

        return value;
    }

    return NULL;
}

int hash_table_size(HashTable *h)
{
    return h->tableSize;
}

void hash_table_destroy(HashTable *h) 
{
    for (int i = 0; i < h->tableSize; i++)
    {  
        if (h->buckets[i] != NULL)
        {
            ForwardListIterator *itList = forward_list_iterator_construct(h->buckets[i]);

            while (!forward_list_iterator_is_over(itList))
            {
                HashTableItem *pair = forward_list_iterator_next(itList);
                hash_pair_destroy(pair);
            }
            forward_list_iterator_destroy(itList);
            
            forward_list_destroy(h->buckets[i]);
        }
    }
    
    free(h->buckets);
    free(h);
}

void hash_table_print(HashTable *h, void (*print_generic)(void *))
{
    for (int i = 0; i < h->tableSize; i++)
    {  
        if (h->buckets[i] != NULL)
        {
            ForwardListIterator *itList = forward_list_iterator_construct(h->buckets[i]);

            printf("bucket: %d\n", i);

            while (!forward_list_iterator_is_over(itList))
            {
                HashTableItem *pair = forward_list_iterator_next(itList);
                _hash_pair_print(pair, print_generic);
            }
            forward_list_iterator_destroy(itList);
        }
    }
}   

HashTableIterator *hash_table_iterator(HashTable *h)
{
    HashTableIterator *it = (HashTableIterator *)calloc(1, sizeof(HashTableIterator));

    it->hashTable = h;
    it->currentBucket = 0;
    it->currentElement = 0;
    it->currentNode = NULL;

    while (it->currentBucket < h->tableSize)
    {
        if (h->buckets[it->currentBucket] != NULL)
        {
            it->currentNode = forward_list_head(h->buckets[it->currentBucket]);
            it->currentElement++;
            break;
        }

        it->currentBucket++;
    }

    return it;
}

bool hash_table_iterator_is_over(HashTableIterator *it)
{
    if (it->currentElement > it->hashTable->numberElements)
    {
        return 1;
    }

    return 0;
}

HashTableItem *hash_table_iterator_next(HashTableIterator *it)
{
    if (it->currentNode == NULL)
    {
        do
        {
            it->currentBucket++;
        } while (it->hashTable->buckets[it->currentBucket] == NULL);

        it->currentNode = forward_list_head(it->hashTable->buckets[it->currentBucket]);
    }
    HashTableItem *pair = node_value(it->currentNode);

    it->currentNode = node_next(it->currentNode);
    it->currentElement++;

    return pair;
}

void hash_table_iterator_destroy(HashTableIterator *it)
{
    free(it);
}