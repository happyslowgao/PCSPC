/*
 * File: sort1.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 27-Nov-2022 10:23:53
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "SCL_decoder.h"
#include "sort1.h"
#include "sortIdx.h"
#include "nonSingletonDim.h"

/* Type Definitions */
#ifndef struct_emxArray_int32_T_254
#define struct_emxArray_int32_T_254

struct emxArray_int32_T_254
{
  int data[254];
  int size[1];
};

#endif                                 /*struct_emxArray_int32_T_254*/

#ifndef typedef_emxArray_int32_T_254
#define typedef_emxArray_int32_T_254

typedef struct emxArray_int32_T_254 emxArray_int32_T_254;

#endif                                 /*typedef_emxArray_int32_T_254*/

/* Function Definitions */

/*
 * Arguments    : double x_data[]
 *                int x_size[1]
 *                int idx_data[]
 *                int idx_size[1]
 * Return Type  : void
 */
void b_sort(double x_data[], int x_size[1], int idx_data[], int idx_size[1])
{
  int dim;
  int i7;
  int vwork_size[1];
  int vstride;
  int k;
  double vwork_data[254];
  int iidx_data[254];
  int iidx_size[1];
  dim = nonSingletonDim(x_size);
  if (dim <= 1) {
    i7 = x_size[0];
  } else {
    i7 = 1;
  }

  vwork_size[0] = (unsigned char)i7;
  idx_size[0] = (unsigned char)x_size[0];
  vstride = 1;
  k = 1;
  while (k <= dim - 1) {
    vstride *= x_size[0];
    k = 2;
  }

  for (dim = 0; dim + 1 <= vstride; dim++) {
    for (k = 0; k + 1 <= i7; k++) {
      vwork_data[k] = x_data[dim + k * vstride];
    }

    sortIdx(vwork_data, vwork_size, iidx_data, iidx_size);
    for (k = 0; k + 1 <= i7; k++) {
      x_data[dim + k * vstride] = vwork_data[k];
      idx_data[dim + k * vstride] = iidx_data[k];
    }
  }
}

/*
 * Arguments    : double x_data[]
 *                int x_size[1]
 * Return Type  : void
 */
void sort(double x_data[], int x_size[1])
{
  int dim;
  int i6;
  int vwork_size[1];
  int vstride;
  int k;
  double vwork_data[254];
  emxArray_int32_T_254 b_vwork_data;
  dim = nonSingletonDim(x_size);
  if (dim <= 1) {
    i6 = x_size[0];
  } else {
    i6 = 1;
  }

  vwork_size[0] = (unsigned char)i6;
  vstride = 1;
  k = 1;
  while (k <= dim - 1) {
    vstride *= x_size[0];
    k = 2;
  }

  for (dim = 0; dim + 1 <= vstride; dim++) {
    for (k = 0; k + 1 <= i6; k++) {
      vwork_data[k] = x_data[dim + k * vstride];
    }

    sortIdx(vwork_data, vwork_size, b_vwork_data.data, b_vwork_data.size);
    for (k = 0; k + 1 <= i6; k++) {
      x_data[dim + k * vstride] = vwork_data[k];
    }
  }
}

/*
 * File trailer for sort1.c
 *
 * [EOF]
 */
