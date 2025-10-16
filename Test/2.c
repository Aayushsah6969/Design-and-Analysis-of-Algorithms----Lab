#include <stdio.h>
#define INF 9999   // a large number representing "infinity" (no direct path)
#define V 5        // number of vertices in the graph

int main() {
    // Adjacency matrix representation of the graph
    // 0 means there is no direct edge between those vertices
    int cost[V][V] = {
        {0, 6, 0, 1, 0},   // edges from vertex 0
        {6, 0, 5, 2, 2},   // edges from vertex 1
        {0, 5, 0, 0, 5},   // edges from vertex 2
        {1, 2, 0, 0, 1},   // edges from vertex 3
        {0, 2, 5, 1, 0}    // edges from vertex 4
    };

    int dist[V];    // stores the shortest distance from the source to each vertex
    int visited[V]; // marks whether a vertex has been permanently "visited"
    int i, j, count, min, next;
    int src = 0;    // source vertex (we start from vertex 0)

    // Step 1: Initialize all distances and visited[] array
    for (i = 0; i < V; i++) {
        if (cost[src][i] == 0)
            dist[i] = INF;     // if no direct edge, set distance as infinity
        else
            dist[i] = cost[src][i];  // if edge exists, take that edge weight
        visited[i] = 0;        // mark all vertices as unvisited
    }

    dist[src] = 0;   // distance from source to itself is 0
    visited[src] = 1;  // mark the source vertex as visited
    count = 1;       // we have visited 1 vertex (the source)

    // Step 2: Repeat until all vertices are visited
    while (count < V - 1) {
        min = INF;

        // Step 2a: Find the unvisited vertex with the smallest distance
        for (i = 0; i < V; i++) {
            if (dist[i] < min && !visited[i]) {
                min = dist[i];
                next = i; // this will be the next vertex to process
            }
        }

        visited[next] = 1; // mark this vertex as visited

        // Step 2b: Update the distances of its neighboring vertices
        for (i = 0; i < V; i++) {
            // if there is an edge and the vertex is unvisited
            if (!visited[i]) {
                if (cost[next][i] != 0 && dist[next] + cost[next][i] < dist[i])
                    dist[i] = dist[next] + cost[next][i]; // update distance
            }
        }

        count++; // move to the next iteration
    }

    // Step 3: Print the final shortest distances
    printf("Shortest distances from source (vertex %d):\n", src);
    for (i = 0; i < V; i++)
        printf("To vertex %d = %d\n", i, dist[i]);

    return 0;
}
