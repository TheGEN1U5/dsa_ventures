#include <stdio.h>

void printarr(int* a, int size){
    for(int i = 1, l = size; i < l; i++) printf("%d ", a[i]);
    printf("\n");
}

void swap(int* a, int* b){
    int t = *a;
    *a = *b;
    *b = t;
}

void max_heapify(int* a, int i, int s){
    int l = 2 * i;
    int r = 2 * i + 1;
    int largest = i;
    if(i < s && a[i] < a[l]) largest = l;
    if(i < s && a[largest] < a[r]) largest = r;
    if(largest != i && largest < s){
        int t = a[i];
        a[i] = a[largest];
        a[largest] = t;
        max_heapify(a, largest, s);
    }
}

void heap_sort(int* a, int size){
    for(int i = (size - 1) / 2; i >= 1; i--){
        max_heapify(a, i, size);
    }
    printarr(a, size);
    for(int i = size - 1; i > 2; i--){
        int temp = a[i];
        a[i] = a[1];
        a[1] = temp;
        max_heapify(a, 1, i);
        printarr(a, size);
    }
}


int main(void){
    int arr[] = {-1, 4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
    printarr(arr, 11);
    heap_sort(arr, 11);
    printarr(arr, 11);

}