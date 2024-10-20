/*
 * File: _coder_SCL_decoder_api.h
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 27-Nov-2022 10:23:53
 */

#ifndef _CODER_SCL_DECODER_API_H
#define _CODER_SCL_DECODER_API_H

/* Include Files */
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include <stddef.h>
#include <stdlib.h>
#include "_coder_SCL_decoder_api.h"

/* Type Definitions */
#ifndef struct_emxArray_real_T
#define struct_emxArray_real_T

struct emxArray_real_T
{
  real_T *data;
  int32_T *size;
  int32_T allocatedSize;
  int32_T numDimensions;
  boolean_T canFreeData;
};

#endif                                 /*struct_emxArray_real_T*/

#ifndef typedef_emxArray_real_T
#define typedef_emxArray_real_T

typedef struct emxArray_real_T emxArray_real_T;

#endif                                 /*typedef_emxArray_real_T*/

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

/* Function Declarations */
extern void SCL_decoder(real_T llr[8], int8_T L, int8_T K, int16_T frozen_bits[8],
  int16_T lambda_offset[4], int16_T llr_layer_vec[8], int16_T bit_layer_vec[8],
  real_T decoder_data[], int32_T decoder_size[2], emxArray_real_T *u);
extern void SCL_decoder_api(const mxArray * const prhs[7], const mxArray *plhs[2]);
extern void SCL_decoder_atexit(void);
extern void SCL_decoder_initialize(void);
extern void SCL_decoder_terminate(void);
extern void SCL_decoder_xil_terminate(void);

#endif

/*
 * File trailer for _coder_SCL_decoder_api.h
 *
 * [EOF]
 */
