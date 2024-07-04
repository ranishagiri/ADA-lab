#include <stdio.h>
#include <limits.h>

#define MAX 100

void prims(int n, int cost[MAX][MAX], int INF) {
    int S[MAX], d[MAX], p[MAX], T[MAX][2];
    int i, j, min, source, sum = 0, k = 0, u;


    min = INF;
    source = 0;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (cost[i][j] != 0 && cost[i][j] < min) {
                min = cost[i][j];
                source = i;
            }
        }
    }


    for (i = 0; i < n; i++) {
        S[i] = 0;
        d[i] = cost[source][i];
        p[i] = source;
    }

    S[source] = 1;

    for (i = 1; i < n; i++) {

        min = INF;
        u = -1;
        for (j = 0; j < n; j++) {
            if (S[j] == 0 && d[j] <= min) {
                min = d[j];
                u = j;
            }
        }


        T[k][0] = u;
        T[k][1] = p[u];
        k++;


        sum += cost[u][p[u]];

        // Add u to S
        S[u] = 1;


        for (j = 0; j < n; j++) {
            if (S[j] == 0 && cost[u][j] < d[j]) {
                d[j] = cost[u][j];
                p[j] = u;
            }
        }
    }

    // Step 5: Check if MST exists
    if (sum >= INF) {
        printf("Spanning tree does not exist.\n");
    } else {
        printf("Spanning tree exists and MST is:\n");
        for (i = 0; i < n - 1; i++) {
            printf("%d -> %d\n", T[i][1], T[i][0]);
        }
        printf("The cost of Spanning tree is MST is %d\n", sum);
    }
}

int main() {
    int n, cost[MAX][MAX], i, j;
    int INF = INT_MAX; // Initialize INF to a large value, like INT_MAX

    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    printf("Enter the cost adjacency matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &cost[i][j]);
            if (cost[i][j] == 9999 ) {
                cost[i][j] = INF;
            }
        }
    }

    prims(n, cost, INF);

    return 0;
}
