#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define INF INT_MAX

int minKey(int key[], bool mstSet[], int vertices) {
    int min = INF, min_index;

    for (int v = 0; v < vertices; v++) {
        if (mstSet[v] == false && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}

void printMST(int parent[], int graph[100][100], int vertices) {
    int mst[100][100] = {0};
    int totalWeight = 0;

    printf("Cost Adjacency Matrix of Minimum Spanning Tree (MST):\n");
    for (int i = 1; i < vertices; i++) {
        mst[i][parent[i]] = graph[i][parent[i]];
        mst[parent[i]][i] = graph[i][parent[i]];
        totalWeight += graph[i][parent[i]];
    }

    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            printf("%d ", mst[i][j]);
        }
        printf("\n");
    }
    printf("Total Weight of the Minimum Spanning Tree: %d\n", totalWeight);
}

void primMST(int graph[100][100], int vertices, int start_vertex) {
    int parent[100];
    int key[100];
    bool mstSet[100];

    for (int i = 0; i < vertices; i++) {
        key[i] = INF;
        mstSet[i] = false;
    }

    key[start_vertex] = 0;
    parent[start_vertex] = -1;

    for (int count = 0; count < vertices - 1; count++) {
        int u = minKey(key, mstSet, vertices);
        mstSet[u] = true;

        for (int v = 0; v < vertices; v++) {
            if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    printMST(parent, graph, vertices);
}

int main() {
    int vertices, start_vertex;
    int graph[100][100];

    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);

    printf("Enter the starting vertex (0-based index): ");
    scanf("%d", &start_vertex);

    FILE *file = fopen("inUnAdjMat.dat", "r");
    if (file == NULL) {
        printf("Error: Could not open the file.\n");
        return 1;
    }

    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            fscanf(file, "%d", &graph[i][j]);
        }
    }
    fclose(file);

    primMST(graph, vertices, start_vertex);

    return 0;
}

