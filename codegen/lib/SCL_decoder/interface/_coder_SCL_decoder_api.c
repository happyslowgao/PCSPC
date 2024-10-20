/*
 * File: _coder_SCL_decoder_api.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 27-Nov-2022 10:23:53
 */

/* Include Files */
#include "tmwtypes.h"
#include "_coder_SCL_decoder_api.h"
#include "_coder_SCL_decoder_mex.h"

/* Variable Definitions */
emlrtCTX emlrtRootTLSGlobal = NULL;
emlrtContext emlrtContextGlobal = { true,/* bFirstTime */
  false,                               /* bInitialized */
  131451U,                             /* fVersionInfo */
  NULL,                                /* fErrorFunction */
  "SCL_decoder",                       /* fFunctionName */
  NULL,                                /* fRTCallStack */
  false,                               /* bDebugMode */
  { 2045744189U, 2170104910U, 2743257031U, 4284093946U },/* fSigWrd */
  NULL                                 /* fSigMem */
};

/* Function Declarations */
static real_T (*b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId))[8];
static const mxArray *b_emlrt_marshallOut(const emxArray_real_T *u);
static int8_T c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *L, const
  char_T *identifier);
static int8_T d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId);
static int16_T (*e_emlrt_marshallIn(const emlrtStack *sp, const mxArray
  *frozen_bits, const char_T *identifier))[8];
static real_T (*emlrt_marshallIn(const emlrtStack *sp, const mxArray *llr, const
  char_T *identifier))[8];
static const mxArray *emlrt_marshallOut(const real_T u_data[], const int32_T
  u_size[2]);
static void emxFree_real_T(emxArray_real_T **pEmxArray);
static void emxInit_real_T(const emlrtStack *sp, emxArray_real_T **pEmxArray,
  int32_T numDimensions, boolean_T doPush);
static int16_T (*f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
  const emlrtMsgIdentifier *parentId))[8];
static int16_T (*g_emlrt_marshallIn(const emlrtStack *sp, const mxArray
  *lambda_offset, const char_T *identifier))[4];
static int16_T (*h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
  const emlrtMsgIdentifier *parentId))[4];
static real_T (*i_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[8];
static int8_T j_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId);
static int16_T (*k_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[8];
static int16_T (*l_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[4];

/* Function Definitions */

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : real_T (*)[8]
 */
static real_T (*b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId))[8]
{
  real_T (*y)[8];
  y = i_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}
/*
 * Arguments    : const emxArray_real_T *u
 * Return Type  : const mxArray *
 */
  static const mxArray *b_emlrt_marshallOut(const emxArray_real_T *u)
{
  const mxArray *y;
  const mxArray *m1;
  static const int32_T iv1[2] = { 0, 0 };

  y = NULL;
  m1 = emlrtCreateNumericArray(2, iv1, mxDOUBLE_CLASS, mxREAL);
  emlrtMxSetData((mxArray *)m1, (void *)&u->data[0]);
  emlrtSetDimensions((mxArray *)m1, u->size, 2);
  emlrtAssign(&y, m1);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *L
 *                const char_T *identifier
 * Return Type  : int8_T
 */
static int8_T c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *L, const
  char_T *identifier)
{
  int8_T y;
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = d_emlrt_marshallIn(sp, emlrtAlias(L), &thisId);
  emlrtDestroyArray(&L);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : int8_T
 */
static int8_T d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId)
{
  int8_T y;
  y = j_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *frozen_bits
 *                const char_T *identifier
 * Return Type  : int16_T (*)[8]
 */
static int16_T (*e_emlrt_marshallIn(const emlrtStack *sp, const mxArray
  *frozen_bits, const char_T *identifier))[8]
{
  int16_T (*y)[8];
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = f_emlrt_marshallIn(sp, emlrtAlias(frozen_bits), &thisId);
  emlrtDestroyArray(&frozen_bits);
  return y;
}
/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *llr
 *                const char_T *identifier
 * Return Type  : real_T (*)[8]
 */
  static real_T (*emlrt_marshallIn(const emlrtStack *sp, const mxArray *llr,
  const char_T *identifier))[8]
{
  real_T (*y)[8];
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = b_emlrt_marshallIn(sp, emlrtAlias(llr), &thisId);
  emlrtDestroyArray(&llr);
  return y;
}

/*
 * Arguments    : const real_T u_data[]
 *                const int32_T u_size[2]
 * Return Type  : const mxArray *
 */
static const mxArray *emlrt_marshallOut(const real_T u_data[], const int32_T
  u_size[2])
{
  const mxArray *y;
  const mxArray *m0;
  static const int32_T iv0[2] = { 0, 0 };

  y = NULL;
  m0 = emlrtCreateNumericArray(2, iv0, mxDOUBLE_CLASS, mxREAL);
  emlrtMxSetData((mxArray *)m0, (void *)&u_data[0]);
  emlrtSetDimensions((mxArray *)m0, u_size, 2);
  emlrtAssign(&y, m0);
  return y;
}

/*
 * Arguments    : emxArray_real_T **pEmxArray
 * Return Type  : void
 */
static void emxFree_real_T(emxArray_real_T **pEmxArray)
{
  if (*pEmxArray != (emxArray_real_T *)NULL) {
    if (((*pEmxArray)->data != (real_T *)NULL) && (*pEmxArray)->canFreeData) {
      emlrtFreeMex((void *)(*pEmxArray)->data);
    }

    emlrtFreeMex((void *)(*pEmxArray)->size);
    emlrtFreeMex((void *)*pEmxArray);
    *pEmxArray = (emxArray_real_T *)NULL;
  }
}

/*
 * Arguments    : const emlrtStack *sp
 *                emxArray_real_T **pEmxArray
 *                int32_T numDimensions
 *                boolean_T doPush
 * Return Type  : void
 */
static void emxInit_real_T(const emlrtStack *sp, emxArray_real_T **pEmxArray,
  int32_T numDimensions, boolean_T doPush)
{
  emxArray_real_T *emxArray;
  int32_T i;
  *pEmxArray = (emxArray_real_T *)emlrtMallocMex(sizeof(emxArray_real_T));
  if (doPush) {
    emlrtPushHeapReferenceStackR2012b(sp, (void *)pEmxArray, (void (*)(void *))
      emxFree_real_T);
  }

  emxArray = *pEmxArray;
  emxArray->data = (real_T *)NULL;
  emxArray->numDimensions = numDimensions;
  emxArray->size = (int32_T *)emlrtMallocMex((uint32_T)(sizeof(int32_T)
    * numDimensions));
  emxArray->allocatedSize = 0;
  emxArray->canFreeData = true;
  for (i = 0; i < numDimensions; i++) {
    emxArray->size[i] = 0;
  }
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : int16_T (*)[8]
 */
static int16_T (*f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
  const emlrtMsgIdentifier *parentId))[8]
{
  int16_T (*y)[8];
  y = k_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}
/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *lambda_offset
 *                const char_T *identifier
 * Return Type  : int16_T (*)[4]
 */
  static int16_T (*g_emlrt_marshallIn(const emlrtStack *sp, const mxArray
  *lambda_offset, const char_T *identifier))[4]
{
  int16_T (*y)[4];
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = h_emlrt_marshallIn(sp, emlrtAlias(lambda_offset), &thisId);
  emlrtDestroyArray(&lambda_offset);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : int16_T (*)[4]
 */
static int16_T (*h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
  const emlrtMsgIdentifier *parentId))[4]
{
  int16_T (*y)[4];
  y = l_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}
/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : real_T (*)[8]
 */
  static real_T (*i_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[8]
{
  real_T (*ret)[8];
  static const int32_T dims[2] = { 1, 8 };

  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 2U, dims);
  ret = (real_T (*)[8])emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : int8_T
 */
static int8_T j_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId)
{
  int8_T ret;
  static const int32_T dims = 0;
  emlrtCheckBuiltInR2012b(sp, msgId, src, "int8", false, 0U, &dims);
  ret = *(int8_T *)emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : int16_T (*)[8]
 */
static int16_T (*k_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[8]
{
  int16_T (*ret)[8];
  static const int32_T dims[2] = { 1, 8 };

  emlrtCheckBuiltInR2012b(sp, msgId, src, "int16", false, 2U, dims);
  ret = (int16_T (*)[8])emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}
/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : int16_T (*)[4]
 */
  static int16_T (*l_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[4]
{
  int16_T (*ret)[4];
  static const int32_T dims[2] = { 1, 4 };

  emlrtCheckBuiltInR2012b(sp, msgId, src, "int16", false, 2U, dims);
  ret = (int16_T (*)[4])emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

/*
 * Arguments    : const mxArray * const prhs[7]
 *                const mxArray *plhs[2]
 * Return Type  : void
 */
void SCL_decoder_api(const mxArray * const prhs[7], const mxArray *plhs[2])
{
  real_T (*decoder_data)[127];
  emxArray_real_T *u;
  real_T (*llr)[8];
  int8_T L;
  int8_T K;
  int16_T (*frozen_bits)[8];
  int16_T (*lambda_offset)[4];
  int16_T (*llr_layer_vec)[8];
  int16_T (*bit_layer_vec)[8];
  int32_T decoder_size[2];
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;
  decoder_data = (real_T (*)[127])mxMalloc(sizeof(real_T [127]));
  emlrtHeapReferenceStackEnterFcnR2012b(&st);
  emxInit_real_T(&st, &u, 2, true);

  /* Marshall function inputs */
  llr = emlrt_marshallIn(&st, emlrtAlias(prhs[0]), "llr");
  L = c_emlrt_marshallIn(&st, emlrtAliasP(prhs[1]), "L");
  K = c_emlrt_marshallIn(&st, emlrtAliasP(prhs[2]), "K");
  frozen_bits = e_emlrt_marshallIn(&st, emlrtAlias(prhs[3]), "frozen_bits");
  lambda_offset = g_emlrt_marshallIn(&st, emlrtAlias(prhs[4]), "lambda_offset");
  llr_layer_vec = e_emlrt_marshallIn(&st, emlrtAlias(prhs[5]), "llr_layer_vec");
  bit_layer_vec = e_emlrt_marshallIn(&st, emlrtAlias(prhs[6]), "bit_layer_vec");

  /* Invoke the target function */
  SCL_decoder(*llr, L, K, *frozen_bits, *lambda_offset, *llr_layer_vec,
              *bit_layer_vec, *decoder_data, decoder_size, u);

  /* Marshall function outputs */
  plhs[0] = emlrt_marshallOut(*decoder_data, decoder_size);
  plhs[1] = b_emlrt_marshallOut(u);
  u->canFreeData = false;
  emxFree_real_T(&u);
  emlrtHeapReferenceStackLeaveFcnR2012b(&st);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void SCL_decoder_atexit(void)
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtEnterRtStackR2012b(&st);
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  SCL_decoder_xil_terminate();
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void SCL_decoder_initialize(void)
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtClearAllocCountR2012b(&st, false, 0U, 0);
  emlrtEnterRtStackR2012b(&st);
  emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void SCL_decoder_terminate(void)
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/*
 * File trailer for _coder_SCL_decoder_api.c
 *
 * [EOF]
 */
