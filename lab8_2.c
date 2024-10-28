#include <stdio.h>
#include <string.h>

#define MAX 100

void find_LCS(char *X, char *Y) {
    int m = strlen(X), n = strlen(Y);
    int L[MAX][MAX] = {0};

    // Build the LCS table
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (X[i - 1] == Y[j - 1])
                L[i][j] = L[i - 1][j - 1] + 1;
            else
                L[i][j] = (L[i - 1][j] > L[i][j - 1]) ? L[i - 1][j] : L[i][j - 1];
        }
    }

    // Length of LCS
    int lcs_length = L[m][n];
    printf("LCS Length: %d\n", lcs_length);

    // Reconstruct LCS
    char LCS[MAX];
    int i = m, j = n, index = lcs_length;
    LCS[index] = '\0';  // End of string

    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            LCS[--index] = X[i - 1];
            i--; j--;
        } else if (L[i - 1][j] > L[i][j - 1])
            i--;
        else
            j--;
    }

    printf("LCS: %s\n", LCS);
}

int main() {
    char X[MAX], Y[MAX];

    printf("Enter the first string into an array: ");
    scanf("%s", X);
    printf("Enter the second string into an array: ");
    scanf("%s", Y);

    find_LCS(X, Y);
    return 0;
}
