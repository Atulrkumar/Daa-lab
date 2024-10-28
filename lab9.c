#include <stdio.h>
#define INF 99999
#define MAX 100

int dist[MAX][MAX], next[MAX][MAX];

// Function to initialize distance and path matrices
void floydWarshall(int n) {
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }
}

// Function to display shortest path from u to v
void displayPath(int u, int v) {
    if (next[u][v] == -1) {
        printf("No path\n");
        return;
    }
    printf("Shortest Path from vertex %d to vertex %d: %d", u + 1, v + 1, u + 1);
    while (u != v) {
        u = next[u][v];
        if (u == -1) {  // Prevents infinite loop if there's no valid path
            printf(" -> No path\n");
            return;
        }
        printf(" --> %d", u + 1);
    }
    printf("\nPath weight: %d\n", dist[u][v]);
}

int main() {
    int n, u, v;
    FILE *file = fopen("inDiAdjMat2.txt", "r");

    fscanf(file, "%d", &n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(file, "%d", &dist[i][j]);
            if (i != j && dist[i][j] == 0) dist[i][j] = INF;
            next[i][j] = (dist[i][j] == INF) ? -1 : j;
        }
    }
    fclose(file);

    floydWarshall(n);

    printf("Enter source and destination vertex: ");
    scanf("%d %d", &u, &v);
    u--; v--;  // Adjust for 0-based index

    // Display shortest-path weight matrix
    printf("Shortest Path Weight Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (dist[i][j] == INF) printf("INF ");
            else printf("%d ", dist[i][j]);
        }
        printf("\n");
    }

    // Display path and path weight from source to destination
    displayPath(u, v);

    return 0;
}
