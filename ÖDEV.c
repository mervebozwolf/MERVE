#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROW1 2
#define COL1 3
#define ROW2 3
#define COL2 2

void fillMatrix(int rows, int cols, int matrix[rows][cols]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = rand() % 101; 
        }
    }
}

void printMatrix(int rows, int cols, int matrix[rows][cols]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%4d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    srand(time(NULL)); 

    int matrix1[ROW1][COL1];
    int matrix2[ROW2][COL2];
    int result[ROW1][COL2];

  
    fillMatrix(ROW1, COL1, matrix1);
    fillMatrix(ROW2, COL2, matrix2);

    
    printf("Matrix 1 (%dx%d):\n", ROW1, COL1);
    printMatrix(ROW1, COL1, matrix1);

    
    printf("\nMatrix 2 (%dx%d):\n", ROW2, COL2);
    printMatrix(ROW2, COL2, matrix2);

    
    for (int i = 0; i < ROW1; i++) {
        for (int j = 0; j < COL2; j++) {
            result[i][j] = 0;
            for (int k = 0; k < COL1; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

  
    printf("\nMatrix Multiplication Result (%dx%d):\n", ROW1, COL2);
    printMatrix(ROW1, COL2, result);

    return 0;
}
