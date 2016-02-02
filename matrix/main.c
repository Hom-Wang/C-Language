#include <stdlib.h>
#include <stdio.h>

#include "algorithm_matrix.h"

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
double array[row_n * col_n] = {
   1.0,  3.0, -5.0,  2.0,
   4.0, -3.0,  1.0,  5.0,
   6.0, -2.0,  2.0,  4.0,
   0.0,  2.0,  3.0, -7.0,
};

int main()
{
  Matrix_TypeDef matrix;
  Matrix_init(&matrix, array, row_n, col_n);

  printf("\n");
  printf(" matrix\n");
  Matrix_print(&matrix);
  printf("\n");

  Matrix_inv(&matrix, &matrix);

  printf(" matrix inv\n");
  Matrix_print(&matrix);
  printf("\n");
}
