#include <stdlib.h>
#include <stdio.h>
#define MAX_VERTICES 10

typedef struct{
    int matrix[MAX_VERTICES][MAX_VERTICES];
    int vertices;
    int is_directed;
} Graph;


void init_graph(Graph* graph, int is_directed, int v){
    graph->vertices = v;
    for(int i = 0; i < v; i++){
        for(int j = 0; j < v; j++){
            graph->matrix[i][j] = 0;
        }
    }
    if(is_directed) graph->is_directed = 1;
    else graph->is_directed = 0;
}

void add_edge(Graph* graph, int from, int to, int weight){
    graph->matrix[from][to] = weight;
    if(!graph->is_directed){
        graph->matrix[to][from] = weight;
    }
}