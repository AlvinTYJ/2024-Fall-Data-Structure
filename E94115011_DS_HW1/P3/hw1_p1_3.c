#include <stdio.h>
#include <stdlib.h>

#define MAX 100

struct Queue {
    int items[MAX];
    int front, rear;
};

void initQueue(struct Queue* q) {
    q->front = 0;
    q->rear = -1;
}

int isEmpty(struct Queue* q) {
    return q->rear < q->front;
}

void enqueue(struct Queue* q, int value) {
    if (q->rear == MAX - 1) {
        //Queue overflow
        return;
    }
    q->items[++(q->rear)] = value;
}

int dequeue(struct Queue* q) {
    if (isEmpty(q)) {
        //Queue underflow
        return -1;
    }
    return q->items[(q->front)++];
}

void bfs(int graph[MAX][MAX], int m, int *bfs_order, int *order_index) {
    int visited[MAX] = {0};
    struct Queue q;
    initQueue(&q);

    enqueue(&q, 1);
    visited[1] = 1;

    while (!isEmpty(&q)) {
        int current = dequeue(&q);
        bfs_order[(*order_index)++] = current;

        for (int i = 1; i <= m; i++) {
            if (graph[current][i] == 1 && !visited[i]) {
                enqueue(&q, i);
                visited[i] = 1;
            }
        }
    }
}

int main() {
    int m;
    scanf("%d", &m);

    int graph[MAX][MAX];
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    int bfs_order[MAX];
    int order_index = 0;

    bfs(graph, m, bfs_order, &order_index);

    for (int i = 0; i < order_index; i++) {
        printf("%d ", bfs_order[i]);
    }

    return 0;
}