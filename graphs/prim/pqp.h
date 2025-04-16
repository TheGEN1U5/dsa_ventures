#include <stdlib.h>
#include <stdio.h>
#define MAX_SIZE 100

typedef struct {
    int index;
    int weight;
    int parent;
} node;

typedef struct {
    node* data[MAX_SIZE];
    int size;
} PriorityQueue;

node* create_node(int index, int weight, int parent){
    node* new_node = (node*) malloc(sizeof(node));
    new_node->index = index; new_node->weight = weight; new_node->parent = parent;
    return new_node;
}


void initQueue(PriorityQueue* pq) {
    pq->size = 0;
    for(int i = 0; i < MAX_SIZE; i++) pq->data[i] = NULL;
}

int isEmpty(PriorityQueue* pq) {
    return pq->size == 0;
}

void swap(node** a, node** b) {
    node* temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyUp(PriorityQueue* pq, int index) {
    int parent = (index - 1) / 2;
    if (index && pq->data[parent]->weight > pq->data[index]->weight) {
        swap(&pq->data[parent], &pq->data[index]);
        heapifyUp(pq, parent);
    }
}

void heapifyDown(PriorityQueue* pq, int index) {
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int smallest = index;

    if (left < pq->size && pq->data[left]->weight < pq->data[smallest]->weight)
        smallest = left;
    if (right < pq->size && pq->data[right]->weight < pq->data[smallest]->weight)
        smallest = right;

    if (smallest != index) {
        swap(&pq->data[index], &pq->data[smallest]);
        heapifyDown(pq, smallest);
    }
}

void insert(PriorityQueue* pq, node* value) {
    if (pq->size >= MAX_SIZE) {
        printf("Heap is full!\n");
        return;
    }
    pq->data[pq->size] = value;
    heapifyUp(pq, pq->size);
    pq->size++;
}

node* extractMin(PriorityQueue* pq) {
    node* min = pq->data[0];
    pq->data[0] = pq->data[--pq->size];
    heapifyDown(pq, 0);
    return min;
}

node* peekMin(PriorityQueue* pq) {
    if (isEmpty(pq)) {
        printf("Heap is empty!\n");
        return NULL;
    }
    return pq->data[0];
}