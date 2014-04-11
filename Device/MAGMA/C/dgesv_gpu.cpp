#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "magma.h"

using namespace std;

int main(void)
{
  magma_init();
  double *b, *AT, *b_d, *AT_d;
  double A[3][3];
  int a = 0;
  magma_int_t* pivot;
  magma_int_t i = 0, j = 0, ok, status;
  magma_int_t m = 3, n = 1, mm = 9, mn = 3;
  magma_int_t info;

  AT = (double*)malloc(9*sizeof(double));
  b = (double*)malloc(3*sizeof(double));
  pivot = (magma_int_t*)malloc(3*sizeof(int));

  A[0][0] = 3.1;
  A[0][1] = 1.3;
  A[0][2] = -5.7;
  A[1][0] = 1;
  A[1][1] = -6.9;
  A[1][2] = 5.8;
  A[2][0] = 3.4;
  A[2][1] = 7.2;
  A[2][2] = -8.8;

  b[0] = -1.3;
  b[1] = -0.1;
  b[2] = 1.8;
  for(a = 0; a<3; a++)
    for(j = 0; j<3; j++)
      AT[j+3*a]=A[j][a];

  //cudaMalloc((void**)&AT_d,9*sizeof(double));
  //cudaMalloc((void**)&b_d,3*sizeof(double));

  magma_dmalloc(&AT_d, m*m);
  magma_dmalloc(&b_d, m);
  magma_dsetmatrix( m, m, AT, m, AT_d, m);
  magma_dsetmatrix(m, n, b, m, b_d, m);

  //cudaMemcpy(AT_d, AT, 9*sizeof(double),cudaMemcpyHostToDevice);
  
  magma_dgesv_gpu(m, 1, AT_d, m, pivot, b_d, m, &info);
  magma_dgetmatrix(m,n,b_d,m,b,m);

  //cudaMemcpy(b,b_d,3*sizeof(double),cudaMemcpyDeviceToHost);

  for (i = 0; i < 3; i++)
  {
    printf("%f\n", b[i]);
  }
  return 0;
}
