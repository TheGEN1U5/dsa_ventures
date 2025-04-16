#include <stdlib.h>
#include <stdio.h>
#include "myqueue.h"
#define MAX_VERTICES 10

typedef struct{
    int matrix[MAX_VERTICES][MAX_VERTICES];
    int vertices;
    int is_directed;
} Graph;

typedef struct{
    int parent;
    int d;
    int f;
    int color;
} node;

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

void add_edge(Graph* graph, int from, int to){
    graph->matrix[from][to] = 1;
    if(!graph->is_directed){
        graph->matrix[to][from] = 1;
    }
}


void bfs(Graph* graph){
    int v = graph->vertices;
    int bfs_mat[v][3];
    for(int i = 0; i < v; i++){
        bfs_mat[i][0] = INT_MIN;
        bfs_mat[i][1] = -1;
        bfs_mat[i][2] = 0;
    }
    // 0 -> parent, 1 -> distance, 2 -> color
    Queue frontier; init(&frontier);
    bfs_mat[0][1] = 0; // set distance of 0 to be 0
    bfs_mat[0][2] = 1; // set color of 0 to be gray
    enqueue(&frontier, 0);
    while(!is_empty(&frontier)){
        int node = front(&frontier); dequeue(&frontier);
        for(int i = 0; i < v; i++){
            if(graph->matrix[node][i] && bfs_mat[i][2] == 0){
                // parent of i is node
                bfs_mat[i][0] = node;
                // distance of(i) = distance of(parent of(i)) + 1 (where 1 is weight)
                bfs_mat[i][1] = bfs_mat[node][1] + 1;
                // set color of i to gray
                bfs_mat[i][2] = 1;
                enqueue(&frontier, i);
            }
        }
        // set node color to black since all children visited
        bfs_mat[node][2] = 2;
        printf("%d ", node);
    }
    printf("\n");
}

void dfs_visit(Graph* graph, int i, int* time, node* dfs_mat){
    dfs_mat[i].color = 1;
    *time = *time + 1;
    dfs_mat[i].d = *time;
    for(int j = 0, v = graph->vertices; j < v; j++){
        if(graph->matrix[i][j] && dfs_mat[j].color == 0){
            dfs_mat[j].parent = i;
            dfs_visit(graph, j, time, dfs_mat);
        }
    }
    dfs_mat[i].color = 2;
    *time  = *time + 1;
    dfs_mat[i].f = *time;
    printf("%d  %d/%d\n", i, dfs_mat[i].d, dfs_mat[i].f);
}

void dfs(Graph* graph){
    int v = graph->vertices;
    node dfs_mat[v];
    for(int i = 0; i < v; i++){
        dfs_mat[i].parent = INT_MIN; // parent
        dfs_mat[i].d = 0;            // discovered
        dfs_mat[i].f = 0;            // finished
        dfs_mat[i].color = 0;        // color
    }
    int time = 0;
    for(int i = 0; i < v; i++){
        if(dfs_mat[i].color == 0){
            dfs_visit(graph, i, &time, dfs_mat);
        }
    }

}

int main(void){
    Graph uag;
    init_graph(&uag, 0, 5);
    add_edge(&uag, 0, 1);
    add_edge(&uag, 0, 4);
    add_edge(&uag, 1, 2);
    add_edge(&uag, 1, 3);
    add_edge(&uag, 1, 4);
    add_edge(&uag, 2, 3);
    add_edge(&uag, 3, 4);
    // bfs(&uag);

    Graph dg;
    init_graph(&dg, 1, 7);
    add_edge(&dg, 0, 1);
    add_edge(&dg, 0, 4);
    add_edge(&dg, 1, 2);
    add_edge(&dg, 4, 1);
    add_edge(&dg, 4, 3);
    add_edge(&dg, 5, 2);
    add_edge(&dg, 5, 4);
    add_edge(&dg, 6, 5);
    dfs(&dg);
}