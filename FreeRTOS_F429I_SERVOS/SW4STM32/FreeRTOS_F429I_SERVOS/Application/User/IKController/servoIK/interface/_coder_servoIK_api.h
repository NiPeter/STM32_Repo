/*
 * File: _coder_servoIK_api.h
 *
 * MATLAB Coder version            : 3.1
 * C/C++ source code generated on  : 06-Jun-2017 21:06:32
 */

#ifndef _CODER_SERVOIK_API_H
#define _CODER_SERVOIK_API_H

/* Include Files */
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include <stddef.h>
#include <stdlib.h>
#include "_coder_servoIK_api.h"

/* Type Definitions */
#ifndef typedef_Servo_Struct
#define typedef_Servo_Struct

typedef struct {
  real_T a;
  real_T s;
  real_T beta[6];
} Servo_Struct;

#endif                                 /*typedef_Servo_Struct*/

#ifndef typedef_IK_Struct
#define typedef_IK_Struct

typedef struct {
  real_T b[18];
  real_T p[18];
  real_T h0;
  Servo_Struct servo;
} IK_Struct;

#endif                                 /*typedef_IK_Struct*/

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

/* Function Declarations */
extern void servoIK(real_T Q[6], IK_Struct *ik, real_T alpha[6]);
extern void servoIK_api(const mxArray *prhs[2], const mxArray *plhs[1]);
extern void servoIK_atexit(void);
extern void servoIK_initialize(void);
extern void servoIK_terminate(void);
extern void servoIK_xil_terminate(void);

#endif

/*
 * File trailer for _coder_servoIK_api.h
 *
 * [EOF]
 */
