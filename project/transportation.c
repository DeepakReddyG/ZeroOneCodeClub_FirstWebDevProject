#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_SIZE 10

void vogelApproximation(int *demand, int *supply, int **cost, int rows, int cols) {
    int **allocation = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        allocation[i] = (int *)calloc(cols, sizeof(int));
    }

    int *row_penalty = (int *)calloc(rows, sizeof(int));
    int *col_penalty = (int *)calloc(cols, sizeof(int));

    while (1) {
        int max_row_penalty = 0, max_col_penalty = 0;
        int max_row_index = -1, max_col_index = -1;

        // Calculate penalties for rows and columns
        for (int i = 0; i < rows; i++) {
            int first_min = INT_MAX, second_min = INT_MAX;
            for (int j = 0; j < cols; j++) {
                if (cost[i][j] < first_min) {
                    second_min = first_min;
                    first_min = cost[i][j];
                } else if (cost[i][j] < second_min) {
                    second_min = cost[i][j];
                }
            }
            row_penalty[i] = second_min - first_min;
            if (row_penalty[i] > max_row_penalty) {
                max_row_penalty = row_penalty[i];
                max_row_index = i;
            }
        }

        for (int j = 0; j < cols; j++) {
            int first_min = INT_MAX, second_min = INT_MAX;
            for (int i = 0; i < rows; i++) {
                if (cost[i][j] < first_min) {
                    second_min = first_min;
                    first_min = cost[i][j];
                } else if (cost[i][j] < second_min) {
                    second_min = cost[i][j];
                }
            }
            col_penalty[j] = second_min - first_min;
            if (col_penalty[j] > max_col_penalty) {
                max_col_penalty = col_penalty[j];
                max_col_index = j;
            }
        }

        // Termination condition
        if (max_row_index == -1 && max_col_index == -1) {
            break;
        }

        if (row_penalty[max_row_index] >= col_penalty[max_col_index]) {
            int min_supply = (supply[max_row_index] < demand[max_col_index]) ? supply[max_row_index] : demand[max_col_index];
            allocation[max_row_index][max_col_index] = min_supply;

            supply[max_row_index] -= min_supply;
            demand[max_col_index] -= min_supply;

            for (int i = 0; i < rows; i++) {
                cost[i][max_col_index] = INT_MAX;
            }
        } else {
            int min_supply = (supply[max_row_index] < demand[max_col_index]) ? supply[max_row_index] : demand[max_col_index];
            allocation[max_row_index][max_col_index] = min_supply;

            supply[max_row_index] -= min_supply;
            demand[max_col_index] -= min_supply;

            for (int j = 0; j < cols; j++) {
                cost[max_row_index][j] = INT_MAX;
            }
        }
    }

    // Printing the allocation matrix
    printf("Allocation Matrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d\t", allocation[i][j]);
        }
        printf("\n");
    }

    // Free allocated memory
    for (int i = 0; i < rows; i++) {
        free(allocation[i]);
    }
    free(allocation);
    free(row_penalty);
    free(col_penalty);
}

int main() {
    int rows, cols;
    printf("Enter the number of sources: ");
    scanf("%d", &rows);

    printf("Enter the number of destinations: ");
    scanf("%d", &cols);

    int *supply = (int *)malloc(rows * sizeof(int));
    int *demand = (int *)malloc(cols * sizeof(int));
    int **cost = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        cost[i] = (int *)malloc(cols * sizeof(int));
    }

    printf("Enter the supply values for each source:\n");
    for (int i = 0; i < rows; i++) {
        scanf("%d", &supply[i]);
    }

    printf("Enter the demand values for each destination:\n");
    for (int i = 0; i < cols; i++) {
        scanf("%d", &demand[i]);
    }

    printf("Enter the transportation cost matrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%d", &cost[i][j]);
        }
    }

    vogelApproximation(demand, supply, cost, rows, cols);

    // Free allocated memory
    free(supply);
    free(demand);
    for (int i = 0; i < rows; i++) {
        free(cost[i]);
    }
    free(cost);

    return 0;
}
