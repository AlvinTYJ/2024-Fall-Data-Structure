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
        //Heap overflow
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

void deleteKey(struct MinHeap* heap, int key) {
    int index = findIndex(heap, key);
    if (index == -1) {
        return;
    }

    heap->arr[index] = heap->arr[heap->size - 1];
    heap->size--;
    heapifyDown(heap, index);
}

int main() {
    struct MinHeap heap;
    heap.size = 0;
    
    char input[50];
    char operation[10];
    int value;

    while (1) {
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }

        if (strcmp(input, "\n") == 0) {
            break;
        }

        sscanf(input, "%s %d", operation, &value);

        if (strcmp(operation, "insert") == 0) {
            insert(&heap, value);
        } else if (strcmp(operation, "delete") == 0) {
            deleteKey(&heap, value);
        }
    }

    for (int i = 0; i < heap.size; i++) {
        printf("%d ", heap.arr[i]); 
    }
    printf("\n");
    return 0;
}