#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    float p;
    float w;
    float pw_ratio;
} Item;

void swap(Item* a, Item* b) {
    Item temp = *a;
    *a = *b;
    *b = temp;
}

void sort_by_ratio(Item items[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (items[j].pw_ratio < items[j + 1].pw_ratio) {
                swap(&items[j], &items[j + 1]);
            }
        }
    }
}

void knapsack(Item items[], int n, float cap) {
    sort_by_ratio(items, n);
    float profit = 0.0;
    float rem_cap = cap;
    float taken[n];

    for (int i = 0; i < n; i++) {
        taken[i] = 0.0;
    }

    for (int i = 0; i < n; i++) {
        if (rem_cap >= items[i].w) {
            taken[i] = 1.0;
            rem_cap -= items[i].w;
            profit += items[i].p;
        } else {
            taken[i] = rem_cap / items[i].w;
            profit += items[i].p * taken[i];
            rem_cap = 0;
        }
        if (rem_cap == 0)
            break;
    }

    printf("ID\tProfit\tWeight\tTaken\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%.6f\t%.6f\t%.6f\n", items[i].id, items[i].p, items[i].w, taken[i]);
    }

    printf("Max profit: %.6f\n", profit);
}

int main() {
    int n;
    float cap;

    printf("Enter capacity: ");
    scanf("%f", &cap);

    printf("Enter number of items: ");
    scanf("%d", &n);

    Item items[n];

    for (int i = 0; i < n; i++) {
        printf("Enter profit and weight of item %d: ", i + 1);
        scanf("%f %f", &items[i].p, &items[i].w);
        items[i].id = i + 1;
        items[i].pw_ratio = items[i].p / items[i].w;
    }

    knapsack(items, n, cap);

    return 0;
}
