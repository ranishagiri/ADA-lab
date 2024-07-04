#include <stdio.h>

#define N 4
#define CAPACITY 7

int max(int a, int b) {
    if(a>b){
        return a;
    }
    return b;

}


void knapsack(int weights[], int profits[]) {
    int i, w;
    int dp[N + 1][CAPACITY + 1];

    for (i = 0; i <= N; i++) {
        for (w = 0; w <= CAPACITY; w++) {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            else if (weights[i - 1] <= w)
                dp[i][w] = max(profits[i - 1] + dp[i - 1][w - weights[i - 1]], dp[i - 1][w]);
            else
                dp[i][w] = dp[i - 1][w];
        }
    }

    int maxProfit = dp[N][CAPACITY];
    printf("Maximum profit: %d\n", maxProfit);

    int selectedObjects[N];
    int k = N, c = CAPACITY;
    while (k > 0 && c > 0) {
        if (dp[k][c] != dp[k - 1][c]) {
            selectedObjects[k - 1] = 1;
            c =c- weights[k - 1];
        } else {
            selectedObjects[k - 1] = 0;
        }
        k--;
    }

    printf("\nTable Values (DP Table):\n");
    for (i = 0; i <= N; i++) {
        for (w = 0; w <= CAPACITY; w++) {
            printf("%d\t", dp[i][w]);
        }
        printf("\n");
    }

    printf("\nObjects selected in the knapsack:\n");
    for (i = 0; i < N; i++) {
        if (selectedObjects[i] == 1)
            printf("Object %d (Weight: %d, Profit: %d)\n", i + 1, weights[i], profits[i]);
    }
}

int main() {
    int weights[N];
    int profits[N];

    printf("Enter the weights:\n");
    for(int i=0;i<N;i++){
        scanf("%d",&weights[i]);
    }

    printf("Enter the profits:\n");
    for(int i=0;i<N;i++){
        scanf("%d",&profits[i]);
    }

    printf("Knapsack Capacity: %d\n", CAPACITY);
    printf("Objects:\n");
    for (int i = 0; i < N; i++) {
        printf("Object %d - Weight: %d, Profit: %d\n", i + 1, weights[i], profits[i]);
    }

    knapsack(weights, profits);

    return 0;
}

