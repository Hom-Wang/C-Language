#include <stdlib.h>
#include <stdio.h>

#include "algorithm_matrix.h"

/*
#define row_n 4
#define col_n 8
double array[col_n * row_n] = {
  1.0,  3.0, -5.0,  2.0, 1.0, 0.0, 0.0, 0.0,
  4.0, -3.0,  1.0,  5.0, 0.0, 1.0, 0.0, 0.0,
  6.0, -2.0,  2.0,  4.0, 0.0, 0.0, 1.0, 0.0,
  0.0,  2.0,  3.0, -7.0, 0.0, 0.0, 0.0, 1.0
};
*/
#define row_n 4
#define col_n 4
double array[col_n * row_n] = {
  1.0,  3.0, -5.0,  2.0,
  4.0, -3.0,  1.0,  5.0,
  6.0, -2.0,  2.0,  4.0,
  0.0,  2.0,  3.0, -7.0
};

int main()
{
  Matrix_TypeDef *matrix;
  Matrix_TypeDef *matrixA = Matrix_copyArr(array, row_n, col_n);
  Matrix_TypeDef *matrixB;

  printf("matrixA\n");
  Matrix_print(matrixA);
  printf("\n");

  printf("Inv matrixA\n");
  matrix = Matrix_inv(matrixA);
  Matrix_print(matrix);
  printf("\n");
/*
  printf("Matrix_getMatrix\n");
  matrixB = Matrix_getMatrix(matrix, 0, 4, 3, 3);
  Matrix_print(matrixB);
  printf("\n");
*/
  Matrix_delete(matrix);
  Matrix_delete(matrixA);
/*
  Matrix_delete(matrixB);
*/
  return;
}
