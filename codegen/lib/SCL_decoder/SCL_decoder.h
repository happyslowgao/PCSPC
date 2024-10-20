/*
 * File: SCL_decoder.h
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 27-Nov-2022 10:23:53
 */

#ifndef SCL_DECODER_H
#define SCL_DECODER_H

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "SCL_decoder_types.h"

/* Function Declarations */
extern void SCL_decoder(const double llr[8], signed char L, signed char K, const
  short frozen_bits[8], const short lambda_offset[4], const short llr_layer_vec
  [8], const short bit_layer_vec[8], double decoder_data[], int decoder_size[2],
  emxArray_real_T *u);

#endif

/*
 * File trailer for SCL_decoder.h
 *
 * [EOF]
 */
