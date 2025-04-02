#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define V 100

int maxKey(int key[], bool mstSet[], int n) {
    int max = INT_MIN, max_index;
    
    for (int v = 0; v < n; v++)
        if (mstSet[v] == false && key[v] > max) {
            max = key[v];
            max_index = v;
        }
    
    return max_index;
}

void printMST(int parent[], int graph[V][V], int n) {
    int totalWeight = 0;

    for (int i = 1; i < n; i++) {
        int u = i;
        int v = parent[i];
        totalWeight += graph[u][v];
    }
    printf("%d", totalWeight);
    
    for (int i = 1; i < n; i++) { //parent[] = [-1, 2, 0]
        int u = i;
        int v = parent[i];
        if (u < v)
            printf(" (%d, %d)", u, v);
        else
            printf(" (%d, %d)", v, u);
    }
    printf("\n");
}

void primMST(int graph[V][V], int n) {
    int parent[V];  // Array to store constructed MST
    int key[V];     // Key values used to pick maximum weight edge in cut
    bool mstSet[V]; // To represent vertices not yet included in MST

    // Initialize all keys as INT_MIN (negative infinity for maximum)
    for (int i = 0; i < n; i++) {
        key[i] = INT_MIN;
        mstSet[i] = false;
    }

    key[0] = 0;     
    parent[0] = -1;

    for (int count = 0; count < n - 1; count++) {
        // Pick the maximum key vertex from the set of vertices not yet included
        int u = maxKey(key, mstSet, n);

        // Add the picked vertex to the MST set
        mstSet[u] = true;

        // Update key values and parent index of the adjacent vertices of the picked vertex
        for (int v = 0; v < n; v++)
            // Update the key only if graph[u][v] is greater than key[v] and v is not in mstSet
            if (graph[u][v] && mstSet[v] == false && graph[u][v] > key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
    }
    printMST(parent, graph, n);
}

int main() {
    int n;
    int graph[V][V];
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    primMST(graph, n);

    return 0;
}
