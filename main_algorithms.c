
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "headers/labirinto.h"
#include "headers/algorithms.h"

void print_result(ResultData *result)
{
    if (!result->sucesso)
    {
        printf("IMPOSSIVEL\n");
        return;
    }

    for (int i = 0; i < result->tamanho_caminho; i++)
        printf("%d %d\n", result->caminho[i].x, result->caminho[i].y);

    printf("%.2lf\n", result->custo_caminho);
    printf("%d\n", result->tamanho_caminho);
    printf("%d\n", result->nos_expandidos);
}

void mostra_caminho(Labirinto *l, ResultData *result, Celula inicio, Celula fim)
{
    if (result->sucesso)
    {
        for (int i = 0; i < result->tamanho_caminho; i++)
            labirinto_atribuir(l, result->caminho[i].x, result->caminho[i].y, CAMINHO);
    }

    labirinto_atribuir(l, inicio.x, inicio.y, INICIO);
    labirinto_atribuir(l, fim.x, fim.y, FIM);
    labirinto_print(l);
}

int main()
{
    char arquivo_labirinto[100];
    char algoritmo[100];
    Celula inicio, fim;
    ResultData result;
    Labirinto *lab;

    scanf("%s", arquivo_labirinto);
    scanf("%d %d", &inicio.x, &inicio.y);
    scanf("%d %d", &fim.x, &fim.y);
    scanf("\n%s", algoritmo);

    lab = labirinto_carregar(arquivo_labirinto);

    if (!strcmp(algoritmo, "BFS"))
        result = breadth_first_search(lab, inicio, fim);
    else if (!strcmp(algoritmo, "DFS"))
        result = depth_first_search(lab, inicio, fim);
    else if (!strcmp(algoritmo, "A*"))
        result = a_star(lab, inicio, fim);
    else if (!strcmp(algoritmo, "DUMMY"))
        result = dummy_search(lab, inicio, fim);
    else
    {
        printf("Algoritmo desconhecido: %s\n", algoritmo);
        exit(1);
    }

    print_result(&result);

    // descomente para visualizar informacoes de debug no labirinto
    mostra_caminho(lab, &result, inicio, fim);

    labirinto_destruir(lab);
    if (result.caminho != NULL)
        free(result.caminho);

    return 0;
}

    // int count;
    // float dx, dy, cost = 0;

    // if (result.sucesso)
    // {
    //     for (count = 0; path_node->prev != NULL; count++, path_node = path_node->prev)
    //     {
    //         path[count] = path_node->pos;
    //         dx = path_node->pos.x - path[count].x;
    //         dy = path_node->pos.y - path[count].y;
    //         cost += sqrt(pow(dx, 2) + pow(dy, 2));
    //     }
    //     _path_reverse(path, count);

    //     result.caminho = path;
    //     result.tamanho_caminho = count;
    //     result.custo_caminho = cost;
    // }