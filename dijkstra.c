#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct No {
    int adj; 
    int peso; 
    struct No *prox; 
} No;

typedef struct Vertice {
    int flag; 
    int distancia; 
    struct No *inicio; 
} Vertice;

void adicionarAresta(Vertice *g, int origem, int destino, int peso) {
    No *novo = (No*)malloc(sizeof(No));
    novo->adj = destino;
    novo->peso = peso;
    novo->prox = g[origem].inicio;
    g[origem].inicio = novo;
}

void inicializarDistancias(Vertice *g, int numVertices, int origem) {
    for (int i = 0; i < numVertices; i++) {
        if (i == origem) {
            g[i].distancia = 0; 
        } else {
            g[i].distancia = INT_MAX; 
        }
    }
}

void relaxarAresta(Vertice *g, int u, int v, int peso) {
    if (g[u].distancia != INT_MAX && g[v].distancia > g[u].distancia + peso) {
        g[v].distancia = g[u].distancia + peso;
    }
}

int encontrarVerticeMaisProximo(Vertice *g, int numVertices) {
    int minDistancia = INT_MAX;
    int verticeMaisProximo = -1;

    for (int i = 0; i < numVertices; i++) {
        if (g[i].flag == 0 && g[i].distancia < minDistancia) {
            minDistancia = g[i].distancia;
            verticeMaisProximo = i;
        }
    }

    return verticeMaisProximo;
}

void dijkstra(Vertice *g, int numVertices, int origem) {
    inicializarDistancias(g, numVertices, origem);

    for (int i = 0; i < numVertices - 1; i++) {
        int u = encontrarVerticeMaisProximo(g, numVertices);
        g[u].flag = 1;

        No *p = g[u].inicio;
        while (p != NULL) {
            relaxarAresta(g, u, p->adj, p->peso);
            p = p->prox;
        }
    }
}

void imprimirDistancias(Vertice *g, int numVertices, int origem) {
    printf("Distâncias mínimas do vértice %d:\n", origem);
    for (int i = 0; i < numVertices; i++) {
        printf("Para o vértice %d: %d\n", i, g[i].distancia);
    }
}

int main() {
    int numVertices = 6; 
    Vertice grafo[numVertices]; 

    for (int i = 0; i < numVertices; i++) {
        grafo[i].inicio = NULL;
        grafo[i].flag = 0;
    }

    adicionarAresta(grafo, 0, 1, 2);
    adicionarAresta(grafo, 0, 2, 4);
    adicionarAresta(grafo, 1, 2, 1);
    adicionarAresta(grafo, 1, 3, 7);
    adicionarAresta(grafo, 2, 3, 3);
    adicionarAresta(grafo, 2, 4, 5);
    adicionarAresta(grafo, 3, 4, 1);
    adicionarAresta(grafo, 3, 5, 2);
    adicionarAresta(grafo, 4, 5, 3);

    int origem = 0; 

    dijkstra(grafo, numVertices, origem);
    imprimirDistancias(grafo, numVertices, origem); 

    for (int i = 0; i < numVertices; i++) {
        No *p = grafo[i].inicio;
        while (p != NULL) {
            No *aux = p;
            p = p->prox;
            free(aux);
        }
    }

    return 0;
}
