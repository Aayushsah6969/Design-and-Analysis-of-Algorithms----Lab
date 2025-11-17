#include <stdio.h>

typedef struct {
    int item_id;
    float profit, weight, ratio;
} ITEM;

// Bubble sort in descending order by ratio
void bubbleSort(ITEM arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].ratio < arr[j+1].ratio) {
                ITEM temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

// Fractional Knapsack
void fractionalKnapsack(ITEM items[], int n, float capacity) {
    float totalProfit = 0.0;
    float amount[n];  

    for (int i = 0; i < n; i++)
        amount[i] = 0.0;

    for (int i = 0; i < n; i++) {
        if (capacity <= 0) break;

        if (items[i].weight <= capacity) {
            amount[i] = 1.0; // take full item
            capacity -= items[i].weight;
            totalProfit += items[i].profit;
        } else {
            amount[i] = capacity / items[i].weight; // fraction
            totalProfit += items[i].profit * amount[i];
            capacity = 0;
        }
    }

    printf("\nItem No\t\tProfit\t\tWeight\t\tAmount to be taken\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%.6f\t%.6f\t%.6f\n", items[i].item_id, items[i].profit, items[i].weight, amount[i]);
    }

    printf("\nMaximum profit: %.6f\n", totalProfit);
}

int main() {
    int n;
    float capacity;

    printf("Enter the number of items: ");
    scanf("%d", &n);

    ITEM items[n];

    for (int i = 0; i < n; i++) {
        printf("Enter the profit and weight of item no %d: ", i + 1);
        scanf("%f %f", &items[i].profit, &items[i].weight);
        items[i].item_id = i + 1;
        items[i].ratio = items[i].profit / items[i].weight;
    }

    printf("Enter the capacity of knapsack: ");
    scanf("%f", &capacity);

    // Sort using bubble sort (descending order of ratio)
    bubbleSort(items, n);

    // Apply fractional knapsack
    fractionalKnapsack(items, n, capacity);

    return 0;
}
