#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 100

struct MinHeap {
    int size;
    int arr[MAX];
};

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyUp(struct MinHeap* heap, int index) {
    if (index > 0 && heap->arr[(index - 1) / 2] > heap->arr[index]) {
        swap(&heap->arr[(index - 1) / 2], &heap->arr[index]);
        heapifyUp(heap, (index - 1) / 2);
    }
}

void insert(struct MinHeap* heap, int key) {
    if (heap->size == MAX) {
        printf("Heap overflow\n");
        return;
    }

    heap->arr[heap->size] = key;
    heap->size++;
    heapifyUp(heap, heap->size - 1);
}

void heapifyDown(struct MinHeap* heap, int index) {
    int smallest = index;
    int left = 2*index + 1;
    int right = 2*index + 2;

    if (left < heap->size && heap->arr[left] < heap->arr[smallest])
        smallest = left;

    if (right < heap->size && heap->arr[right] < heap->arr[smallest])
        smallest = right;

    if (smallest != index) {
        swap(&heap->arr[smallest], &heap->arr[index]);
        heapifyDown(heap, smallest);
    }
}

int findIndex(struct MinHeap* heap, int key) {
    for (int i = 0; i < heap->size; i++) {
        if (heap->arr[i] == key)
            return i;
    }
    return -1;
}

void delete(struct MinHeap* heap, int key) {
    int index = findIndex(heap, key);
    if (index == -1) {
        return;
    }

    heap->arr[index] = heap->arr[heap->size - 1];
    heap->size--;
    heapifyDown(heap, index);
}

int main() { //Priority Queue Implementation Using Min-Heap
    struct MinHeap heap;
    heap.size = 0;

    FILE *infile, *outfile;
    infile = fopen("3.txt", "r");
    if (infile == NULL) {
        printf("Error opening input file\n");
        return 1;
    }

    outfile = fopen("output.txt", "w");
    if (outfile == NULL) {
        printf("Error opening output file\n");
        fclose(infile);
        return 1;
    }

    char operation[10];
    int value;

    while (fscanf(infile, "%s", operation) != EOF) {
        if (strcmp(operation, "insert") == 0) {
            fscanf(infile, "%d", &value);
            insert(&heap, value);
        } else if (strcmp(operation, "delete") == 0) {
            fscanf(infile, "%d", &value);
            delete(&heap, value);
        }
    }

    for (int i = 0; i < heap.size; i++) {
        fprintf(outfile, "%d ", heap.arr[i]);
    }
    fprintf(outfile, "\n");

    fclose(infile);
    fclose(outfile);
    return 0;
}