/*
 * File: _coder_structInitFnc_api.c
 *
 * MATLAB Coder version            : 3.1
 * C/C++ source code generated on  : 06-Jun-2017 21:00:10
 */

/* Include Files */
#include "tmwtypes.h"
#include "_coder_structInitFnc_api.h"
#include "_coder_structInitFnc_mex.h"

/* Variable Definitions */
emlrtCTX emlrtRootTLSGlobal = NULL;
emlrtContext emlrtContextGlobal = { true, false, 131434U, NULL, "structInitFnc",
  NULL, false, { 2045744189U, 2170104910U, 2743257031U, 4284093946U }, NULL };

/* Function Declarations */
static Steward_Struct b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
  const emlrtMsgIdentifier *parentId);
static Base_Struct c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
  const emlrtMsgIdentifier *parentId);
static real_T d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId);
static Platform_Struct e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
  const emlrtMsgIdentifier *parentId);
static Steward_Struct emlrt_marshallIn(const emlrtStack *sp, const mxArray
  *steward, const char_T *identifier);
static const mxArray *emlrt_marshallOut(const struct0_T *u);
static void f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId);
static Drive_Struct g_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
  const emlrtMsgIdentifier *parentId);
static real_T h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId);
static void i_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId);

/* Function Definitions */

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : Steward_Struct
 */
static Steward_Struct b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
  const emlrtMsgIdentifier *parentId)
{
  Steward_Struct y;
  emlrtMsgIdentifier thisId;
  static const char * fieldNames[3] = { "base", "platform", "drive" };

  static const int32_T dims = 0;
  thisId.fParent = parentId;
  thisId.bParentIsCell = false;
  emlrtCheckStructR2012b(sp, parentId, u, 3, fieldNames, 0U, &dims);
  thisId.fIdentifier = "base";
  y.base = c_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2013a(sp, u, 0,
    "base")), &thisId);
  thisId.fIdentifier = "platform";
  y.platform = e_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2013a(sp, u, 0,
    "platform")), &thisId);
  thisId.fIdentifier = "drive";
  y.drive = g_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2013a(sp, u, 0,
    "drive")), &thisId);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : Base_Struct
 */
static Base_Struct c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
  const emlrtMsgIdentifier *parentId)
{
  Base_Struct y;
  emlrtMsgIdentifier thisId;
  static const char * fieldNames[2] = { "r", "alpha" };

  static const int32_T dims = 0;
  thisId.fParent = parentId;
  thisId.bParentIsCell = false;
  emlrtCheckStructR2012b(sp, parentId, u, 2, fieldNames, 0U, &dims);
  thisId.fIdentifier = "r";
  y.r = d_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2013a(sp, u, 0, "r")),
    &thisId);
  thisId.fIdentifier = "alpha";
  y.alpha = d_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2013a(sp, u, 0,
    "alpha")), &thisId);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : real_T
 */
static real_T d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId)
{
  real_T y;
  y = h_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : Platform_Struct
 */
static Platform_Struct e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
  const emlrtMsgIdentifier *parentId)
{
  Platform_Struct y;
  emlrtMsgIdentifier thisId;
  static const char * fieldNames[3] = { "r", "alpha", "h" };

  static const int32_T dims = 0;
  thisId.fParent = parentId;
  thisId.bParentIsCell = false;
  emlrtCheckStructR2012b(sp, parentId, u, 3, fieldNames, 0U, &dims);
  thisId.fIdentifier = "r";
  y.r = d_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2013a(sp, u, 0, "r")),
    &thisId);
  thisId.fIdentifier = "alpha";
  y.alpha = d_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2013a(sp, u, 0,
    "alpha")), &thisId);
  thisId.fIdentifier = "h";
  f_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2013a(sp, u, 0, "h")), &thisId);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *steward
 *                const char_T *identifier
 * Return Type  : Steward_Struct
 */
static Steward_Struct emlrt_marshallIn(const emlrtStack *sp, const mxArray
  *steward, const char_T *identifier)
{
  Steward_Struct y;
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = b_emlrt_marshallIn(sp, emlrtAlias(steward), &thisId);
  emlrtDestroyArray(&steward);
  return y;
}

/*
 * Arguments    : const struct0_T *u
 * Return Type  : const mxArray *
 */
static const mxArray *emlrt_marshallOut(const struct0_T *u)
{
  const mxArray *y;
  const mxArray *b_y;
  const mxArray *m0;
  static const int32_T iv0[2] = { 6, 3 };

  real_T *pData;
  int32_T i;
  const mxArray *c_y;
  static const int32_T iv1[2] = { 6, 3 };

  const mxArray *d_y;
  const mxArray *e_y;
  const mxArray *f_y;
  const mxArray *g_y;
  const mxArray *h_y;
  static const int32_T iv2[2] = { 1, 6 };

  y = NULL;
  emlrtAssign(&y, emlrtCreateStructMatrix(1, 1, 0, NULL));
  b_y = NULL;
  m0 = emlrtCreateNumericArray(2, iv0, mxDOUBLE_CLASS, mxREAL);
  pData = (real_T *)mxGetPr(m0);
  for (i = 0; i < 18; i++) {
    pData[i] = u->b[i];
  }

  emlrtAssign(&b_y, m0);
  emlrtAddField(y, b_y, "b", 0);
  c_y = NULL;
  m0 = emlrtCreateNumericArray(2, iv1, mxDOUBLE_CLASS, mxREAL);
  pData = (real_T *)mxGetPr(m0);
  for (i = 0; i < 18; i++) {
    pData[i] = u->p[i];
  }

  emlrtAssign(&c_y, m0);
  emlrtAddField(y, c_y, "p", 0);
  d_y = NULL;
  m0 = emlrtCreateDoubleScalar(u->h0);
  emlrtAssign(&d_y, m0);
  emlrtAddField(y, d_y, "h0", 0);
  e_y = NULL;
  emlrtAssign(&e_y, emlrtCreateStructMatrix(1, 1, 0, NULL));
  f_y = NULL;
  m0 = emlrtCreateDoubleScalar(u->servo.a);
  emlrtAssign(&f_y, m0);
  emlrtAddField(e_y, f_y, "a", 0);
  g_y = NULL;
  m0 = emlrtCreateDoubleScalar(u->servo.s);
  emlrtAssign(&g_y, m0);
  emlrtAddField(e_y, g_y, "s", 0);
  h_y = NULL;
  m0 = emlrtCreateNumericArray(2, iv2, mxDOUBLE_CLASS, mxREAL);
  pData = (real_T *)mxGetPr(m0);
  for (i = 0; i < 6; i++) {
    pData[i] = u->servo.beta[i];
  }

  emlrtAssign(&h_y, m0);
  emlrtAddField(e_y, h_y, "beta", 0);
  emlrtAddField(y, e_y, "servo", 0);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : void
 */
static void f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId)
{
  i_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : Drive_Struct
 */
static Drive_Struct g_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
  const emlrtMsgIdentifier *parentId)
{
  Drive_Struct y;
  emlrtMsgIdentifier thisId;
  static const char * fieldNames[3] = { "a", "s", "alpha0" };

  static const int32_T dims = 0;
  thisId.fParent = parentId;
  thisId.bParentIsCell = false;
  emlrtCheckStructR2012b(sp, parentId, u, 3, fieldNames, 0U, &dims);
  thisId.fIdentifier = "a";
  y.a = d_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2013a(sp, u, 0, "a")),
    &thisId);
  thisId.fIdentifier = "s";
  y.s = d_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2013a(sp, u, 0, "s")),
    &thisId);
  thisId.fIdentifier = "alpha0";
  f_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2013a(sp, u, 0, "alpha0")),
                     &thisId);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : real_T
 */
static real_T h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId)
{
  real_T ret;
  static const int32_T dims = 0;
  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 0U, &dims);
  ret = *(real_T *)mxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : void
 */
static void i_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId)
{
  static const int32_T dims[2] = { 0, 0 };

  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 2U, dims);
  emlrtDestroyArray(&src);
}

/*
 * Arguments    : const mxArray * const prhs[1]
 *                const mxArray *plhs[1]
 * Return Type  : void
 */
void structInitFnc_api(const mxArray * const prhs[1], const mxArray *plhs[1])
{
  Steward_Struct steward;
  struct0_T ik;
  emlrtStack st = { NULL, NULL, NULL };

  st.tls = emlrtRootTLSGlobal;

  /* Marshall function inputs */
  steward = emlrt_marshallIn(&st, emlrtAliasP(prhs[0]), "steward");

  /* Invoke the target function */
  structInitFnc(&steward, &ik);

  /* Marshall function outputs */
  plhs[0] = emlrt_marshallOut(&ik);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void structInitFnc_atexit(void)
{
  emlrtStack st = { NULL, NULL, NULL };

  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtEnterRtStackR2012b(&st);
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  structInitFnc_xil_terminate();
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void structInitFnc_initialize(void)
{
  emlrtStack st = { NULL, NULL, NULL };

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
void structInitFnc_terminate(void)
{
  emlrtStack st = { NULL, NULL, NULL };

  st.tls = emlrtRootTLSGlobal;
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/*
 * File trailer for _coder_structInitFnc_api.c
 *
 * [EOF]
 */
