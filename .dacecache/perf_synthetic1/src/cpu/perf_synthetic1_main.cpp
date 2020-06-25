#include <stdlib.h>
#include "perf_synthetic1.h"

int main(int argc, char** argv) {
  float a = 42;
  int n = 42;
  float * __restrict__ A_ger = (float*) calloc(n**2, sizeof(float));
  float * __restrict__ res = (float*) calloc(1, sizeof(float));
  float * __restrict__ x_gemv = (float*) calloc(n, sizeof(float));
  float * __restrict__ x_ger = (float*) calloc(n, sizeof(float));
  float * __restrict__ y1_ger = (float*) calloc(n, sizeof(float));
  float * __restrict__ y2_ger = (float*) calloc(n, sizeof(float));
  float * __restrict__ y3_ger = (float*) calloc(n, sizeof(float));
  float * __restrict__ y4_ger = (float*) calloc(n, sizeof(float));
  float * __restrict__ y5_ger = (float*) calloc(n, sizeof(float));
  float * __restrict__ y6_ger = (float*) calloc(n, sizeof(float));
  float * __restrict__ y7_ger = (float*) calloc(n, sizeof(float));
  float * __restrict__ y8_ger = (float*) calloc(n, sizeof(float));

  __dace_init_perf_synthetic1(A_ger, res, x_gemv, x_ger, y1_ger, y2_ger, y3_ger, y4_ger, y5_ger, y6_ger, y7_ger, y8_ger, a, n);
  __program_perf_synthetic1(A_ger, res, x_gemv, x_ger, y1_ger, y2_ger, y3_ger, y4_ger, y5_ger, y6_ger, y7_ger, y8_ger, a, n);
  __dace_exit_perf_synthetic1(A_ger, res, x_gemv, x_ger, y1_ger, y2_ger, y3_ger, y4_ger, y5_ger, y6_ger, y7_ger, y8_ger, a, n);

  free(Array (dtype=float, shape=(n**2,)));
  free(Array (dtype=float, shape=(1,)));
  free(Array (dtype=float, shape=(n,)));
  free(Array (dtype=float, shape=(n,)));
  free(Array (dtype=float, shape=(n,)));
  free(Array (dtype=float, shape=(n,)));
  free(Array (dtype=float, shape=(n,)));
  free(Array (dtype=float, shape=(n,)));
  free(Array (dtype=float, shape=(n,)));
  free(Array (dtype=float, shape=(n,)));
  free(Array (dtype=float, shape=(n,)));
  free(Array (dtype=float, shape=(n,)));
  return 0;
}
