#include <stdio.h>
#include <limits.h>

#define MAX 10

void print_optimal_parens(int s[MAX][MAX], int i, int j) {
    if (i == j)
        printf("A%d", i + 1);
    else {
        printf("(");
        print_optimal_parens(s, i, s[i][j]);
        print_optimal_parens(s, s[i][j] + 1, j);
        printf(")");
    }
}

void matrix_chain_order(int p[], int n) {
    int m[MAX][MAX] = {0}, s[MAX][MAX] = {0};

    for (int l = 2; l < n; l++) {
        for (int i = 0; i < n - l; i++) {
            int j = i + l;
            m[i][j] = INT_MAX;
            for (int k = i; k < j; k++) {
                int q = m[i][k] + m[k + 1][j] + p[i] * p[k + 1] * p[j];
                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }

    printf("M Table:\n");
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1; j++)
            printf("%d\t", m[i][j]);
        printf("\n");
    }

    printf("\nS Table:\n");
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1; j++)
            printf("%d\t", s[i][j]);
        printf("\n");
    }

    printf("\nOptimal parenthesization: ");
    print_optimal_parens(s, 0, n - 2);
    printf("\nThe optimal ordering of the given matrices requires %d scalar multiplications.\n", m[0][n - 2]);
}

int main() {
    int n, p[MAX + 1];

    printf("Enter number of matrices: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        int row, col;
        printf("Enter row and col size of A%d: ", i + 1);
        scanf("%d %d", &row, &col);
        if (i == 0)
            p[i] = row;
        p[i + 1] = col;
    }

    matrix_chain_order(p, n + 1);
    return 0;
}
