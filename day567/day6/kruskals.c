#include <stdio.h>
#include <stdlib.h>

#define MAX 100

struct Edge {
    int u, v, weight;
};

struct Graph {
    int V, E;
    struct Edge edges[MAX];
};

struct Subset {
    int parent;
    int rank;
};

int find(struct Subset subsets[], int i) {
    if (subsets[i].parent != i) {
        subsets[i].parent = find(subsets, subsets[i].parent);
    }
    return subsets[i].parent;
}

void unionSubsets(struct Subset subsets[], int x, int y) {
    int rootX = find(subsets, x);
    int rootY = find(subsets, y);

    if (subsets[rootX].rank < subsets[rootY].rank) {
        subsets[rootX].parent = rootY;
    } else if (subsets[rootX].rank > subsets[rootY].rank) {
        subsets[rootY].parent = rootX;
    } else {
        subsets[rootY].parent = rootX;
        subsets[rootX].rank++;
    }
}

int compareEdges(const void *a, const void *b) {
    struct Edge *edgeA = (struct Edge *)a;
    struct Edge *edgeB = (struct Edge *)b;
    return edgeA->weight - edgeB->weight;
}

void kruskalMST(struct Graph *graph) {
    int V = graph->V;
    struct Edge result[MAX];
    int e = 0;
    int i = 0;

    qsort(graph->edges, graph->E, sizeof(graph->edges[0]), compareEdges);

    struct Subset *subsets = (struct Subset *)malloc(V * sizeof(struct Subset));

    for (int v = 0; v < V; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    while (e < V - 1 && i < graph->E) {
        struct Edge nextEdge = graph->edges[i++];
        int x = find(subsets, nextEdge.u - 1);
        int y = find(subsets, nextEdge.v - 1);

        if (x != y) {
            result[e++] = nextEdge;
            unionSubsets(subsets, x, y);
        }
    }

    int totalWeight = 0;
    printf("Edge  Cost\n");
    for (i = 0; i < e; ++i) {
        printf("%d--%d  %d\n", result[i].u, result[i].v, result[i].weight);
        totalWeight += result[i].weight;
    }
    printf("Total Weight of the Spanning Tree: %d\n", totalWeight);

    free(subsets);
}

int main() {
    int n, m;
    struct Graph graph;

    printf("Enter the number of nodes and edges: ");
    scanf("%d %d", &n, &m);

    graph.V = n;
    graph.E = m;

    printf("Enter the edges (u, v) and their respective weights:\n");
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &graph.edges[i].u, &graph.edges[i].v, &graph.edges[i].weight);
    }

    kruskalMST(&graph);

    return 0;
}

