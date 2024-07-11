#include <stdio.h>
#include <stdlib.h>

#define SIZE 100 // Assuming a maximum size for the graph

// Structure to represent an edge in the graph
struct Edge {
    int u, v, weight;
};

// Function prototypes
void kruskals(int c[SIZE][SIZE], int n);
int find(int parent[], int i);
void unionSet(int parent[], int rank[], int x, int y);

int main() {
    int c[SIZE][SIZE], n;

    printf("Enter the number of vertices in the graph: ");
    scanf("%d", &n);

    printf("Enter the cost matrix (enter 9999 for infinity):\n");
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%d", &c[i][j]);
        }
    }

    kruskals(c, n);

    return 0;
}

// Kruskal's algorithm to find Minimum Cost Spanning Tree
void kruskals(int c[SIZE][SIZE], int n) {
    struct Edge edges[SIZE * SIZE]; // Maximum possible edges
    int edgeCount = 0;

    // Create edges array from the cost matrix
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (c[i][j] != 9999) {
                edges[edgeCount].u = i;
                edges[edgeCount].v = j;
                edges[edgeCount].weight = c[i][j];
                edgeCount++;
            }
        }
    }

    // Sort edges based on weight (using bubble sort for simplicity)
    for (int i = 0; i < edgeCount - 1; i++) {
        for (int j = 0; j < edgeCount - i - 1; j++) {
            if (edges[j].weight > edges[j + 1].weight) {
                struct Edge temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }

    // Initialize parent and rank arrays for Union-Find
    int parent[SIZE], rank[SIZE];
    for (int i = 1; i <= n; i++) {
        parent[i] = 0; // Initialize each vertex as its own parent
        rank[i] = 0;
    }

    int mincost = 0;
    printf("\nEdges in the Minimum Spanning Tree:\n");

    // Process each edge in sorted order
    for (int i = 0; i < edgeCount; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int weight = edges[i].weight;

        // Check if including this edge forms a cycle (Union-Find)
        int set_u = find(parent, u);
        int set_v = find(parent, v);

        if (set_u != set_v) {
            // Include this edge in the MST
            printf("%d -> %d: %d\n", u, v, weight);
            mincost += weight;
            unionSet(parent, rank, set_u, set_v);
        }
    }

    printf("\nMinimum Cost Spanning Tree: %d\n", mincost);
}

// Find function for Union-Find
int find(int parent[], int i) {
    if (parent[i] == 0)
        return i;
    return find(parent, parent[i]);
}

// Union function for Union-Find
void unionSet(int parent[], int rank[], int x, int y) {
    if (rank[x] > rank[y])
        parent[y] = x;
    else if (rank[x] < rank[y])
        parent[x] = y;
    else {
        parent[y] = x;
        rank[x]++;
    }
}

