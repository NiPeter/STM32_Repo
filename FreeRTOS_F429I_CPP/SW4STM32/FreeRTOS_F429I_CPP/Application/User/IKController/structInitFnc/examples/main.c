/*
 * File: main.c
 *
 * MATLAB Coder version            : 3.1
 * C/C++ source code generated on  : 06-Jun-2017 21:00:10
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
#include "structInitFnc.h"
#include "main.h"
#include "structInitFnc_terminate.h"
#include "structInitFnc_initialize.h"

/* Function Declarations */
static Base_Struct argInit_Base_Struct(void);
static Drive_Struct argInit_Drive_Struct(void);
static Platform_Struct argInit_Platform_Struct(void);
static Steward_Struct argInit_Steward_Struct(void);
static double argInit_real_T(void);
static void main_structInitFnc(void);

/* Function Definitions */

/*
 * Arguments    : void
 * Return Type  : Base_Struct
 */
static Base_Struct argInit_Base_Struct(void)
{
  Base_Struct result;

  /* Set the value of each structure field.
     Change this value to the value that the application requires. */
  result.r = argInit_real_T();
  result.alpha = argInit_real_T();
  return result;
}

/*
 * Arguments    : void
 * Return Type  : Drive_Struct
 */
static Drive_Struct argInit_Drive_Struct(void)
{
  Drive_Struct result;

  /* Set the value of each structure field.
     Change this value to the value that the application requires. */
  result.a = argInit_real_T();
  result.s = argInit_real_T();
  return result;
}

/*
 * Arguments    : void
 * Return Type  : Platform_Struct
 */
static Platform_Struct argInit_Platform_Struct(void)
{
  Platform_Struct result;

  /* Set the value of each structure field.
     Change this value to the value that the application requires. */
  result.r = argInit_real_T();
  result.alpha = argInit_real_T();
  return result;
}

/*
 * Arguments    : void
 * Return Type  : Steward_Struct
 */
static Steward_Struct argInit_Steward_Struct(void)
{
  Steward_Struct result;

  /* Set the value of each structure field.
     Change this value to the value that the application requires. */
  result.base = argInit_Base_Struct();
  result.platform = argInit_Platform_Struct();
  result.drive = argInit_Drive_Struct();
  return result;
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
static void main_structInitFnc(void)
{
  Steward_Struct r0;
  static struct0_T ik;

  /* Initialize function 'structInitFnc' input arguments. */
  /* Initialize function input argument 'steward'. */
  /* Call the entry-point 'structInitFnc'. */
  r0 = argInit_Steward_Struct();
  structInitFnc(&r0, &ik);
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
  structInitFnc_initialize();

  /* Invoke the entry-point functions.
     You can call entry-point functions multiple times. */
  main_structInitFnc();

  /* Terminate the application.
     You do not need to do this more than one time. */
  structInitFnc_terminate();
  return 0;
}

/*
 * File trailer for main.c
 *
 * [EOF]
 */
