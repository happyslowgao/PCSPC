/*
 * File: nonSingletonDim.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 27-Nov-2022 10:23:53
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "SCL_decoder.h"
#include "nonSingletonDim.h"

/* Function Definitions */

/*
 * Arguments    : const int x_size[1]
 * Return Type  : int
 */
int nonSingletonDim(const int x_size[1])
{
  int dim;
  dim = 2;
  if (x_size[0] != 1) {
    dim = 1;
  }

  return dim;
}

/*
 * File trailer for nonSingletonDim.c
 *
 * [EOF]
 */
