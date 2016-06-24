#include <stdlib.h>
#include <stdio.h>

#include "matrix.h"

/*
#define row_n 4
#define col_n 8
double array[row_n * col_n] = {
   1.0,  3.0, -5.0,  2.0,  1.0,  0.0,  0.0,  0.0,
   4.0, -3.0,  1.0,  5.0,  0.0,  1.0,  0.0,  0.0,
   6.0, -2.0,  2.0,  4.0,  0.0,  0.0,  1.0,  0.0,
   0.0,  2.0,  3.0, -7.0,  0.0,  0.0,  0.0,  1.0
};
*/

#define row_n 4
#define col_n 4
matrix_arr_t arrayA[row_n * col_n] = {
   1.0,  3.0, -5.0,  2.0,
   4.0, -3.0,  1.0,  5.0,
   6.0, -2.0,  2.0,  4.0,
   0.0,  2.0,  3.0, -7.0,
};

matrix_arr_t arrayB[row_n * col_n] = {
   0.000056,  3.0, -5.0,  72.0,
   0.000115, -1.0,  1.0,  2120.0,
   0.000841, -2.0,  8.0,  10.0,
   0.000016,  2.0,  3.0, -86.0,
};

int main()
{
  matrix_t matrixA;
  Matrix_Init(&matrixA, arrayA, row_n, col_n);

  matrix_t *matrixB = Matrix_CreatePtr(arrayB, row_n, col_n);
  matrix_t *matrixC = Matrix_Create(row_n, col_n);
  Matrix_Clear(matrixC);

  printf("\n");

  printf(" matrixA\n");
  Matrix_Print(&matrixA);
  printf("\n");

  printf(" matrixB\n");
  Matrix_Print(matrixB);
  printf("\n");

  printf(" matrixC\n");
  Matrix_Print(matrixC);
  printf("\n");

  // matrixC = matrixA * matrixB
  Matrix_Mul(matrixC, &matrixA, matrixB);
  printf(" matrixC = matrixA * matrixB\n");
  Matrix_Print(matrixC);
  printf("\n");

  // matrixC = inv(matrixC)
  Matrix_Inv(matrixC, matrixC);
  printf(" matrixC = inv(matrixC)\n");
  Matrix_Print(matrixC);
  printf("\n");

  Matrix_Delete(matrixB);
  Matrix_Delete(matrixC);
}
