
#ifndef _DEQUE_H_
#define _DEQUE_H_

typedef struct Deque Deque;

typedef void * data_type;

// criacao do deque
Deque *deque_construct(void);

// funcoes para insercao na direita e esquerda (devem ser feitas em O(1), com eventual realloc)
void deque_push_back(Deque *d, void *val);
void deque_push_front(Deque *d, void *val);

void deque_realloc(Deque *d);

// funcoes para remocao na direita e esquerda (devem ser feitas em O(1))
void *deque_pop_back(Deque *d);
void *deque_pop_front(Deque *d);

// numero de elementos
int deque_size(Deque *d);

// obtem o i-esimo elemento
void *deque_get(Deque *d, int idx);

// libera o espaco alocado para o deque
void deque_destroy(Deque *d);

void deque_print(Deque *deque, void (*print_generic)(void *));

#endif