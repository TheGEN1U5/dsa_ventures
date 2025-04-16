#include <stdlib.h>
#include <stdio.h>
#include "pqp.h"
#include "graph.h"


node** prim_MST(Graph* graph){
    int v = graph->vertices;
    PriorityQueue pq; initQueue(&pq);
    node** MST = (node**) malloc((v - 1) * sizeof(node*));
    node* new_node = create_node(0, 0, -1);
    insert(&pq, new_node);
    int c = 0;
    int visited[v]; for(int i = 0; i < v; i++) visited[i] = 0;
    while(!isEmpty(&pq)){
        node* min = extractMin(&pq);
        if(!visited[min->index]){
            visited[min->index] = 1;
            if(min->parent != -1){
                MST[c] = min; c++;
            }
            for(int i = 0; i < v; i++){
                if(graph->matrix[min->index][i] && !visited[i]){
                    insert(&pq, create_node(i, graph->matrix[min->index][i], min->index));
                }
            }
        }else{
            free(min);
        }
    }
    return MST;
}

int main(void){
    // Graph uag;
    // init_graph(&uag, 0, 5);
    // add_edge(&uag, 0, 1);
    // add_edge(&uag, 0, 4);
    // add_edge(&uag, 1, 2);
    // add_edge(&uag, 1, 3);
    // add_edge(&uag, 1, 4);
    // add_edge(&uag, 2, 3);
    // add_edge(&uag, 3, 4);
    // // bfs(&uag);
    // // prim_MST(uag);
    // Graph dg;
    // init_graph(&dg, 1, 7);
    // add_edge(&dg, 0, 1);
    // add_edge(&dg, 0, 4);
    // add_edge(&dg, 1, 2);
    // add_edge(&dg, 4, 1);
    // add_edge(&dg, 4, 3);
    // add_edge(&dg, 5, 2);
    // add_edge(&dg, 5, 4);
    // add_edge(&dg, 6, 5);
    // dfs(&dg);

    Graph ucg;
    init_graph(&ucg, 0, 9);
    add_edge(&ucg, 0, 1, 4);
    add_edge(&ucg, 0, 7, 8);
    add_edge(&ucg, 1, 2, 8);
    add_edge(&ucg, 1, 7, 11);
    add_edge(&ucg, 2, 3, 7);
    add_edge(&ucg, 2, 5, 4);
    add_edge(&ucg, 2, 8, 2);
    add_edge(&ucg, 3, 4, 9);
    add_edge(&ucg, 3, 5, 14);
    add_edge(&ucg, 4, 5, 10);
    add_edge(&ucg, 5, 6, 2);
    add_edge(&ucg, 6, 7, 1);
    add_edge(&ucg, 6, 8, 6);
    add_edge(&ucg, 7, 8, 7);
    node** MST = prim_MST(&ucg);
    for(int i = 0, v = ucg.vertices - 1; i < v; i++){
        printf("%d-%d  %d\n", MST[i]->parent, MST[i]->index, MST[i]->weight);
    }
}