/*
 * helikopter4_dt.h
 *
 * Code generation for model "helikopter4".
 *
 * Model version              : 1.68
 * Simulink Coder version : 8.6 (R2014a) 27-Dec-2013
 * C source code generated on : Tue Apr 19 20:38:38 2016
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "ext_types.h"

/* data type size table */
static uint_T rtDataTypeSizes[] = {
  sizeof(real_T),
  sizeof(real32_T),
  sizeof(int8_T),
  sizeof(uint8_T),
  sizeof(int16_T),
  sizeof(uint16_T),
  sizeof(int32_T),
  sizeof(uint32_T),
  sizeof(boolean_T),
  sizeof(fcn_call_T),
  sizeof(int_T),
  sizeof(pointer_T),
  sizeof(action_T),
  2*sizeof(uint32_T),
  sizeof(t_card)
};

/* data type name table */
static const char_T * rtDataTypeNames[] = {
  "real_T",
  "real32_T",
  "int8_T",
  "uint8_T",
  "int16_T",
  "uint16_T",
  "int32_T",
  "uint32_T",
  "boolean_T",
  "fcn_call_T",
  "int_T",
  "pointer_T",
  "action_T",
  "timer_uint32_pair_T",
  "t_card"
};

/* data type transitions for block I/O structure */
static DataTypeTransition rtBTransitions[] = {
  { (char_T *)(&helikopter4_B.KalibrerElev), 0, 0, 13 }
  ,

  { (char_T *)(&helikopter4_DW.HILInitialize_AIMinimums[0]), 0, 0, 66 },

  { (char_T *)(&helikopter4_DW.HILInitialize_Card), 14, 0, 1 },

  { (char_T *)(&helikopter4_DW.HILReadEncoder_PWORK), 11, 0, 22 },

  { (char_T *)(&helikopter4_DW.HILInitialize_ClockModes[0]), 6, 0, 46 },

  { (char_T *)(&helikopter4_DW.HILInitialize_POSortedChans[0]), 7, 0, 8 },

  { (char_T *)(&helikopter4_DW.ToFile_IWORK.Count), 10, 0, 7 }
};

/* data type transition table for block I/O structure */
static DataTypeTransitionTable rtBTransTable = {
  7U,
  rtBTransitions
};

/* data type transitions for Parameters structure */
static DataTypeTransition rtPTransitions[] = {
  { (char_T *)(&helikopter4_P.K[0]), 0, 0, 39 },

  { (char_T *)(&helikopter4_P.HILInitialize_hardware_clocks[0]), 6, 0, 9 },

  { (char_T *)(&helikopter4_P.HILInitialize_analog_input_chan[0]), 7, 0, 38 },

  { (char_T *)(&helikopter4_P.HILInitialize_active), 8, 0, 35 },

  { (char_T *)(&helikopter4_P.Constant_Value), 0, 0, 61 },

  { (char_T *)(&helikopter4_P.HILReadEncoder_Active), 8, 0, 2 }
};

/* data type transition table for Parameters structure */
static DataTypeTransitionTable rtPTransTable = {
  6U,
  rtPTransitions
};

/* [EOF] helikopter4_dt.h */
