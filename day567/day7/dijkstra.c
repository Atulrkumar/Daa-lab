#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 100

void readGraph(const char *filename, int *n, int graph[MAX_VERTICES][MAX_VERTICES]) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        exit(EXIT_FAILURE);
    }

    fscanf(file, "%d", n);
    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *n; j++) {
            fscanf(file, "%d", &graph[i][j]);
        }
    }
    fclose(file);
}

void dijkstra(int graph[MAX_VERTICES][MAX_VERTICES], int n, int start_vertex) {
    int distances[MAX_VERTICES];
    int visited[MAX_VERTICES] = {0};
    int previous[MAX_VERTICES];
    
    for (int i = 0; i < n; i++) {
        distances[i] = INT_MAX;
        previous[i] = -1;
    }
    distances[start_vertex] = 0;

    for (int count = 0; count < n - 1; count++) {
        int min_distance = INT_MAX;
        int min_index = -1;

        for (int v = 0; v < n; v++) {
            if (!visited[v] && distances[v] <= min_distance) {
                min_distance = distances[v];
                min_index = v;
            }
        }

        visited[min_index] = 1;

        for (int v = 0; v < n; v++) {
            if (!visited[v] && graph[min_index][v] != 0 && 
                distances[min_index] != INT_MAX && 
                distances[min_index] + graph[min_index][v] < distances[v]) {
                distances[v] = distances[min_index] + graph[min_index][v];
                previous[v] = min_index;
            }
        }
    }

    printf("Source\tDestination\tCost\tPath\n");
    for (int i = 0; i < n; i++) {
        if (i == start_vertex) {
            printf("%d\t%d\t0\t-\n", start_vertex + 1, start_vertex + 1);
        } else {
            if (distances[i] < INT_MAX) {
                printf("%d\t%d\t%d\t", start_vertex + 1, i + 1, distances[i]);

                int path[MAX_VERTICES];
                int path_length = 0;
                for (int j = i; j != -1; j = previous[j]) {
                    path[path_length++] = j + 1;
                }
                
                for (int j = path_length - 1; j >= 0; j--) {
                    printf("%d", path[j]);
                    if (j > 0) printf("->");
                }
                printf("\n");
            } else {
                printf("%d\t%d\t-\n", start_vertex + 1, i + 1);
            }
        }
    }
}

int main() {
    int n;
    int graph[MAX_VERTICES][MAX_VERTICES] = {0};

    printf("Enter the number of vertices: ");
    scanf("%d", &n);
    
    printf("Enter the adjacency matrix (%d x %d):\n", n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    int start_vertex;
    printf("Enter the source vertex (1 to %d): ", n);
    scanf("%d", &start_vertex);
    start_vertex--;

    dijkstra(graph, n, start_vertex);

    return 0;
}
