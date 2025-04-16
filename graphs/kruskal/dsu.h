#include <stdio.h>
#define MAX 15

typedef struct{
    int parents[MAX];
    int rank[MAX];
    int size;
} DSU;

int max(int a, int b){
    return a > b ? a : b;
}

void init_dsu(DSU* dsu, int size){
    for(int i = 0; i < MAX; i++){
        dsu->parents[i] = i;
        dsu->rank[i] = 0;
    }
    dsu->size = size;
}

int find(DSU* dsu, int a){
    if(a == dsu->parents[a]) return a;
    dsu->parents[a] = find(dsu, dsu->parents[a]);
    return dsu->parents[a];
}

void union_dsu(DSU* dsu, int a, int b){
    int rootA = find(dsu, a);
    int rootB = find(dsu, b);

    if(rootA == rootB) return; // already in same set

    if(dsu->rank[rootA] > dsu->rank[rootB]){
        dsu->parents[rootB] = rootA;
    }
    else if(dsu->rank[rootA] < dsu->rank[rootB]){
        dsu->parents[rootA] = rootB;
    }
    else {
        dsu->parents[rootB] = rootA;
        dsu->rank[rootA]++;  // only increase when ranks are equal
    }

}
