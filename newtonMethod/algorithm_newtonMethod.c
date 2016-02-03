/*====================================================================================================*/
/*====================================================================================================*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "algorithm_matrix.h"
#include "algorithm_newtonMethod.h"

#define row_X 9
#define col_X 1
/*====================================================================================================*/
/*====================================================================================================*/
void newtonMethod_G( const Matrix_TypeDef *matrixX, const double *pAccel, const uint16_t n, Matrix_TypeDef *matrixG );
/*====================================================================================================*/
/*====================================================================================================*
**函數 : newtonMethod
**功能 :
**輸入 : *matrixX, *pAccel, alpha, n
**輸出 : none
**使用 : newtonMethod(matrixX, matrixA, alpha, n);
**====================================================================================================*/
/*====================================================================================================*/
void newtonMethod( const Matrix_TypeDef *matrixX, const Matrix_TypeDef *matrixA, const double alpha, const uint32_t n )
{
  Matrix_TypeDef *matrixG = Matrix_create(matrixX->rows, matrixX->cols);

  // gauss-newton method
  for(uint32_t i = 0; i < n; i++) {
    newtonMethod_G(matrixX, matrixA->arr, matrixA->cols, matrixG);
    Matrix_mulNumb(matrixG, matrixG, alpha);
    Matrix_sub(matrixX, matrixX, matrixG);
  }

  Matrix_delete(matrixG);
}
/*====================================================================================================*/
/*====================================================================================================*/
void newtonMethod_e( const double *arrayX, const double *pAccel, double *param_e )
{
  double accel[3] = {0};
  double param[3] = {0};

  for(uint8_t i = 0; i < 3; i++)
    accel[i] = pAccel[i] - arrayX[6 + i];

  param[0] = arrayX[0] * accel[0] + arrayX[1] * accel[1] + arrayX[2] * accel[2];
  param[1] = arrayX[1] * accel[0] + arrayX[3] * accel[1] + arrayX[4] * accel[2];
  param[2] = arrayX[2] * accel[0] + arrayX[4] * accel[1] + arrayX[5] * accel[2];

  *param_e = param[0] * param[0] + param[1] * param[1] + param[2] * param[2] - 1000000.0;
}
/*====================================================================================================*/
/*====================================================================================================*/
void newtonMethod_Ge( const double *arrayX, const double *pAccel, double *param_Ge )
{
  double param_A = arrayX[0] * arrayX[0] + arrayX[1] * arrayX[1] + arrayX[2] * arrayX[2];
  double param_B = arrayX[1] * arrayX[1] + arrayX[3] * arrayX[3] + arrayX[4] * arrayX[4];
  double param_C = arrayX[2] * arrayX[2] + arrayX[4] * arrayX[4] + arrayX[5] * arrayX[5];
  double param_D = arrayX[0] * arrayX[1] + arrayX[1] * arrayX[3] + arrayX[2] * arrayX[4];
  double param_E = arrayX[1] * arrayX[2] + arrayX[3] * arrayX[4] + arrayX[4] * arrayX[5];
  double param_F = arrayX[0] * arrayX[2] + arrayX[1] * arrayX[4] + arrayX[2] * arrayX[5];

  double accel[3] = {0};
  for(uint8_t i = 0; i < 3; i++)
    accel[i] = pAccel[i] - arrayX[6 + i];

  double param_a1a1 = accel[0] * accel[0];
  double param_a1a2 = accel[0] * accel[1];
  double param_a1a3 = accel[0] * accel[2];
  double param_a2a2 = accel[1] * accel[1];
  double param_a2a3 = accel[1] * accel[2];
  double param_a3a3 = accel[2] * accel[2];

  param_Ge[0] = arrayX[0] * param_a1a1 + arrayX[1] * param_a1a2 + arrayX[2] * param_a1a3;
  param_Ge[1] = arrayX[1] * (param_a1a1 + param_a2a2) + (arrayX[0] + arrayX[3]) * param_a1a2 + arrayX[2] * param_a2a3 + arrayX[4] * param_a1a3;
  param_Ge[2] = arrayX[2] * (param_a1a1 + param_a3a3) + arrayX[4] * param_a1a2 + arrayX[1] * param_a2a3 + (arrayX[0] + arrayX[5]) * param_a1a3;
  param_Ge[3] = arrayX[1] * param_a1a2 + arrayX[3] * param_a2a2 + arrayX[4] * param_a2a3;
  param_Ge[4] = arrayX[4] * (param_a2a2 + param_a3a3) + arrayX[2] * param_a1a2 + (arrayX[3] + arrayX[5]) * param_a2a3 + arrayX[1] * param_a1a3;
  param_Ge[5] = arrayX[2] * param_a1a3 + arrayX[4] * param_a2a3 + arrayX[5] * param_a3a3;
  param_Ge[6] = - param_A * accel[0] - param_D * accel[1] - param_F * accel[2];
  param_Ge[7] = - param_D * accel[0] - param_B * accel[1] - param_E * accel[2];
  param_Ge[8] = - param_F * accel[0] - param_E * accel[1] - param_C * accel[2];
}
/*====================================================================================================*/
/*====================================================================================================*/
void newtonMethod_G( const Matrix_TypeDef *matrixX, const double *pAccel, const uint16_t n, Matrix_TypeDef *matrixG )
{
  double accel[3] = {0};
  double param_e = 0;
  double param_Ge[row_X * col_X] = {0};

  Matrix_TypeDef *matrixGE  = Matrix_create(row_X, col_X);
  Matrix_TypeDef *matrixG2E = Matrix_create(row_X, row_X);

  for(uint8_t i = 0; i < n; i++) {
    accel[0] = pAccel[0 * n + i];
    accel[1] = pAccel[1 * n + i];
    accel[2] = pAccel[2 * n + i];
    newtonMethod_e(matrixX->arr, accel, &param_e);
    newtonMethod_Ge(matrixX->arr, accel, param_Ge);

    // G2E = sum(Ge^T * Ge)
    for(uint8_t j = 0; j < row_X; j++) {
      matrixGE->arr[j] += param_e * param_Ge[j];
      for(uint8_t k = 0; k < row_X; k++) {
        matrixG2E->arr[k * row_X + j] += param_Ge[j] * param_Ge[k];
      }
    }
  }

  Matrix_inv(matrixG2E, matrixG2E);
  Matrix_mul(matrixG, matrixG2E, matrixGE);

  Matrix_delete(matrixGE);
  Matrix_delete(matrixG2E);
}
/*====================================================================================================*/
/*====================================================================================================*/
