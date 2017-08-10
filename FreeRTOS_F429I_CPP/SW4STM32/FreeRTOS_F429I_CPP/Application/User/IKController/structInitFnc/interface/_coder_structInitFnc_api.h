/*
 * File: _coder_structInitFnc_api.h
 *
 * MATLAB Coder version            : 3.1
 * C/C++ source code generated on  : 06-Jun-2017 21:00:10
 */

#ifndef _CODER_STRUCTINITFNC_API_H
#define _CODER_STRUCTINITFNC_API_H

/* Include Files */
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include <stddef.h>
#include <stdlib.h>
#include "_coder_structInitFnc_api.h"

/* Type Definitions */
#ifndef typedef_Base_Struct
#define typedef_Base_Struct

typedef struct {
  real_T r;
  real_T alpha;
} Base_Struct;

#endif                                 /*typedef_Base_Struct*/

#ifndef typedef_Drive_Struct
#define typedef_Drive_Struct

typedef struct {
  real_T a;
  real_T s;
} Drive_Struct;

#endif                                 /*typedef_Drive_Struct*/

#ifndef typedef_Platform_Struct
#define typedef_Platform_Struct

typedef struct {
  real_T r;
  real_T alpha;
} Platform_Struct;

#endif                                 /*typedef_Platform_Struct*/

#ifndef typedef_Steward_Struct
#define typedef_Steward_Struct

typedef struct {
  Base_Struct base;
  Platform_Struct platform;
  Drive_Struct drive;
} Steward_Struct;

#endif                                 /*typedef_Steward_Struct*/

#ifndef typedef_struct1_T
#define typedef_struct1_T

typedef struct {
  real_T a;
  real_T s;
  real_T beta[6];
} struct1_T;

#endif                                 /*typedef_struct1_T*/

#ifndef typedef_struct0_T
#define typedef_struct0_T

typedef struct {
  real_T b[18];
  real_T p[18];
  real_T h0;
  struct1_T servo;
} struct0_T;

#endif                                 /*typedef_struct0_T*/

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

/* Function Declarations */
extern void structInitFnc(Steward_Struct *steward, struct0_T *ik);
extern void structInitFnc_api(const mxArray * const prhs[1], const mxArray *
  plhs[1]);
extern void structInitFnc_atexit(void);
extern void structInitFnc_initialize(void);
extern void structInitFnc_terminate(void);
extern void structInitFnc_xil_terminate(void);

#endif

/*
 * File trailer for _coder_structInitFnc_api.h
 *
 * [EOF]
 */
