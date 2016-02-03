#include <stdlib.h>
#include <stdio.h>

#include "algorithm_matrix.h"
#include "algorithm_newtonMethod.h"

#define row_A 3
#define col_A 18
double arrayA[row_A * col_A] = {
   1.0000, -1.0000,  0.0000,  0.0000,  0.0000,  0.0000,  0.7070,  0.7070, -0.7070, -0.7070,  0.7070,  0.7070, -0.7070, -0.7070,  0.0000,  0.0000,  0.0000,  0.0000,
   0.0000,  0.0000,  1.0000, -1.0000,  0.0000,  0.0000,  0.7070, -0.7070, -0.7070,  0.7070,  0.0000,  0.0000,  0.0000,  0.0000,  0.7070,  0.7070, -0.7070, -0.7070,
   0.0000,  0.0000,  0.0000,  0.0000,  1.0000, -1.0000,  0.0000,  0.0000,  0.0000,  0.0000,  0.7070, -0.7070, -0.7070,  0.7070,  0.7070, -0.7070, -0.7070,  0.7070,
};

#define row_K 3
#define col_K 3
double arrayK[row_K * col_K] = {
   0.9980, -0.0109,  0.0293,
  -0.0109,  1.0419,  0.0509,
   0.0293,  0.0509,  0.9552,
};

#define row_B 3
#define col_B 1
double arrayB[row_B * col_B] = {
   35.9405,
   31.0196,
  -67.4777,
};

#define row_X 9
#define col_X 1
double arrayX[row_X * col_X] = {
  1.0,
  0.0,
  0.0,
  1.0,
  0.0,
  1.0,
  0.0,
  0.0,
  0.0,
};

int main()
{
  Matrix_TypeDef *matrixA = Matrix_createPtr(arrayA, row_A, col_A);
  Matrix_TypeDef *matrixK = Matrix_createPtr(arrayK, row_K, col_K);
  Matrix_TypeDef *matrixS = Matrix_create(row_K, col_K);
  Matrix_TypeDef *matrixB = Matrix_createPtr(arrayB, row_B, col_B);
  Matrix_TypeDef *matrixX = Matrix_createPtr(arrayX, row_X, col_X);

  // cal noiseA
  Matrix_inv(matrixS, matrixK);                     // K = inv(K)
  for(uint8_t i = 0; i < col_A; i++) {
    Matrix_TypeDef *tmpMatrixA = Matrix_create(row_A, 1);

    Matrix_getMatrix(tmpMatrixA, matrixA, 0, i);    // tmpA = A(:, i)
    Matrix_mulNumb(tmpMatrixA, tmpMatrixA, 1000);   // tmpA = tmpA * 1000
    Matrix_mul(tmpMatrixA, matrixS, tmpMatrixA);    // tmpA = K * tmpA
    Matrix_add(tmpMatrixA, tmpMatrixA, matrixB);    // tmpA = tmpA + b
    Matrix_setMatrix(matrixA, tmpMatrixA, 0, i);    // A(:, i) = tmpA

    Matrix_delete(tmpMatrixA);
  }

  // gauss-newton method
  newtonMethod(matrixX, matrixA, 0.32, 100);

  // print result
  printf("\n\t origin\t\t newton\t\t(newton - origin) / origin * 100\n");
  printf("k_11\t%.6f\t%.6f\terr = %.24f\n", arrayK[0], arrayX[0], (arrayX[0] - arrayK[0]) / arrayK[0] * 100);
  printf("k_12\t%.6f\t%.6f\terr = %.24f\n", arrayK[1], arrayX[1], (arrayX[1] - arrayK[1]) / arrayK[1] * 100);
  printf("k_13\t%.6f\t%.6f\terr = %.24f\n", arrayK[2], arrayX[2], (arrayX[2] - arrayK[2]) / arrayK[2] * 100);
  printf("k_22\t%.6f\t%.6f\terr = %.24f\n", arrayK[4], arrayX[3], (arrayX[3] - arrayK[4]) / arrayK[4] * 100);
  printf("k_23\t%.6f\t%.6f\terr = %.24f\n", arrayK[5], arrayX[4], (arrayX[4] - arrayK[5]) / arrayK[5] * 100);
  printf("k_33\t%.6f\t%.6f\terr = %.24f\n", arrayK[8], arrayX[5], (arrayX[5] - arrayK[8]) / arrayK[8] * 100);
  printf("b_x \t%.6f\t%.6f\terr = %.24f\n", arrayB[0], arrayX[6], (arrayX[6] - arrayB[0]) / arrayB[0] * 100);
  printf("b_y \t%.6f\t%.6f\terr = %.24f\n", arrayB[1], arrayX[7], (arrayX[7] - arrayB[1]) / arrayB[1] * 100);
  printf("b_z \t%.6f\t%.6f\terr = %.24f\n", arrayB[2], arrayX[8], (arrayX[8] - arrayB[2]) / arrayB[2] * 100);

  Matrix_delete(matrixA);
  Matrix_delete(matrixK);
  Matrix_delete(matrixS);
  Matrix_delete(matrixB);
  Matrix_delete(matrixX);
}
/*====================================================================================================*/
/*====================================================================================================*/
