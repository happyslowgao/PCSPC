/*
 * File: main.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 27-Nov-2022 10:23:53
 */

/*************************************************************************/
/* This automatically generated example C main file shows how to call    */
/* entry-point functions that MATLAB Coder generated. You must customize */
/* this file for your application. Do not modify this file directly.     */
/* Instead, make a copy of this file, modify it, and integrate it into   */
/* your development environment.                                         */
/*                                                                       */
/* This file initializes entry-point function arguments to a default     */
/* size and value before calling the entry-point functions. It does      */
/* not store or use any values returned from the entry-point functions.  */
/* If necessary, it does pre-allocate memory for returned values.        */
/* You can use this file as a starting point for a main function that    */
/* you can deploy in your application.                                   */
/*                                                                       */
/* After you copy the file, and before you deploy it, you must make the  */
/* following changes:                                                    */
/* * For variable-size function arguments, change the example sizes to   */
/* the sizes that your application requires.                             */
/* * Change the example values of function arguments to the values that  */
/* your application requires.                                            */
/* * If the entry-point functions return values, store these values or   */
/* otherwise use them as required by your application.                   */
/*                                                                       */
/*************************************************************************/
/* Include Files */
#include "rt_nonfinite.h"
#include "SCL_decoder.h"
#include "main.h"
#include "SCL_decoder_terminate.h"
#include "SCL_decoder_emxAPI.h"
#include "SCL_decoder_initialize.h"

/* Function Declarations */
static void argInit_1x4_int16_T(short result[4]);
static void argInit_1x8_int16_T(short result[8]);
static void argInit_1x8_real_T(double result[8]);
static short argInit_int16_T(void);
static signed char argInit_int8_T(void);
static double argInit_real_T(void);
static void main_SCL_decoder(void);

/* Function Definitions */

/*
 * Arguments    : short result[4]
 * Return Type  : void
 */
static void argInit_1x4_int16_T(short result[4])
{
  int idx1;

  /* Loop over the array to initialize each element. */
  for (idx1 = 0; idx1 < 4; idx1++) {
    /* Set the value of the array element.
       Change this value to the value that the application requires. */
    result[idx1] = argInit_int16_T();
  }
}

/*
 * Arguments    : short result[8]
 * Return Type  : void
 */
static void argInit_1x8_int16_T(short result[8])
{
  int idx1;

  /* Loop over the array to initialize each element. */
  for (idx1 = 0; idx1 < 8; idx1++) {
    /* Set the value of the array element.
       Change this value to the value that the application requires. */
    result[idx1] = argInit_int16_T();
  }
}

/*
 * Arguments    : double result[8]
 * Return Type  : void
 */
static void argInit_1x8_real_T(double result[8])
{
  int idx1;

  /* Loop over the array to initialize each element. */
  for (idx1 = 0; idx1 < 8; idx1++) {
    /* Set the value of the array element.
       Change this value to the value that the application requires. */
    result[idx1] = argInit_real_T();
  }
}

/*
 * Arguments    : void
 * Return Type  : short
 */
static short argInit_int16_T(void)
{
  return 0;
}

/*
 * Arguments    : void
 * Return Type  : signed char
 */
static signed char argInit_int8_T(void)
{
  return 0;
}

/*
 * Arguments    : void
 * Return Type  : double
 */
static double argInit_real_T(void)
{
  return 0.0;
}

/*
 * Arguments    : void
 * Return Type  : void
 */
static void main_SCL_decoder(void)
{
  emxArray_real_T *u;
  double dv0[8];
  short iv0[8];
  short iv1[4];
  short iv2[8];
  short iv3[8];
  double decoder_data[127];
  int decoder_size[2];
  emxInitArray_real_T(&u, 2);

  /* Initialize function 'SCL_decoder' input arguments. */
  /* Initialize function input argument 'llr'. */
  /* Initialize function input argument 'frozen_bits'. */
  /* Initialize function input argument 'lambda_offset'. */
  /* Initialize function input argument 'llr_layer_vec'. */
  /* Initialize function input argument 'bit_layer_vec'. */
  /* Call the entry-point 'SCL_decoder'. */
  argInit_1x8_real_T(dv0);
  argInit_1x8_int16_T(iv0);
  argInit_1x4_int16_T(iv1);
  argInit_1x8_int16_T(iv2);
  argInit_1x8_int16_T(iv3);
  SCL_decoder(dv0, argInit_int8_T(), argInit_int8_T(), iv0, iv1, iv2, iv3,
              decoder_data, decoder_size, u);
  emxDestroyArray_real_T(u);
}

/*
 * Arguments    : int argc
 *                const char * const argv[]
 * Return Type  : int
 */
int main(int argc, const char * const argv[])
{
  (void)argc;
  (void)argv;

  /* Initialize the application.
     You do not need to do this more than one time. */
  SCL_decoder_initialize();

  /* Invoke the entry-point functions.
     You can call entry-point functions multiple times. */
  main_SCL_decoder();

  /* Terminate the application.
     You do not need to do this more than one time. */
  SCL_decoder_terminate();
  return 0;
}

/*
 * File trailer for main.c
 *
 * [EOF]
 */
