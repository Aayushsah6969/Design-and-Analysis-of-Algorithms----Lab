#include <stdio.h>

// Define a large number to represent infinity
#define INF 99999

int numVertices;

// Function to print the solution matrix
void printMatrix(int dist[][numVertices]) {
    printf("\nShortest path matrix:\n");
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            if (dist[i][j] == INF)
                printf("%7s", "INF");
            else
                printf("%7d", dist[i][j]);
        }
        printf("\n");
    }
}

// Function to reconstruct and print the shortest path
void printPath(int path[][numVertices], int u, int v) {
    // If there is no path
    if (path[u][v] == -1) {
        printf("No path from %d to %d exists\n", u + 1, v + 1);
        return;
    }
    
    printf("%d", u + 1);
    while (u != v) {
        u = path[u][v];
        printf(" -> %d", u + 1);
    }
}


/*
 * Solves the all-pairs shortest path problem using Floyd Warshall algorithm.
 * graph: The input adjacency matrix.
 */
void floydWarshall(int graph[][numVertices]) {
    int dist[numVertices][numVertices];
    int path[numVertices][numVertices];
    int i, j, k;

    // Initialize the solution matrix same as input graph matrix.
    // Initialize the path matrix.
    for (i = 0; i < numVertices; i++) {
        for (j = 0; j < numVertices; j++) {
            dist[i][j] = graph[i][j];
            if (graph[i][j] != INF && i != j) {
                path[i][j] = j;
            } else {
                path[i][j] = -1;
            }
        }
    }

    // Main algorithm: consider each vertex as an intermediate vertex.
    for (k = 0; k < numVertices; k++) {
        // Pick all vertices as source one by one
        for (i = 0; i < numVertices; i++) {
            // Pick all vertices as destination for the above picked source
            for (j = 0; j < numVertices; j++) {
                // If vertex k is on the shortest path from i to j,
                // then update the value of dist[i][j]
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    path[i][j] = path[i][k];
                }
            }
        }
    }

    // Print the shortest distance matrix
    printMatrix(dist);

    // Get source and destination from user to print the path
    int u, v;
    printf("\nEnter the source and destination vertex (1 to %d): ", numVertices);
    scanf("%d %d", &u, &v);

    // Adjust to 0-based indexing
    u--; 
    v--;

    if (u >= 0 && u < numVertices && v >= 0 && v < numVertices) {
        printf("\nShortest Path from vertex %d to vertex %d: ", u + 1, v + 1);
        printPath(path, u, v);
        printf("\nPath weight: %d\n", dist[u][v]);
    } else {
        printf("Invalid source or destination vertex.\n");
    }
}

int main() {
    printf("Enter the number of vertices: ");
    scanf("%d", &numVertices);

    int graph[numVertices][numVertices];

    printf("Enter the cost adjacency matrix (use %d for infinity):\n", INF);
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    floydWarshall(graph);

    return 0;
}
