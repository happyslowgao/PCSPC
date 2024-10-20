/*
 * File: SCL_decoder.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 27-Nov-2022 10:23:53
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "SCL_decoder.h"
#include "sort1.h"
#include "sign.h"
#include "mod.h"
#include "sum.h"
#include "SCL_decoder_emxutil.h"

/* Function Declarations */
static double rt_roundd_snf(double u);

/* Function Definitions */

/*
 * Arguments    : double u
 * Return Type  : double
 */
static double rt_roundd_snf(double u)
{
  double y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

/*
 * Arguments    : const double llr[8]
 *                signed char L
 *                signed char K
 *                const short frozen_bits[8]
 *                const short lambda_offset[4]
 *                const short llr_layer_vec[8]
 *                const short bit_layer_vec[8]
 *                double decoder_data[]
 *                int decoder_size[2]
 *                emxArray_real_T *u
 * Return Type  : void
 */
void SCL_decoder(const double llr[8], signed char L, signed char K, const short
                 frozen_bits[8], const short lambda_offset[4], const short
                 llr_layer_vec[8], const short bit_layer_vec[8], double
                 decoder_data[], int decoder_size[2], emxArray_real_T *u)
{
  int loop_ub;
  double P_data[889];
  signed char middle;
  double C_data[889];
  int i0;
  int PM_size[1];
  double PM_data[127];
  int activepath_size[1];
  double activepath_data[127];
  double cnt_u;
  int phi;
  short layer;
  int iidx_data[127];
  double phi_mod_2;
  signed char l_index;
  short index_1;
  double PM_pair_data[254];
  short i1;
  short beta;
  double varargin_1;
  double d0;
  short index_2;
  int i2;
  short i_layer;
  int PM_sort_size[1];
  double varargin_2;
  int i3;
  double PM_sort_data[254];
  boolean_T compare_data[254];
  signed char kill_index_data[127];
  double d1;
  int kill_cnt;
  double b_varargin_1;
  signed char i4;
  signed char i5;
  int b_index;
  double P[7];
  double c_varargin_1;
  double d_varargin_1;
  double C[7];
  double u_data[127];
  double e_varargin_1;
  loop_ub = 7 * L;
  if (0 <= loop_ub - 1) {
    memset(&P_data[0], 0, (unsigned int)(loop_ub * (int)sizeof(double)));
  }

  /* 每条路径P是7个 */
  if (L > 63) {
    middle = MAX_int8_T;
  } else if (L <= -64) {
    middle = MIN_int8_T;
  } else {
    middle = (signed char)(L << 1);
  }

  loop_ub = 7 * middle;
  if (0 <= loop_ub - 1) {
    memset(&C_data[0], 0, (unsigned int)(loop_ub * (int)sizeof(double)));
  }

  /* 每条路径P是7个 */
  i0 = u->size[0] * u->size[1];
  u->size[0] = K;
  u->size[1] = L;
  emxEnsureCapacity_real_T(u, i0);
  loop_ub = K * L;
  for (i0 = 0; i0 < loop_ub; i0++) {
    u->data[i0] = 0.0;
  }

  /* 存放译码，就是非冻结比特 unfrozen bits that polar codes carry, including crc bits. */
  PM_size[0] = L;
  loop_ub = L;
  if (0 <= loop_ub - 1) {
    memset(&PM_data[0], 0, (unsigned int)(loop_ub * (int)sizeof(double)));
  }

  /* Path metrics */
  activepath_size[0] = L;
  loop_ub = L;
  if (0 <= loop_ub - 1) {
    memset(&activepath_data[0], 0, (unsigned int)(loop_ub * (int)sizeof(double)));
  }

  /* Indicate if the path is active. '1'→active; '0' otherwise. */
  cnt_u = 1.0;

  /* information bit counter  */
  /* initialize */
  activepath_data[0] = 1.0;
  for (phi = 0; phi < 8; phi++) {
    layer = llr_layer_vec[phi];
    phi_mod_2 = b_mod(phi);
    for (l_index = 1; l_index <= L; l_index++) {
      if (!(activepath_data[l_index - 1] == 0.0)) {
        switch (phi) {
         case 0:
          /* Decoding bits u_0 and u_N/2 needs channel LLR, so the decoding of them is separated from other bits.  */
          index_1 = lambda_offset[2];
          i0 = lambda_offset[2] - 1;
          if (i0 < -32768) {
            i0 = -32768;
          }

          i1 = (short)i0;
          for (beta = 0; beta <= i1; beta++) {
            varargin_1 = fabs(llr[beta]);
            i0 = beta + index_1;
            if (i0 > 32767) {
              i0 = 32767;
            }

            i0++;
            if (i0 > 32767) {
              i0 = 32767;
            }

            varargin_2 = fabs(llr[i0 - 1]);
            d0 = llr[beta];
            b_sign(&d0);
            i0 = beta + index_1;
            if (i0 > 32767) {
              i0 = 32767;
            }

            i0++;
            if (i0 > 32767) {
              i0 = 32767;
            }

            d1 = llr[i0 - 1];
            b_sign(&d1);
            i0 = beta + index_1;
            if (i0 > 32767) {
              i0 = 32767;
            }

            if ((varargin_1 < varargin_2) || rtIsNaN(varargin_2)) {
              b_varargin_1 = varargin_1;
            } else {
              b_varargin_1 = varargin_2;
            }

            P_data[(i0 + 7 * (l_index - 1)) - 1] = d0 * d1 * b_varargin_1;
          }

          for (loop_ub = 0; loop_ub < 2; loop_ub++) {
            index_1 = lambda_offset[1 - loop_ub];
            index_2 = lambda_offset[2 - loop_ub];
            i0 = lambda_offset[1 - loop_ub] - 1;
            if (i0 < -32768) {
              i0 = -32768;
            }

            i1 = (short)i0;
            for (beta = 0; beta <= i1; beta++) {
              i0 = beta + index_2;
              if (i0 > 32767) {
                i0 = 32767;
              }

              varargin_1 = fabs(P_data[(i0 + 7 * (l_index - 1)) - 1]);
              i0 = beta + index_1;
              if (i0 > 32767) {
                i0 = 32767;
              }

              i0 += index_2;
              if (i0 > 32767) {
                i0 = 32767;
              } else {
                if (i0 < -32768) {
                  i0 = -32768;
                }
              }

              varargin_2 = fabs(P_data[(i0 + 7 * (l_index - 1)) - 1]);
              i0 = beta + index_2;
              if (i0 > 32767) {
                i0 = 32767;
              }

              d0 = P_data[(i0 + 7 * (l_index - 1)) - 1];
              b_sign(&d0);
              i0 = beta + index_1;
              if (i0 > 32767) {
                i0 = 32767;
              }

              i0 += index_2;
              if (i0 > 32767) {
                i0 = 32767;
              } else {
                if (i0 < -32768) {
                  i0 = -32768;
                }
              }

              d1 = P_data[(i0 + 7 * (l_index - 1)) - 1];
              b_sign(&d1);
              i0 = beta + index_1;
              if (i0 > 32767) {
                i0 = 32767;
              }

              if ((varargin_1 < varargin_2) || rtIsNaN(varargin_2)) {
                d_varargin_1 = varargin_1;
              } else {
                d_varargin_1 = varargin_2;
              }

              P_data[(i0 + 7 * (l_index - 1)) - 1] = d0 * d1 * d_varargin_1;
            }
          }
          break;

         case 4:
          index_1 = lambda_offset[2];
          i0 = lambda_offset[2] - 1;
          if (i0 < -32768) {
            i0 = -32768;
          }

          i1 = (short)i0;
          for (beta = 0; beta <= i1; beta++) {
            i0 = beta + index_1;
            if (i0 > 32767) {
              i0 = 32767;
            }

            i2 = beta + index_1;
            if (i2 > 32767) {
              i2 = 32767;
            }

            if (l_index > 63) {
              middle = MAX_int8_T;
            } else if (l_index <= -64) {
              middle = MIN_int8_T;
            } else {
              middle = (signed char)(l_index << 1);
            }

            i3 = (beta + index_1) + 1;
            if (i3 > 32767) {
              i3 = 32767;
            }

            P_data[(i0 + 7 * (l_index - 1)) - 1] = (1.0 - 2.0 * C_data[(i2 + 7 *
              (middle - 2)) - 1]) * llr[beta] + llr[i3 - 1];
          }

          for (loop_ub = 0; loop_ub < 2; loop_ub++) {
            index_1 = lambda_offset[1 - loop_ub];
            index_2 = lambda_offset[2 - loop_ub];
            i0 = lambda_offset[1 - loop_ub] - 1;
            if (i0 < -32768) {
              i0 = -32768;
            }

            i1 = (short)i0;
            for (beta = 0; beta <= i1; beta++) {
              i0 = beta + index_2;
              if (i0 > 32767) {
                i0 = 32767;
              }

              varargin_1 = fabs(P_data[(i0 + 7 * (l_index - 1)) - 1]);
              i0 = beta + index_1;
              if (i0 > 32767) {
                i0 = 32767;
              }

              i0 += index_2;
              if (i0 > 32767) {
                i0 = 32767;
              } else {
                if (i0 < -32768) {
                  i0 = -32768;
                }
              }

              varargin_2 = fabs(P_data[(i0 + 7 * (l_index - 1)) - 1]);
              i0 = beta + index_2;
              if (i0 > 32767) {
                i0 = 32767;
              }

              d0 = P_data[(i0 + 7 * (l_index - 1)) - 1];
              b_sign(&d0);
              i0 = beta + index_1;
              if (i0 > 32767) {
                i0 = 32767;
              }

              i0 += index_2;
              if (i0 > 32767) {
                i0 = 32767;
              } else {
                if (i0 < -32768) {
                  i0 = -32768;
                }
              }

              d1 = P_data[(i0 + 7 * (l_index - 1)) - 1];
              b_sign(&d1);
              i0 = beta + index_1;
              if (i0 > 32767) {
                i0 = 32767;
              }

              if ((varargin_1 < varargin_2) || rtIsNaN(varargin_2)) {
                c_varargin_1 = varargin_1;
              } else {
                c_varargin_1 = varargin_2;
              }

              P_data[(i0 + 7 * (l_index - 1)) - 1] = d0 * d1 * c_varargin_1;
            }
          }
          break;

         default:
          i0 = layer + 1;
          if (i0 > 32767) {
            i0 = 32767;
          }

          index_1 = lambda_offset[i0 - 1];
          i0 = layer + 2;
          if (i0 > 32767) {
            i0 = 32767;
          }

          index_2 = lambda_offset[i0 - 1];
          i0 = layer + 1;
          if (i0 > 32767) {
            i0 = 32767;
          }

          i0 = lambda_offset[i0 - 1] - 1;
          if (i0 < -32768) {
            i0 = -32768;
          }

          i1 = (short)i0;
          for (beta = 0; beta <= i1; beta++) {
            i0 = beta + index_1;
            if (i0 > 32767) {
              i0 = 32767;
            }

            i2 = beta + index_1;
            if (i2 > 32767) {
              i2 = 32767;
            }

            if (l_index > 63) {
              middle = MAX_int8_T;
            } else if (l_index <= -64) {
              middle = MIN_int8_T;
            } else {
              middle = (signed char)(l_index << 1);
            }

            i3 = beta + index_2;
            if (i3 > 32767) {
              i3 = 32767;
            }

            loop_ub = beta + index_1;
            if (loop_ub > 32767) {
              loop_ub = 32767;
            }

            loop_ub += index_2;
            if (loop_ub > 32767) {
              loop_ub = 32767;
            } else {
              if (loop_ub < -32768) {
                loop_ub = -32768;
              }
            }

            P_data[(i0 + 7 * (l_index - 1)) - 1] = (1.0 - 2.0 * C_data[(i2 + 7 *
              (middle - 2)) - 1]) * P_data[(i3 + 7 * (l_index - 1)) - 1] +
              P_data[(loop_ub + 7 * (l_index - 1)) - 1];
          }

          i0 = layer - 1;
          if (i0 < -32768) {
            i0 = -32768;
          }

          for (i_layer = (short)i0; i_layer > -1; i_layer--) {
            index_1 = lambda_offset[i_layer];
            i0 = i_layer + 2;
            if (i0 > 32767) {
              i0 = 32767;
            }

            index_2 = lambda_offset[i0 - 1];
            i0 = lambda_offset[i_layer] - 1;
            if (i0 < -32768) {
              i0 = -32768;
            }

            i1 = (short)i0;
            for (beta = 0; beta <= i1; beta++) {
              i0 = beta + index_2;
              if (i0 > 32767) {
                i0 = 32767;
              }

              varargin_1 = fabs(P_data[(i0 + 7 * (l_index - 1)) - 1]);
              i0 = beta + index_1;
              if (i0 > 32767) {
                i0 = 32767;
              }

              i0 += index_2;
              if (i0 > 32767) {
                i0 = 32767;
              } else {
                if (i0 < -32768) {
                  i0 = -32768;
                }
              }

              varargin_2 = fabs(P_data[(i0 + 7 * (l_index - 1)) - 1]);
              i0 = beta + index_2;
              if (i0 > 32767) {
                i0 = 32767;
              }

              d0 = P_data[(i0 + 7 * (l_index - 1)) - 1];
              b_sign(&d0);
              i0 = beta + index_1;
              if (i0 > 32767) {
                i0 = 32767;
              }

              i0 += index_2;
              if (i0 > 32767) {
                i0 = 32767;
              } else {
                if (i0 < -32768) {
                  i0 = -32768;
                }
              }

              d1 = P_data[(i0 + 7 * (l_index - 1)) - 1];
              b_sign(&d1);
              i0 = beta + index_1;
              if (i0 > 32767) {
                i0 = 32767;
              }

              if ((varargin_1 < varargin_2) || rtIsNaN(varargin_2)) {
                e_varargin_1 = varargin_1;
              } else {
                e_varargin_1 = varargin_2;
              }

              P_data[(i0 + 7 * (l_index - 1)) - 1] = d0 * d1 * e_varargin_1;
            }
          }
          break;
        }
      }
    }

    if (frozen_bits[phi] == 0) {
      /* if now we decode an unfrozen bit */
      loop_ub = L << 1;
      for (i0 = 0; i0 < loop_ub; i0++) {
        PM_pair_data[i0] = 1.7976931348623157E+308;
      }

      for (l_index = 1; l_index <= L; l_index++) {
        if (!(activepath_data[l_index - 1] == 0.0)) {
          if (P_data[7 * (l_index - 1)] >= 0.0) {
            PM_pair_data[(l_index - 1) << 1] = PM_data[l_index - 1];
            PM_pair_data[1 + ((l_index - 1) << 1)] = PM_data[l_index - 1] +
              P_data[7 * (l_index - 1)];
          } else {
            PM_pair_data[(l_index - 1) << 1] = PM_data[l_index - 1] - P_data[7 *
              (l_index - 1)];
            PM_pair_data[1 + ((l_index - 1) << 1)] = PM_data[l_index - 1];
          }
        }
      }

      varargin_1 = 2.0 * sum(activepath_data, activepath_size);
      d0 = rt_roundd_snf(varargin_1);
      if (d0 < 128.0) {
        if (d0 >= -128.0) {
          middle = (signed char)d0;
        } else {
          middle = MIN_int8_T;
        }
      } else if (d0 >= 128.0) {
        middle = MAX_int8_T;
      } else {
        middle = 0;
      }

      if (varargin_1 < L) {
      } else {
        middle = L;
      }

      PM_sort_size[0] = L << 1;
      loop_ub = L << 1;
      if (0 <= loop_ub - 1) {
        memcpy(&PM_sort_data[0], &PM_pair_data[0], (unsigned int)(loop_ub * (int)
                sizeof(double)));
      }

      sort(PM_sort_data, PM_sort_size);
      loop_ub = L << 1;
      for (i0 = 0; i0 < loop_ub; i0++) {
        compare_data[i0] = (PM_pair_data[i0] <= PM_sort_data[middle - 1]);
      }

      loop_ub = L;
      if (0 <= loop_ub - 1) {
        memset(&kill_index_data[0], 0, (unsigned int)(loop_ub * (int)sizeof
                (signed char)));
      }

      /* to record the index of the path that is killed */
      kill_cnt = -1;

      /* the total number of killed path */
      /* the above two variables consist of a stack */
      for (middle = 1; middle <= L; middle++) {
        if ((!compare_data[(middle - 1) << 1]) && (!compare_data[1 + ((middle -
               1) << 1)])) {
          /* which indicates that this path should be killed */
          activepath_data[middle - 1] = 0.0;
          kill_cnt++;

          /* push stack */
          kill_index_data[kill_cnt] = middle;
        }
      }

      for (l_index = 1; l_index <= L; l_index++) {
        if (!(activepath_data[l_index - 1] == 0.0)) {
          switch ((compare_data[(l_index - 1) << 1] << 1) + compare_data[1 +
                  ((l_index - 1) << 1)]) {
           case 1:
            /* path_state can equal to 0, but in this case we do no operation. */
            u->data[((int)cnt_u + u->size[0] * (l_index - 1)) - 1] = 1.0;
            if (l_index > 63) {
              middle = MAX_int8_T;
            } else {
              middle = (signed char)(l_index << 1);
            }

            d0 = rt_roundd_snf(((double)middle - 1.0) + phi_mod_2);
            if (d0 < 128.0) {
              if (d0 >= -128.0) {
                middle = (signed char)d0;
              } else {
                middle = MIN_int8_T;
              }
            } else if (d0 >= 128.0) {
              middle = MAX_int8_T;
            } else {
              middle = 0;
            }

            C_data[7 * (middle - 1)] = 1.0;
            PM_data[l_index - 1] = PM_pair_data[1 + ((l_index - 1) << 1)];
            break;

           case 2:
            u->data[((int)cnt_u + u->size[0] * (l_index - 1)) - 1] = 0.0;
            if (l_index > 63) {
              middle = MAX_int8_T;
            } else {
              middle = (signed char)(l_index << 1);
            }

            d0 = rt_roundd_snf(((double)middle - 1.0) + phi_mod_2);
            if (d0 < 128.0) {
              if (d0 >= -128.0) {
                middle = (signed char)d0;
              } else {
                middle = MIN_int8_T;
              }
            } else if (d0 >= 128.0) {
              middle = MAX_int8_T;
            } else {
              middle = 0;
            }

            C_data[7 * (middle - 1)] = 0.0;
            PM_data[l_index - 1] = PM_pair_data[(l_index - 1) << 1];
            break;

           case 3:
            b_index = kill_index_data[kill_cnt] - 1;
            kill_cnt--;

            /* pop stack */
            activepath_data[b_index] = 1.0;
            for (i0 = 0; i0 < 7; i0++) {
              P[i0] = P_data[i0 + 7 * (l_index - 1)];
            }

            if (l_index > 63) {
              middle = MAX_int8_T;
            } else {
              middle = (signed char)(l_index << 1);
            }

            i0 = middle;
            i2 = (b_index + 1) << 1;
            for (i3 = 0; i3 < 7; i3++) {
              P_data[i3 + 7 * b_index] = P[i3];
              C[i3] = C_data[i3 + 7 * (i0 - 2)];
            }

            for (i0 = 0; i0 < 7; i0++) {
              C_data[i0 + 7 * (i2 - 2)] = C[i0];
            }

            if (l_index > 63) {
              middle = MAX_int8_T;
            } else {
              middle = (signed char)(l_index << 1);
            }

            i0 = middle;
            i2 = (b_index + 1) << 1;
            for (i3 = 0; i3 < 7; i3++) {
              C[i3] = C_data[i3 + 7 * (i0 - 1)];
            }

            for (i0 = 0; i0 < 7; i0++) {
              C_data[i0 + 7 * (i2 - 1)] = C[i0];
            }

            loop_ub = u->size[0];
            for (i0 = 0; i0 < loop_ub; i0++) {
              u_data[i0] = u->data[i0 + u->size[0] * (l_index - 1)];
            }

            for (i0 = 0; i0 < loop_ub; i0++) {
              u->data[i0 + u->size[0] * b_index] = u_data[i0];
            }

            u->data[((int)cnt_u + u->size[0] * (l_index - 1)) - 1] = 0.0;
            u->data[((int)cnt_u + u->size[0] * b_index) - 1] = 1.0;
            if (l_index > 63) {
              middle = MAX_int8_T;
            } else {
              middle = (signed char)(l_index << 1);
            }

            d0 = rt_roundd_snf(((double)middle - 1.0) + phi_mod_2);
            if (d0 < 128.0) {
              if (d0 >= -128.0) {
                middle = (signed char)d0;
              } else {
                middle = MIN_int8_T;
              }
            } else if (d0 >= 128.0) {
              middle = MAX_int8_T;
            } else {
              middle = 0;
            }

            C_data[7 * (middle - 1)] = 0.0;
            C_data[7 * ((int)((2.0 * ((double)b_index + 1.0) - 1.0) + phi_mod_2)
                        - 1)] = 1.0;
            PM_data[l_index - 1] = PM_pair_data[(l_index - 1) << 1];
            PM_data[b_index] = PM_pair_data[1 + ((l_index - 1) << 1)];
            break;
          }
        }
      }

      cnt_u++;
    } else {
      /* frozen bit operation */
      for (l_index = 1; l_index <= L; l_index++) {
        if (!(activepath_data[l_index - 1] == 0.0)) {
          if (P_data[7 * (l_index - 1)] < 0.0) {
            PM_data[l_index - 1] -= P_data[7 * (l_index - 1)];
          }

          if (phi_mod_2 == 0.0) {
            if (l_index > 63) {
              middle = MAX_int8_T;
            } else {
              middle = (signed char)(l_index << 1);
            }

            C_data[7 * (middle - 2)] = 0.0;
          } else {
            if (l_index > 63) {
              middle = MAX_int8_T;
            } else {
              middle = (signed char)(l_index << 1);
            }

            C_data[7 * (middle - 1)] = 0.0;
          }
        }
      }
    }

    for (l_index = 1; l_index <= L; l_index++) {
      /* partial-sum return */
      if ((!(activepath_data[l_index - 1] == 0.0)) && (phi_mod_2 == 1.0) && (phi
           != 7)) {
        i0 = bit_layer_vec[phi] - 1;
        if (i0 < -32768) {
          i0 = -32768;
        }

        i1 = (short)i0;
        for (i_layer = 0; i_layer <= i1; i_layer++) {
          layer = lambda_offset[i_layer];
          if (layer > 16383) {
            layer = MAX_int16_T;
          } else if (layer <= -16384) {
            layer = MIN_int16_T;
          } else {
            layer <<= 1;
          }

          i0 = layer - 1;
          if (i0 < -32768) {
            i0 = -32768;
          }

          layer = (short)i0;
          for (beta = lambda_offset[i_layer]; beta <= layer; beta++) {
            i0 = beta + lambda_offset[i_layer];
            if (i0 > 32767) {
              i0 = 32767;
            } else {
              if (i0 < -32768) {
                i0 = -32768;
              }
            }

            if (l_index > 63) {
              middle = MAX_int8_T;
              i4 = MAX_int8_T;
              i5 = MAX_int8_T;
            } else {
              middle = (signed char)(l_index << 1);
              i4 = (signed char)(l_index << 1);
              i5 = (signed char)(l_index << 1);
            }

            C_data[(i0 + 7 * (middle - 1)) - 1] = b_mod(C_data[(beta + 7 * (i4 -
              2)) - 1] + C_data[(beta + 7 * (i5 - 1)) - 1]);
            i0 = i_layer + 2;
            if (i0 > 32767) {
              i0 = 32767;
            }

            i0 = beta + lambda_offset[i0 - 1];
            if (i0 > 32767) {
              i0 = 32767;
            } else {
              if (i0 < -32768) {
                i0 = -32768;
              }
            }

            if (l_index > 63) {
              middle = MAX_int8_T;
              i4 = MAX_int8_T;
            } else {
              middle = (signed char)(l_index << 1);
              i4 = (signed char)(l_index << 1);
            }

            C_data[(i0 + 7 * (middle - 1)) - 1] = C_data[(beta + 7 * (i4 - 1)) -
              1];
          }
        }

        i0 = bit_layer_vec[phi] + 1;
        if (i0 > 32767) {
          i0 = 32767;
        }

        i1 = lambda_offset[i0 - 1];
        if (i1 > 16383) {
          i1 = MAX_int16_T;
        } else if (i1 <= -16384) {
          i1 = MIN_int16_T;
        } else {
          i1 <<= 1;
        }

        i0 = i1 - 1;
        if (i0 < -32768) {
          i0 = -32768;
        }

        i1 = (short)i0;
        i0 = bit_layer_vec[phi] + 1;
        if (i0 > 32767) {
          i0 = 32767;
        }

        for (beta = lambda_offset[i0 - 1]; beta <= i1; beta++) {
          i0 = bit_layer_vec[phi] + 1;
          if (i0 > 32767) {
            i0 = 32767;
          }

          i0 = beta + lambda_offset[i0 - 1];
          if (i0 > 32767) {
            i0 = 32767;
          } else {
            if (i0 < -32768) {
              i0 = -32768;
            }
          }

          if (l_index > 63) {
            middle = MAX_int8_T;
            i4 = MAX_int8_T;
            i5 = MAX_int8_T;
          } else {
            middle = (signed char)(l_index << 1);
            i4 = (signed char)(l_index << 1);
            i5 = (signed char)(l_index << 1);
          }

          C_data[(i0 + 7 * (middle - 2)) - 1] = b_mod(C_data[(beta + 7 * (i4 - 2))
            - 1] + C_data[(beta + 7 * (i5 - 1)) - 1]);
          i0 = bit_layer_vec[phi] + 2;
          if (i0 > 32767) {
            i0 = 32767;
          }

          i0 = beta + lambda_offset[i0 - 1];
          if (i0 > 32767) {
            i0 = 32767;
          } else {
            if (i0 < -32768) {
              i0 = -32768;
            }
          }

          if (l_index > 63) {
            middle = MAX_int8_T;
            i4 = MAX_int8_T;
          } else {
            middle = (signed char)(l_index << 1);
            i4 = (signed char)(l_index << 1);
          }

          C_data[(i0 + 7 * (middle - 2)) - 1] = C_data[(beta + 7 * (i4 - 1)) - 1];
        }
      }
    }
  }

  /* path selection. */
  b_sort(PM_data, PM_size, iidx_data, activepath_size);
  loop_ub = activepath_size[0];
  for (i0 = 0; i0 < loop_ub; i0++) {
    PM_data[i0] = iidx_data[i0];
  }

  /* 对PM进行排序 */
  /* 取排序最小的那个在原来PM数组中占第几列 */
  loop_ub = u->size[0];
  decoder_size[0] = 1;
  decoder_size[1] = loop_ub;
  for (i0 = 0; i0 < loop_ub; i0++) {
    decoder_data[decoder_size[0] * i0] = u->data[i0 + u->size[0] * ((int)
      PM_data[0] - 1)];
  }
}

/*
 * File trailer for SCL_decoder.c
 *
 * [EOF]
 */
