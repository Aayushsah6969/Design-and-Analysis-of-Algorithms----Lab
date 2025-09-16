#include <stdio.h>
#include <limits.h>

#define MAX 20

int main() {
    int n, start;
    int graph[MAX][MAX], mst[MAX][MAX];
    int key[MAX], parent[MAX], visited[MAX];
    FILE *fp;

    // Open file
    fp = fopen("inUnAdjMat.dat", "r");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    // Input
    printf("Enter the Number of Vertices: ");
    scanf("%d", &n);
    printf("Enter the Starting Vertex: ");
    scanf("%d", &start);

    // Read adjacency matrix from file
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            fscanf(fp, "%d", &graph[i][j]);
    fclose(fp);

    // Initialize arrays
    for (int i = 0; i < n; i++) {
        key[i] = INT_MAX;
        visited[i] = 0;
        parent[i] = -1;
        for (int j = 0; j < n; j++)
            mst[i][j] = 0;
    }

    // Start vertex
    key[start - 1] = 0;

    // Prim's algorithm
    for (int count = 0; count < n - 1; count++) {
        int min = INT_MAX, u = -1;

        // Pick smallest key vertex not visited
        for (int v = 0; v < n; v++) {
            if (!visited[v] && key[v] < min) {
                min = key[v];
                u = v;
            }
        }

        visited[u] = 1;

        // Update keys of neighbors
        for (int v = 0; v < n; v++) {
            if (graph[u][v] && !visited[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    // Build MST adjacency matrix
    int totalCost = 0;
    for (int i = 1; i < n; i++) {
        int u = parent[i];
        int v = i;
        int w = graph[u][v];
        mst[u][v] = w;
        mst[v][u] = w;
        totalCost += w;
    }

    // Print MST adjacency matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%d ", mst[i][j]);
        printf("\n");
    }

    // Print total weight
    printf("Total Weight of the Spanning Tree: %d\n", totalCost);

    return 0;
}
