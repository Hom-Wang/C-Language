/* #include "algorithm_matrix.h" */

#ifndef __ALGORITHM_MATRIX_H
#define __ALGORITHM_MATRIX_H

#include <stdint.h>
/*====================================================================================================*/
/*====================================================================================================*/
typedef struct {
   uint16_t rows;
   uint16_t cols;
   uint16_t total;
   double   *arr;
} Matrix_TypeDef;
/*====================================================================================================*/
/*====================================================================================================*/
void            Matrix_clear( Matrix_TypeDef *matrix );
Matrix_TypeDef *Matrix_create( uint16_t rows, uint16_t cols );
Matrix_TypeDef *Matrix_createDiag( uint16_t cols, double data );
Matrix_TypeDef *Matrix_copy( Matrix_TypeDef *matrixA );
Matrix_TypeDef *Matrix_copyArr( double *array, uint16_t rows, uint16_t cols );
void            Matrix_delete( Matrix_TypeDef *matrix );

void            Matrix_setData( Matrix_TypeDef *matrix, uint16_t rows, uint16_t cols, double data );
double          Matrix_getData( Matrix_TypeDef *matrix, uint16_t rows, uint16_t cols );
Matrix_TypeDef *Matrix_getDiag( Matrix_TypeDef *matrix );
Matrix_TypeDef *Matrix_getMatrix( Matrix_TypeDef *matrixA, uint16_t pRows, uint16_t pCols, uint16_t rows, uint16_t cols );

Matrix_TypeDef *Matrix_add( Matrix_TypeDef *matrixA, Matrix_TypeDef *matrixB );
Matrix_TypeDef *Matrix_sub( Matrix_TypeDef *matrixA, Matrix_TypeDef *matrixB );
Matrix_TypeDef *Matrix_mul( Matrix_TypeDef *matrixA, Matrix_TypeDef *matrixB );
Matrix_TypeDef *Matrix_transpose( Matrix_TypeDef *matrixA );
Matrix_TypeDef *Matrix_inv( Matrix_TypeDef *matrixA );
Matrix_TypeDef *Matrix_gaussianElimination( Matrix_TypeDef *matrixA );
Matrix_TypeDef *Matrix_cholesky( Matrix_TypeDef *matrixA );
double          Matrix_det( Matrix_TypeDef *matrix );

void            Matrix_print( Matrix_TypeDef *matrix );
/*====================================================================================================*/
/*====================================================================================================*/
#endif
