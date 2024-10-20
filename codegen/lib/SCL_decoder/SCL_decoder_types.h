/*
 * File: SCL_decoder_types.h
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 27-Nov-2022 10:23:53
 */

#ifndef SCL_DECODER_TYPES_H
#define SCL_DECODER_TYPES_H

/* Include Files */
#include "rtwtypes.h"

/* Type Definitions */
#ifndef struct_emxArray_real_T
#define struct_emxArray_real_T

struct emxArray_real_T
{
  double *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};

#endif                                 /*struct_emxArray_real_T*/

#ifndef typedef_emxArray_real_T
#define typedef_emxArray_real_T

typedef struct emxArray_real_T emxArray_real_T;

#endif                                 /*typedef_emxArray_real_T*/
#endif

/*
 * File trailer for SCL_decoder_types.h
 *
 * [EOF]
 */
