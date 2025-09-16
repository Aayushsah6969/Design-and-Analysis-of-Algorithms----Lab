#include <stdio.h>

#define MAX 100

// Structure for an edge
typedef struct {
    int u, v, w;
} Edge;

// Find parent (with path compression)
int find(int parent[], int i) {
    if (parent[i] == i)
        return i;
    return parent[i] = find(parent, parent[i]);
}

// Union two sets
void unionSet(int parent[], int rank[], int x, int y) {
    int rootX = find(parent, x);
    int rootY = find(parent, y);

    if (rootX != rootY) {
        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
}

int main() {
    int n, m;
    Edge edges[MAX];

    // Input
    printf("Enter number of nodes and edges: ");
    scanf("%d %d", &n, &m);

    printf("Enter edges (u v w):\n");
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
    }

    // Sort edges by weight (simple bubble sort)
    for (int i = 0; i < m - 1; i++) {
        for (int j = i + 1; j < m; j++) {
            if (edges[i].w > edges[j].w) {
                Edge temp = edges[i];
                edges[i] = edges[j];
                edges[j] = temp;
            }
        }
    }

    // Initialize Union-Find
    int parent[MAX], rank[MAX];
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    int totalCost = 0;
    printf("Edge Cost\n");

    // Kruskal’s algorithm
    for (int i = 0, count = 0; i < m && count < n - 1; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].w;

        int setU = find(parent, u);
        int setV = find(parent, v);

        if (setU != setV) { // if adding doesn’t form cycle
            printf("%d--%d %d\n", u, v, w);
            totalCost += w;
            unionSet(parent, rank, setU, setV);
            count++;
        }
    }

    printf("Total Weight of the Spanning Tree: %d\n", totalCost);

    return 0;
}
