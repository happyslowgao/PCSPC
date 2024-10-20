/*
 * File: sum.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 27-Nov-2022 10:23:53
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "SCL_decoder.h"
#include "sum.h"

/* Function Definitions */

/*
 * Arguments    : const double x_data[]
 *                const int x_size[1]
 * Return Type  : double
 */
double sum(const double x_data[], const int x_size[1])
{
  double y;
  int k;
  if (x_size[0] == 0) {
    y = 0.0;
  } else {
    y = x_data[0];
    for (k = 2; k <= x_size[0]; k++) {
      y += x_data[k - 1];
    }
  }

  return y;
}

/*
 * File trailer for sum.c
 *
 * [EOF]
 */
