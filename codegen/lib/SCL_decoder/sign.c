/*
 * File: sign.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 27-Nov-2022 10:23:53
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "SCL_decoder.h"
#include "sign.h"

/* Function Definitions */

/*
 * Arguments    : double *x
 * Return Type  : void
 */
void b_sign(double *x)
{
  if (*x < 0.0) {
    *x = -1.0;
  } else if (*x > 0.0) {
    *x = 1.0;
  } else {
    if (*x == 0.0) {
      *x = 0.0;
    }
  }
}

/*
 * File trailer for sign.c
 *
 * [EOF]
 */
