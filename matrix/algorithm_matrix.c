/*====================================================================================================*/
/*====================================================================================================*/
#include <stdlib.h>
#include <stdio.h>

#include "algorithm_matrix.h"
/*====================================================================================================*/
/*====================================================================================================*
**函數 : Matrix_clear
**功能 : Clear Matrix
**輸入 : *matrix, data
**輸出 : none
**使用 : Matrix_clear(matrix, 0);
**====================================================================================================*/
/*====================================================================================================*/
void Matrix_clear( Matrix_TypeDef *matrix )
{
  memset(matrix->arr, 0, sizeof(double) * matrix->total);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : Matrix_create
**功能 : Create Matrix
**輸入 : rows, cols
**輸出 : *matrix
**使用 : matrix = Matrix_create(2, 2);
**====================================================================================================*/
/*====================================================================================================*/
Matrix_TypeDef *Matrix_create( uint16_t rows, uint16_t cols )
{
  Matrix_TypeDef *matrix;

  matrix = (Matrix_TypeDef *)malloc(sizeof(Matrix_TypeDef));
  matrix->rows  = rows;
  matrix->cols  = cols;
  matrix->total = rows * cols;
  matrix->arr = (double *)malloc(sizeof(double) * matrix->total);
  Matrix_clear(matrix);

  return matrix;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : Matrix_createDiag
**功能 : Create Diagonal Matrix
**輸入 : cols, data
**輸出 : *matrix
**使用 : matrix = Matrix_createDiag(2, 1);
**====================================================================================================*/
/*====================================================================================================*/
Matrix_TypeDef *Matrix_createDiag( uint16_t cols, double data )
{
  Matrix_TypeDef *matrix;

  matrix = (Matrix_TypeDef *)malloc(sizeof(Matrix_TypeDef));
  matrix->rows  = cols;
  matrix->cols  = cols;
  matrix->total = cols * cols;
  matrix->arr = (double *)malloc(sizeof(double) * matrix->total);
  Matrix_clear(matrix);

  for(uint16_t i = 0; i < cols; i++)
    matrix->arr[i * matrix->cols + i] = data;

  return matrix;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : Matrix_copy
**功能 : Copy Matrix
**輸入 : *matrixA
**輸出 : *matrix
**使用 : matrix = Matrix_copy(matrixA);
**====================================================================================================*/
/*====================================================================================================*/
Matrix_TypeDef *Matrix_copy( Matrix_TypeDef *matrixA )
{
  Matrix_TypeDef *matrix = Matrix_create(matrixA->rows, matrixA->cols);
  for(uint32_t i = 0; i < matrix->total; i++)
    matrix->arr[i] = matrixA->arr[i];

  return matrix;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : Matrix_copyArr
**功能 : Copy Array to Matrix
**輸入 : *array, rows, cols
**輸出 : *matrix
**使用 : matrix = Matrix_copyArr(array, row, col);
**====================================================================================================*/
/*====================================================================================================*/
Matrix_TypeDef *Matrix_copyArr( double *array, uint16_t rows, uint16_t cols )
{
  Matrix_TypeDef *matrix = Matrix_create(rows, cols);
  for(uint32_t i = 0; i < matrix->total; i++)
    matrix->arr[i] = array[i];

  return matrix;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : Matrix_delete
**功能 : Delete Matrix
**輸入 : *matrix
**輸出 : None
**使用 : Matrix_delete(matrix);
**====================================================================================================*/
/*====================================================================================================*/
void Matrix_delete( Matrix_TypeDef *matrix )
{
  free(matrix->arr);
  free(matrix);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : Matrix_setData
**功能 : Set Data
**輸入 : *matrix, rows, cols, data
**輸出 : None
**使用 : Matrix_setData(matrix, rows, cols, data);
**====================================================================================================*/
/*====================================================================================================*/
void Matrix_setData( Matrix_TypeDef *matrix, uint16_t rows, uint16_t cols, double data )
{
  if((rows < matrix->rows) && (cols < matrix->cols))
    matrix->arr[rows * matrix->cols + cols] = data;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : Matrix_getData
**功能 : Get Data
**輸入 : *matrix, rows, cols
**輸出 : data
**使用 : data = Matrix_getData(matrix, rows, cols);
**====================================================================================================*/
/*====================================================================================================*/
double Matrix_getData( Matrix_TypeDef *matrix, uint16_t rows, uint16_t cols )
{
  if((rows < matrix->rows) && (cols < matrix->cols))
    return matrix->arr[rows * matrix->cols + cols];

  return 0;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : Matrix_getDiag
**功能 : Get Diagonal
**輸入 : *matrixA
**輸出 : *matrix
**使用 : matrix = Matrix_getDiag(matrixA);
**====================================================================================================*/
/*====================================================================================================*/
Matrix_TypeDef *Matrix_getDiag( Matrix_TypeDef *matrixA )
{
  if(matrixA->rows != matrixA->cols)
    return NULL;

  Matrix_TypeDef *matrix = Matrix_create(matrixA->rows, matrixA->cols);
  for(uint16_t i = 0; i < matrix->rows; i++)
    matrix->arr[i * matrix->cols + i] = matrixA->arr[i * matrixA->rows + i];

  return matrix;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : Matrix_getMatrix
**功能 : Get Data
**輸入 : *matrixA, rows, cols, data
**輸出 : *matrix
**使用 : matrix = Matrix_getMatrix(matrixA, matrixA->rows - rows, matrixA->cols - cols, rows, cols);
**====================================================================================================*/
/*====================================================================================================*/
Matrix_TypeDef *Matrix_getMatrix( Matrix_TypeDef *matrixA, uint16_t pRows, uint16_t pCols, uint16_t rows, uint16_t cols )
{
  if(((pRows + rows) > matrixA->rows) || ((pCols + cols) > matrixA->cols))
    return NULL;

  uint32_t cnt = 0;
  Matrix_TypeDef *matrix = Matrix_create(rows, cols);
  for(uint16_t i = pRows; i < pRows + rows; i++) {
    for(uint16_t j = pCols; j < pCols + cols; j++) {
      matrix->arr[cnt++] = matrixA->arr[i * matrixA->cols + j];
    }
  }

  return matrix;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : Matrix_add
**功能 : Matrix Addition
**輸入 : *matrixA, *matrixB
**輸出 : *matrix
**使用 : matrix = Matrix_add(matrixA, matrixB);
**====================================================================================================*/
/*====================================================================================================*/
Matrix_TypeDef *Matrix_add( Matrix_TypeDef *matrixA, Matrix_TypeDef *matrixB )
{
  if((matrixA->rows != matrixB->rows) || (matrixA->cols != matrixB->cols))
    return NULL;

  Matrix_TypeDef *matrix = Matrix_create(matrixA->rows, matrixA->cols);
  for(uint16_t i = 0; i < matrix->rows; i++)
    for(uint16_t j = 0; j < matrix->cols; j++)
      matrix->arr[i * matrix->cols + j] = matrixA->arr[i * matrixA->cols + j] + matrixB->arr[i * matrixB->cols + j];

  return matrix;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : Matrix_sub
**功能 : Matrix Subtraction
**輸入 : *matrixA, *matrixB
**輸出 : *matrix
**使用 : matrix = Matrix_sub(matrixA, matrixB);
**====================================================================================================*/
/*====================================================================================================*/
Matrix_TypeDef *Matrix_sub( Matrix_TypeDef *matrixA, Matrix_TypeDef *matrixB )
{
  if((matrixA->rows != matrixB->rows) || (matrixA->cols != matrixB->cols))
    return NULL;

  Matrix_TypeDef *matrix = Matrix_create(matrixA->rows, matrixA->cols);
  for(uint16_t i = 0; i < matrix->rows; i++)
    for(uint16_t j = 0; j < matrix->cols; j++)
      matrix->arr[i * matrix->cols + j] = matrixA->arr[i * matrixA->cols + j] - matrixB->arr[i * matrixB->cols + j];

  return matrix;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : Matrix_mul
**功能 : Matrix Multiplication
**輸入 : *matrixA, *matrixB
**輸出 : *matrix
**使用 : matrix = Matrix_mul(matrixA, matrixB);
**====================================================================================================*/
/*====================================================================================================*/
Matrix_TypeDef *Matrix_mul( Matrix_TypeDef *matrixA, Matrix_TypeDef *matrixB )
{
  if(matrixA->cols != matrixB->rows)
    return NULL;

  Matrix_TypeDef *matrix = Matrix_create(matrixA->rows, matrixB->cols);
  for(uint16_t i = 0; i < matrixA->rows; i++) {
    for(uint16_t j = 0; j < matrixB->cols; j++) {
      for(uint16_t k = 0; k < matrixA->cols; k++) {
        matrix->arr[i * matrix->cols + j] += matrixA->arr[i * matrixA->cols + k] * matrixB->arr[k * matrixA->cols + j];
      }
    }
  }

  return matrix;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : Matrix_transpose
**功能 : Matrix Transpose
**輸入 : *matrixA
**輸出 : *matrix
**使用 : matrix = Matrix_transpose(matrixA);
**====================================================================================================*/
/*====================================================================================================*/
Matrix_TypeDef *Matrix_transpose( Matrix_TypeDef *matrixA )
{
  Matrix_TypeDef *matrix = Matrix_create(matrixA->cols, matrixA->rows);

  for(uint16_t i = 0; i < matrixA->rows; i++)
    for(uint16_t j = 0; j < matrixA->cols; j++)
      matrix->arr[j * matrix->cols + i] = matrixA->arr[i * matrixA->cols + j];

  return matrix;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : Matrix_inv
**功能 : Inverse Matrix ( Gaussian Elimination )
**輸入 : *matrixA
**輸出 : *matrix
**使用 : matrix = Matrix_inv(matrixA);
**====================================================================================================*/
/*====================================================================================================*/
Matrix_TypeDef *Matrix_inv( Matrix_TypeDef *matrixA )
{
  int32_t i = 0, j = 0;

  if(matrixA->rows != matrixA->cols)
    return NULL;

  /* check nonsingular */
  // if matrix is nonsingular
  // return ERROR;

  Matrix_TypeDef *matrix = Matrix_create(matrixA->rows, matrixA->rows << 1);
  for(uint16_t i = 0; i < matrixA->rows; i++) {
    matrix->arr[i * matrix->cols + matrixA->cols + i] = 1.0;
    for(uint16_t j = 0; j < matrixA->cols; j++) {
      matrix->arr[i * matrix->cols + j] = matrixA->arr[i * matrixA->cols + j];
    }
  }

  Matrix_TypeDef *matrixInv = Matrix_gaussianElimination(matrix);
  Matrix_delete(matrix);
  matrix = Matrix_create(matrixA->rows, matrixA->cols);

  uint32_t cnt = 0;
  for(uint16_t i = 0; i < matrixInv->rows; i++) {
    for(uint16_t j = matrixInv->rows; j < matrixInv->cols; j++) {
      matrix->arr[cnt++] = matrixInv->arr[i * matrixInv->cols + j];
    }
  }
  Matrix_delete(matrixInv);

  return matrix;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : Matrix_gaussianElimination
**功能 : Gaussian Elimination
**輸入 : *matrixA
**輸出 : *matrix
**使用 : matrix = Matrix_gaussianElimination(matrixA);
**====================================================================================================*/
/*====================================================================================================*/
Matrix_TypeDef *Matrix_gaussianElimination( Matrix_TypeDef *matrixA )
{
  double tmp;
  int32_t i = 0, j = 0, k = 0;

  /* check nonsingular */
  // if matrix is nonsingular
  // return ERROR;

  Matrix_TypeDef *matrix = Matrix_copy(matrixA);

  /* left-down to zero */
  for(i = 0; i < matrix->rows - 1; i++) {
    for(j = i + 1; j < matrix->rows; j++) {
      tmp = matrix->arr[j * matrix->cols + i] / matrix->arr[i * matrix->cols + i];
      matrix->arr[j * matrix->cols + i] = 0;
      for(k = i + 1; k < matrix->cols; k++) {
        matrix->arr[j * matrix->cols + k] -= tmp * matrix->arr[i * matrix->cols + k];
      }
    }
  }

  /* diagonal to one */
  for(i = 0; i < matrix->rows; i++) {
    tmp = matrix->arr[i * matrix->cols + i];
    matrix->arr[i * matrix->cols + i] = 1.0;
    for(j = i + 1; j < matrix->cols; j++) {
      matrix->arr[i * matrix->cols + j] = matrix->arr[i * matrix->cols + j] / tmp;
    }
  }

  /* right-up to zero */
  for(i = matrix->rows - 1; i > 0; i--) {
    for(j = i - 1; j >= 0; j--) {
      tmp = matrix->arr[j * matrix->cols + i];
      matrix->arr[j * matrix->cols + i] = 0;
      for(k = matrix->rows; k < matrix->cols; k++) {
        matrix->arr[j * matrix->cols + k] -= tmp * matrix->arr[i * matrix->cols + k];
      }
    }
  }

  return matrix;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : Matrix_det
**功能 : Determinant
**輸入 : *matrix
**輸出 : data
**使用 : data = Matrix_det(matrix);
**====================================================================================================*/
/*====================================================================================================*/
double Matrix_det( Matrix_TypeDef *matrix )
{
  if(matrix->cols != matrix->rows)
    return 0;


//  return det;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : Matrix_cholesky
**功能 : cholesky
**輸入 : *matrixA
**輸出 : *matrix
**使用 : matrix = Matrix_cholesky(matrix);
**====================================================================================================*/
/*====================================================================================================*/
Matrix_TypeDef *Matrix_cholesky( Matrix_TypeDef *matrixA )
{
  if(matrixA->cols != matrixA->rows)
    return NULL;

  Matrix_TypeDef *matrix = Matrix_create(matrixA->cols, matrixA->rows);
/*
  double tempSum = 0;
  for(uint16_t j = 0; j < matrix->cols; j++) {
    for(uint16_t i = j; i < matrix->rows; i++) {
      tempSum = 0;
      if(i == j) {
        for(uint16_t k = 0; k < i - 1; k++)
          tempSum = tempSum + sqrt_matrix(i, k)^2;
        matrix->arr[i * matrix->cols + j] = sqrt(pdMatrix[i * matrix->cols + j] - tempSum);
      }
      else {
        for(uint16_t k = 0; k < j - 1; k++)
          tempSum = tempSum + sqrt_matrix(i, k) * sqrt_matrix(j, k);
        sqrt_matrix(i, j) = (pdMatrix(i, j) - tempSum) / sqrt_matrix(j, j);
      }
    }
  }
*/
  return matrix;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : Matrix_print
**功能 : Print Matrix
**輸入 : *matrix
**輸出 : None
**使用 : Matrix_print(matrix);
**====================================================================================================*/
/*====================================================================================================*/
void Matrix_print( Matrix_TypeDef *matrix )
{
  for(uint16_t i = 0; i < matrix->rows; i++) {
    for(uint16_t j = 0; j < matrix->cols; j++)
      printf("%.2f\t", matrix->arr[i * matrix->cols + j]);
    printf("\n");
  }
}
/*====================================================================================================*/
/*====================================================================================================*/
