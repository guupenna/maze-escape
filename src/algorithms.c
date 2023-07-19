
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../headers/algorithms.h"
#include "../headers/queue.h"
#include "../headers/stack.h"
#include "../headers/heap.h"

typedef struct Node {
    Celula pos;
    struct Node *prev;
} Node;

void _print_generic(void *data)
{
    Celula *c = (Celula *)data;
    printf("x: %d - y: %d\n", c->x, c->y);
}

Node *_node_construct(Celula pos, Node *prev)
{
    Node *node = (Node *)malloc(sizeof(Node));

    node->pos = pos;
    node->prev = prev;

    return node;
}

ResultData _default_result()
{
    ResultData result;

    result.caminho = NULL;
    result.custo_caminho = 0;
    result.nos_expandidos = 0;
    result.tamanho_caminho = 0;
    result.sucesso = 0;

    return result;
}

void _bfs_expand_node(Node *current, Labirinto *l, Queue *to_expand, Queue *expanded)
{
    Celula neighbours[8] = {
        {-1, 0},
        {-1, 1},
        {0, 1},
        {1, 1},
        {1, 0},
        {1, -1},
        {0, -1},
        {-1, -1}

        // {0, 1},
        // {1, 1},
        // {1, 0},
        // {1, -1},
        // {0, -1},
        // {-1, -1},
        // {-1, 0},
        // {-1, 1}
    };

    for (int i = 0; i < 8; i++)
    {
        Celula cel;
        cel.x = current->pos.x + neighbours[i].x;
        cel.y = current->pos.y + neighbours[i].y;

        byte b = labirinto_obter(l, cel.x, cel.y);

        if (b == LIVRE)
        {
            Node *node = _node_construct(cel, current);

            labirinto_atribuir(l, cel.x, cel.y, FRONTEIRA);
            queue_push(to_expand, node);
        }
    }

    labirinto_atribuir(l, current->pos.x, current->pos.y, EXPANDIDO);
    queue_push(expanded, current);
}

void _dfs_expand_node(Node *current, Labirinto *l, Stack *to_expand, Stack *expanded)
{
    Celula neighbours[8] = {
        {-1, 0},
        {-1, 1},
        {0, 1},
        {1, 1},
        {1, 0},
        {1, -1},
        {0, -1},
        {-1, -1}

        // {0, 1},
        // {1, 1},
        // {1, 0},
        // {1, -1},
        // {0, -1},
        // {-1, -1},
        // {-1, 0},
        // {-1, 1}
    };

    for (int i = 0; i < 8; i++)
    {
        Celula cel;
        cel.x = current->pos.x + neighbours[i].x;
        cel.y = current->pos.y + neighbours[i].y;

        byte b = labirinto_obter(l, cel.x, cel.y);

        if (b == LIVRE)
        {
            Node *node = _node_construct(cel, current);

            labirinto_atribuir(l, cel.x, cel.y, FRONTEIRA);
            stack_push(to_expand, node);
        }
    }

    labirinto_atribuir(l, current->pos.x, current->pos.y, EXPANDIDO);
    stack_push(expanded, current);
}

void _path_reverse(Celula *path, int size)
{
    int end = size-1, half = size/2;

    for (int i = 0; i < half; i++)
    {
        Celula aux = path[i];
        path[i] = path[end - i];
        path[end - i] = aux;
    }
}

ResultData a_star(Labirinto *l, Celula inicio, Celula fim)
{
    // corrigir
    return _default_result();
}

ResultData breadth_first_search(Labirinto *l, Celula inicio, Celula fim)
{
    ResultData result = _default_result();

    Node *start_node = _node_construct(inicio, NULL), *end_node = NULL;

    Queue *to_expand = queue_construct();
    queue_push(to_expand, start_node);
    Queue *expanded = queue_construct();

    while (!queue_empty(to_expand))
    {
        Node *current = queue_pop(to_expand);
        result.nos_expandidos++;

        if (current->pos.x == fim.x && current->pos.y == fim.y)
        {
            result.sucesso = 1;
            queue_push(expanded, current);
            // free(end_node);
            end_node = current;
            break;
        }

        _bfs_expand_node(current, l, to_expand, expanded);
    }

    Node *path_node = end_node;
    Celula *path = (Celula *)calloc(queue_size(expanded), sizeof(Celula));
    int count, dx, dy;
    double cost = 0;

    if (result.sucesso == 1)
    {
        for (count = 0; path_node->prev != NULL; count++)
        {
            path[count] = path_node->pos;
            path_node = path_node->prev;
            dx = path_node->pos.x - path[count].x;
            dy = path_node->pos.y - path[count].y;
            cost += sqrt(pow(dx, 2) + pow(dy, 2));
        }
        _path_reverse(path, count);

        result.caminho = path;
        result.tamanho_caminho = count;
        result.custo_caminho = cost;
    }

    queue_destroy(to_expand);
    queue_destroy(expanded);

    return result;
}

ResultData depth_first_search(Labirinto *l, Celula inicio, Celula fim)
{
    ResultData result = _default_result();

    Node *start_node = _node_construct(inicio, NULL), *end_node = _node_construct(fim, NULL);

    Stack *to_expand = stack_construct();
    stack_push(to_expand, start_node);
    Stack *expanded = stack_construct();

    while (!stack_empty(to_expand))
    {
        // stack_print(to_expand, _print_generic);
        Node *current = stack_pop(to_expand);
        result.nos_expandidos++;

        if (current->pos.x == fim.x && current->pos.y == fim.y)
        {
            result.sucesso = 1;
            stack_push(expanded, current);
            free(end_node);
            end_node = current;
            break;
        }

        _dfs_expand_node(current, l, to_expand, expanded);
    }

    Node *path_node = end_node;
    Celula *path = (Celula *)malloc(stack_size(expanded) * sizeof(Celula));
    int count, dx = 0, dy = 0;
    double cost = 0.0;

    if (result.sucesso == 1)
    {
        for (count = 0; path_node->prev != NULL; count++)
        {
            path[count] = path_node->pos;
            path_node = path_node->prev;
            dx = path_node->pos.x - path[count].x;
            dy = path_node->pos.y - path[count].y;
            cost += sqrt(pow(dx, 2) + pow(dy, 2));
        }
        _path_reverse(path, count);

        result.caminho = path;
        result.tamanho_caminho = count;
        result.custo_caminho = cost;
    }

    // if (result.sucesso)
    // {
    //     int count = 0;
    //     while (path_node->prev != NULL)
    //     {
    //         path[count] = path_node->pos;
    //         path_node = path_node->prev;
    //         count++;

    //         dx = path_node->pos.x - path[count-1].x;
    //         dy = path_node->pos.y - path[count-1].y;
    //         custo += sqrt(pow(dx, 2) + pow(dy, 2));
    //     }
    //     _path_reverse(path, count);

    //     result.caminho = path;
    //     result.tamanho_caminho = count;
    //     result.custo_caminho = custo;
    // }

    stack_destroy(to_expand);
    stack_destroy(expanded);

    return result;
}

ResultData dummy_search(Labirinto *l, Celula inicio, Celula fim)
{
    int max_path_length = 0;
    float dx, dy;

    ResultData result = _default_result();

    max_path_length = abs(fim.x - inicio.x) + abs(fim.y - inicio.y);
    result.caminho = (Celula *)malloc(sizeof(Celula) * max_path_length);
    result.sucesso = 1;

    Celula atual = inicio;
    result.caminho[result.tamanho_caminho++] = atual;
    result.nos_expandidos++;

    while ((atual.x != fim.x) || (atual.y != fim.y))
    {
        dx = fim.x - atual.x;
        dy = fim.y - atual.y;

        if (dx != 0)
            dx /= fabs(dx);

        if (dy != 0)
            dy /= fabs(dy);

        atual.x += (int)dx;
        atual.y += (int)dy;

        if (labirinto_obter(l, atual.y, atual.x) == OCUPADO || (atual.x > labirinto_n_colunas(l) - 1) || (atual.y > labirinto_n_linhas(l) - 1) || (atual.x < 0) || (atual.y < 0))
        {
            result.sucesso = 0;
            free(result.caminho);
            result.caminho = NULL;
            return result;
        }

        result.caminho[result.tamanho_caminho++] = atual;
        result.nos_expandidos++;
        result.custo_caminho += sqrt(pow(dx, 2) + pow(dy, 2));
    }

    return result;
}

