/*
 * File: SCL_decoder_emxutil.h
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 27-Nov-2022 10:23:53
 */

#ifndef SCL_DECODER_EMXUTIL_H
#define SCL_DECODER_EMXUTIL_H

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "SCL_decoder_types.h"

/* Function Declarations */
extern void emxEnsureCapacity_real_T(emxArray_real_T *emxArray, int oldNumel);
extern void emxFree_real_T(emxArray_real_T **pEmxArray);
extern void emxInit_real_T(emxArray_real_T **pEmxArray, int numDimensions);

#endif

/*
 * File trailer for SCL_decoder_emxutil.h
 *
 * [EOF]
 */
