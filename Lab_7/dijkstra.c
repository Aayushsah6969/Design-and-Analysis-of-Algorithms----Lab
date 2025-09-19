#include <stdio.h>
#include <stdlib.h>
#define MAX 100
#define INF 1000000

void dijkstra(int n, int graph[MAX][MAX], int src) {
    int dist[MAX], prev[MAX], visited[MAX];
    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
        prev[i] = -1;
        visited[i] = 0;
    }
    dist[src] = 0;

    for (int count = 1; count <= n; count++) {
        int u = -1, minDist = INF;
        for (int i = 1; i <= n; i++) {
            if (!visited[i] && dist[i] < minDist) {
                minDist = dist[i];
                u = i;
            }
        }
        if (u == -1) break;
        visited[u] = 1;

        for (int v = 1; v <= n; v++) {
            if (graph[u][v] > 0 && !visited[v]) {
                if (dist[u] + graph[u][v] < dist[v]) {
                    dist[v] = dist[u] + graph[u][v];
                    prev[v] = u;
                }
            }
        }
    }

    printf("Source Destination Cost Path\n");
    for (int i = 1; i <= n; i++) {
        printf("%d %d ", src, i);
        if (dist[i] == INF) {
            printf("INF -\n");
        } else {
            printf("%d ", dist[i]);
            if (i == src) {
                printf("-\n");
            } else {
                // Print path
                int path[MAX], len = 0, v = i;
                while (v != -1) {
                    path[len++] = v;
                    v = prev[v];
                }
                for (int j = len - 1; j >= 0; j--) {
                    printf("%d", path[j]);
                    if (j != 0) printf("->");
                }
                printf("\n");
            }
        }
    }
}

int main() {
    int n, src;
    int graph[MAX][MAX];

    FILE *fp = fopen("inDiAdjMat1.dat", "r");
    if (!fp) {
        printf("Error opening file.\n");
        return 1;
    }

    printf("Enter the Number of Vertices: ");
    scanf("%d", &n);

    printf("Enter the Source Vertex: ");
    scanf("%d", &src);

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            fscanf(fp, "%d", &graph[i][j]);
    fclose(fp);

    dijkstra(n, graph, src);

    return 0;
}