#include <stdio.h>
#include <stdlib.h>

#define MAX 100

void dfs(int graph[MAX][MAX], int m, int *visited, int current, int *dfs_order, int *order_index) {
    visited[current] = 1;
    dfs_order[(*order_index)++] = current;

    for (int i = 1; i <= m; i++) {
        if (graph[current][i] == 1 && !visited[i]) {
            dfs(graph, m, visited, i, dfs_order, order_index);
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

    int visited[MAX] = {0};
    int dfs_order[MAX];
    int order_index = 0;

    dfs(graph, m, visited, 1, dfs_order, &order_index);

    for (int i = 0; i < order_index; i++) {
        printf("%d ", dfs_order[i]);
    }

    return 0;
}
