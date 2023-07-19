
#include <stdlib.h>
#include <stdio.h>

#include "../headers/stack.h"
#include "../headers/deque.h"

struct Stack {
    Deque *deque;
};

Stack *stack_construct()
{
    Stack *stack = (Stack *)calloc(1, sizeof(Stack));

    stack->deque = deque_construct();

    return stack;
}

void stack_push(Stack *stack, void *data)
{
    deque_push_back(stack->deque, data);
}

bool stack_empty(Stack *stack)
{
    if (deque_size(stack->deque) == 0)
    {
        return 1;
    }

    return 0;
}

int stack_size(Stack *stack)
{
    return deque_size(stack->deque);
}

void *stack_pop(Stack *stack)
{
    if (stack_empty(stack))
    {
        exit(printf("ERRO: Não foi possível dar pop pois a pilha está vazia.\n"));
    }

    void *value = deque_pop_back(stack->deque);

    return value;
}

void stack_destroy(Stack *stack)
{
    deque_destroy(stack->deque);
    free(stack);
}