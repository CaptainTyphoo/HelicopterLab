/*
 * helikopter2.c
 *
 * Code generation for model "helikopter2".
 *
 * Model version              : 1.61
 * Simulink Coder version : 8.6 (R2014a) 27-Dec-2013
 * C source code generated on : Tue Apr 19 17:11:56 2016
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#include "helikopter2.h"
#include "helikopter2_private.h"
#include "helikopter2_dt.h"

/* Block signals (auto storage) */
B_helikopter2_T helikopter2_B;

/* Continuous states */
X_helikopter2_T helikopter2_X;

/* Block states (auto storage) */
DW_helikopter2_T helikopter2_DW;

/* Real-time model */
RT_MODEL_helikopter2_T helikopter2_M_;
RT_MODEL_helikopter2_T *const helikopter2_M = &helikopter2_M_;

/*
 * Writes out MAT-file header.  Returns success or failure.
 * Returns:
 *      0 - success
 *      1 - failure
 */
int_T rt_WriteMat4FileHeader(FILE *fp, int32_T m, int32_T n, const char *name)
{
  typedef enum { ELITTLE_ENDIAN, EBIG_ENDIAN } ByteOrder;

  int16_T one = 1;
  ByteOrder byteOrder = (*((int8_T *)&one)==1) ? ELITTLE_ENDIAN : EBIG_ENDIAN;
  int32_T type = (byteOrder == ELITTLE_ENDIAN) ? 0: 1000;
  int32_T imagf = 0;
  int32_T name_len = (int32_T)strlen(name) + 1;
  if ((fwrite(&type, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&m, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&n, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&imagf, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&name_len, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(name, sizeof(char), name_len, fp) == 0)) {
    return(1);
  } else {
    return(0);
  }
}                                      /* end rt_WriteMat4FileHeader */

/*
 * This function updates continuous states using the ODE1 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE1_IntgData *id = (ODE1_IntgData *)rtsiGetSolverData(si);
  real_T *f0 = id->f[0];
  int_T i;
  int_T nXc = 5;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);
  rtsiSetdX(si, f0);
  helikopter2_derivatives();
  rtsiSetT(si, tnew);
  for (i = 0; i < nXc; i++) {
    *x += h * f0[i];
    x++;
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model output function */
void helikopter2_output(void)
{
  /* local block i/o variables */
  real_T rtb_Saturation_p;
  real_T rtb_HILReadEncoder_o1;
  real_T rtb_HILReadEncoder_o2;
  real_T rtb_HILReadEncoder_o3;
  real_T rtb_Gain[6];
  real_T rtb_Gain1;
  real_T tmp[6];
  int32_T i;
  int32_T i_0;
  real_T u0;
  if (rtmIsMajorTimeStep(helikopter2_M)) {
    /* set solver stop time */
    if (!(helikopter2_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&helikopter2_M->solverInfo,
                            ((helikopter2_M->Timing.clockTickH0 + 1) *
        helikopter2_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&helikopter2_M->solverInfo,
                            ((helikopter2_M->Timing.clockTick0 + 1) *
        helikopter2_M->Timing.stepSize0 + helikopter2_M->Timing.clockTickH0 *
        helikopter2_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(helikopter2_M)) {
    helikopter2_M->Timing.t[0] = rtsiGetT(&helikopter2_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(helikopter2_M)) {
    /* S-Function (hil_read_encoder_block): '<S2>/HIL Read Encoder' */

    /* S-Function Block: helikopter2/Heli 3D/HIL Read Encoder (hil_read_encoder_block) */
    {
      t_error result = hil_read_encoder(helikopter2_DW.HILInitialize_Card,
        helikopter2_P.HILReadEncoder_channels, 3,
        &helikopter2_DW.HILReadEncoder_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helikopter2_M, _rt_error_message);
      } else {
        rtb_HILReadEncoder_o1 = helikopter2_DW.HILReadEncoder_Buffer[0];
        rtb_HILReadEncoder_o2 = helikopter2_DW.HILReadEncoder_Buffer[1];
        rtb_HILReadEncoder_o3 = helikopter2_DW.HILReadEncoder_Buffer[2];
      }
    }

    /* Gain: '<S2>/Kalibrer-Elev' */
    helikopter2_B.KalibrerElev = helikopter2_P.KalibElevasjon *
      rtb_HILReadEncoder_o3;

    /* Sum: '<Root>/Add' incorporates:
     *  Constant: '<Root>/Constant'
     */
    helikopter2_B.Add = helikopter2_B.KalibrerElev +
      helikopter2_P.Constant_Value;

    /* Gain: '<S2>/Kalibrer-Pitch' */
    helikopter2_B.KalibrerPitch = helikopter2_P.KalibPitch *
      rtb_HILReadEncoder_o2;
  }

  /* TransferFcn: '<S2>/Vandring Lavpass' */
  helikopter2_B.VandringLavpass = 0.0;
  helikopter2_B.VandringLavpass += helikopter2_P.VandringLavpass_C *
    helikopter2_X.VandringLavpass_CSTATE;
  if (rtmIsMajorTimeStep(helikopter2_M)) {
    /* ToFile: '<Root>/To File' */
    {
      if (!(++helikopter2_DW.ToFile_IWORK.Decimation % 1) &&
          (helikopter2_DW.ToFile_IWORK.Count*2)+1 < 100000000 ) {
        FILE *fp = (FILE *) helikopter2_DW.ToFile_PWORK.FilePtr;
        if (fp != (NULL)) {
          real_T u[2];
          helikopter2_DW.ToFile_IWORK.Decimation = 0;
          u[0] = helikopter2_M->Timing.t[1];
          u[1] = helikopter2_B.VandringLavpass;
          if (fwrite(u, sizeof(real_T), 2, fp) != 2) {
            rtmSetErrorStatus(helikopter2_M,
                              "Error writing to MAT-file helicopter2/travel2.mat");
            return;
          }

          if (((++helikopter2_DW.ToFile_IWORK.Count)*2)+1 >= 100000000) {
            (void)fprintf(stdout,
                          "*** The ToFile block will stop logging data before\n"
                          "    the simulation has ended, because it has reached\n"
                          "    the maximum number of elements (100000000)\n"
                          "    allowed in MAT-file helicopter2/travel2.mat.\n");
          }
        }
      }
    }

    /* ToFile: '<Root>/To File1' */
    {
      if (!(++helikopter2_DW.ToFile1_IWORK.Decimation % 1) &&
          (helikopter2_DW.ToFile1_IWORK.Count*2)+1 < 100000000 ) {
        FILE *fp = (FILE *) helikopter2_DW.ToFile1_PWORK.FilePtr;
        if (fp != (NULL)) {
          real_T u[2];
          helikopter2_DW.ToFile1_IWORK.Decimation = 0;
          u[0] = helikopter2_M->Timing.t[1];
          u[1] = helikopter2_B.KalibrerPitch;
          if (fwrite(u, sizeof(real_T), 2, fp) != 2) {
            rtmSetErrorStatus(helikopter2_M,
                              "Error writing to MAT-file helicopter2/pitch2.mat");
            return;
          }

          if (((++helikopter2_DW.ToFile1_IWORK.Count)*2)+1 >= 100000000) {
            (void)fprintf(stdout,
                          "*** The ToFile block will stop logging data before\n"
                          "    the simulation has ended, because it has reached\n"
                          "    the maximum number of elements (100000000)\n"
                          "    allowed in MAT-file helicopter2/pitch2.mat.\n");
          }
        }
      }
    }

    /* ToFile: '<Root>/To File2' */
    {
      if (!(++helikopter2_DW.ToFile2_IWORK.Decimation % 1) &&
          (helikopter2_DW.ToFile2_IWORK.Count*2)+1 < 100000000 ) {
        FILE *fp = (FILE *) helikopter2_DW.ToFile2_PWORK.FilePtr;
        if (fp != (NULL)) {
          real_T u[2];
          helikopter2_DW.ToFile2_IWORK.Decimation = 0;
          u[0] = helikopter2_M->Timing.t[1];
          u[1] = helikopter2_B.Add;
          if (fwrite(u, sizeof(real_T), 2, fp) != 2) {
            rtmSetErrorStatus(helikopter2_M,
                              "Error writing to MAT-file helicopter2/elevation2.mat");
            return;
          }

          if (((++helikopter2_DW.ToFile2_IWORK.Count)*2)+1 >= 100000000) {
            (void)fprintf(stdout,
                          "*** The ToFile block will stop logging data before\n"
                          "    the simulation has ended, because it has reached\n"
                          "    the maximum number of elements (100000000)\n"
                          "    allowed in MAT-file helicopter2/elevation2.mat.\n");
          }
        }
      }
    }
  }

  /* FromWorkspace: '<Root>/From Workspace' */
  {
    real_T *pDataValues = (real_T *) helikopter2_DW.FromWorkspace_PWORK.DataPtr;
    real_T *pTimeValues = (real_T *) helikopter2_DW.FromWorkspace_PWORK.TimePtr;
    int_T currTimeIndex = helikopter2_DW.FromWorkspace_IWORK.PrevIndex;
    real_T t = helikopter2_M->Timing.t[0];

    /* Get index */
    if (t <= pTimeValues[0]) {
      currTimeIndex = 0;
    } else if (t >= pTimeValues[140]) {
      currTimeIndex = 139;
    } else {
      if (t < pTimeValues[currTimeIndex]) {
        while (t < pTimeValues[currTimeIndex]) {
          currTimeIndex--;
        }
      } else {
        while (t >= pTimeValues[currTimeIndex + 1]) {
          currTimeIndex++;
        }
      }
    }

    helikopter2_DW.FromWorkspace_IWORK.PrevIndex = currTimeIndex;

    /* Post output */
    {
      real_T t1 = pTimeValues[currTimeIndex];
      real_T t2 = pTimeValues[currTimeIndex + 1];
      if (t1 == t2) {
        if (t < t1) {
          helikopter2_B.FromWorkspace = pDataValues[currTimeIndex];
        } else {
          helikopter2_B.FromWorkspace = pDataValues[currTimeIndex + 1];
        }
      } else {
        real_T f1 = (t2 - t) / (t2 - t1);
        real_T f2 = 1.0 - f1;
        real_T d1;
        real_T d2;
        int_T TimeIndex= currTimeIndex;
        d1 = pDataValues[TimeIndex];
        d2 = pDataValues[TimeIndex + 1];
        helikopter2_B.FromWorkspace = (real_T) rtInterpolate(d1, d2, f1, f2);
        pDataValues += 141;
      }
    }
  }

  if (rtmIsMajorTimeStep(helikopter2_M)) {
    /* ToFile: '<Root>/To File3' */
    {
      if (!(++helikopter2_DW.ToFile3_IWORK.Decimation % 1) &&
          (helikopter2_DW.ToFile3_IWORK.Count*2)+1 < 100000000 ) {
        FILE *fp = (FILE *) helikopter2_DW.ToFile3_PWORK.FilePtr;
        if (fp != (NULL)) {
          real_T u[2];
          helikopter2_DW.ToFile3_IWORK.Decimation = 0;
          u[0] = helikopter2_M->Timing.t[1];
          u[1] = helikopter2_B.FromWorkspace;
          if (fwrite(u, sizeof(real_T), 2, fp) != 2) {
            rtmSetErrorStatus(helikopter2_M,
                              "Error writing to MAT-file helicopter2/input2.mat");
            return;
          }

          if (((++helikopter2_DW.ToFile3_IWORK.Count)*2)+1 >= 100000000) {
            (void)fprintf(stdout,
                          "*** The ToFile block will stop logging data before\n"
                          "    the simulation has ended, because it has reached\n"
                          "    the maximum number of elements (100000000)\n"
                          "    allowed in MAT-file helicopter2/input2.mat.\n");
          }
        }
      }
    }
  }

  /* Integrator: '<S1>/Integrator'
   *
   * Regarding '<S1>/Integrator':
   *  Limited Integrator
   */
  if (helikopter2_X.Integrator_CSTATE >= helikopter2_P.Integrator_UpperSat ) {
    helikopter2_X.Integrator_CSTATE = helikopter2_P.Integrator_UpperSat;
  } else if (helikopter2_X.Integrator_CSTATE <=
             (helikopter2_P.Integrator_LowerSat) ) {
    helikopter2_X.Integrator_CSTATE = (helikopter2_P.Integrator_LowerSat);
  }

  rtb_Saturation_p = helikopter2_X.Integrator_CSTATE;
  if (rtmIsMajorTimeStep(helikopter2_M)) {
    /* Gain: '<S2>/Kalibrer -Vandring' */
    helikopter2_B.KalibrerVandring = helikopter2_P.KalibVandring *
      rtb_HILReadEncoder_o1;
  }

  /* SignalConversion: '<Root>/TmpSignal ConversionAtGainInport1' incorporates:
   *  TransferFcn: '<S2>/Transfer Fcn4'
   *  TransferFcn: '<S2>/Transfer Fcn5'
   *  TransferFcn: '<S2>/Vandring Deriv'
   */
  tmp[0] = helikopter2_B.VandringLavpass;
  tmp[1] = helikopter2_P.VandringDeriv_C * helikopter2_X.VandringDeriv_CSTATE +
    helikopter2_P.VandringDeriv_D * helikopter2_B.KalibrerVandring;
  tmp[2] = helikopter2_B.KalibrerPitch;
  tmp[3] = helikopter2_P.TransferFcn4_C * helikopter2_X.TransferFcn4_CSTATE +
    helikopter2_P.TransferFcn4_D * helikopter2_B.KalibrerPitch;
  tmp[4] = helikopter2_B.Add;
  tmp[5] = helikopter2_P.TransferFcn5_C * helikopter2_X.TransferFcn5_CSTATE +
    helikopter2_P.TransferFcn5_D * helikopter2_B.KalibrerElev;

  /* Gain: '<Root>/Gain' */
  for (i = 0; i < 6; i++) {
    rtb_Gain[i] = 0.0;
    for (i_0 = 0; i_0 < 6; i_0++) {
      rtb_Gain[i] += helikopter2_P.Gain_Gain[6 * i_0 + i] * tmp[i_0];
    }
  }

  /* End of Gain: '<Root>/Gain' */

  /* Sum: '<S1>/Sum' incorporates:
   *  Constant: '<Root>/elevation'
   */
  rtb_Gain1 = helikopter2_P.elevation_Value - rtb_Gain[4];

  /* Gain: '<S1>/K_ei' */
  helikopter2_B.K_ei = helikopter2_P.K_ei * rtb_Gain1;

  /* Sum: '<S1>/Sum1' incorporates:
   *  Gain: '<S1>/K_ed'
   *  Gain: '<S1>/K_ep'
   */
  rtb_Saturation_p = (helikopter2_P.K_ep * rtb_Gain1 + rtb_Saturation_p) +
    -helikopter2_P.K_ed * rtb_Gain[5];

  /* Saturate: '<S1>/Saturation' */
  if (rtb_Saturation_p > helikopter2_P.Saturation_UpperSat) {
    rtb_Saturation_p = helikopter2_P.Saturation_UpperSat;
  } else {
    if (rtb_Saturation_p < helikopter2_P.Saturation_LowerSat) {
      rtb_Saturation_p = helikopter2_P.Saturation_LowerSat;
    }
  }

  /* End of Saturate: '<S1>/Saturation' */
  if (rtmIsMajorTimeStep(helikopter2_M)) {
  }

  /* Saturate: '<S3>/Saturation' */
  if (helikopter2_B.FromWorkspace > helikopter2_P.Saturation_UpperSat_d) {
    rtb_Gain1 = helikopter2_P.Saturation_UpperSat_d;
  } else if (helikopter2_B.FromWorkspace < helikopter2_P.Saturation_LowerSat_n)
  {
    rtb_Gain1 = helikopter2_P.Saturation_LowerSat_n;
  } else {
    rtb_Gain1 = helikopter2_B.FromWorkspace;
  }

  /* Sum: '<S3>/Sum' incorporates:
   *  Gain: '<S3>/K_pd'
   *  Gain: '<S3>/K_pp'
   *  Saturate: '<S3>/Saturation'
   *  Sum: '<S3>/Sum1'
   */
  rtb_Gain1 = 0.3 * helikopter2_P.K_pp * (rtb_Gain1 - rtb_Gain[2]) -
    helikopter2_P.K_pd * rtb_Gain[3];

  /* Gain: '<S4>/Gain2' incorporates:
   *  Sum: '<S4>/Sum4'
   */
  u0 = (rtb_Saturation_p - rtb_Gain1) * helikopter2_P.V_b_eq;

  /* Saturate: '<S2>/Sat B' */
  if (u0 > helikopter2_P.SatB_UpperSat) {
    helikopter2_B.SatB = helikopter2_P.SatB_UpperSat;
  } else if (u0 < helikopter2_P.SatB_LowerSat) {
    helikopter2_B.SatB = helikopter2_P.SatB_LowerSat;
  } else {
    helikopter2_B.SatB = u0;
  }

  /* End of Saturate: '<S2>/Sat B' */
  if (rtmIsMajorTimeStep(helikopter2_M)) {
  }

  /* Gain: '<S4>/Gain1' incorporates:
   *  Sum: '<S4>/Sum3'
   */
  u0 = (rtb_Gain1 + rtb_Saturation_p) * helikopter2_P.V_f_eq;

  /* Saturate: '<S2>/Sat' */
  if (u0 > helikopter2_P.Sat_UpperSat) {
    helikopter2_B.Sat = helikopter2_P.Sat_UpperSat;
  } else if (u0 < helikopter2_P.Sat_LowerSat) {
    helikopter2_B.Sat = helikopter2_P.Sat_LowerSat;
  } else {
    helikopter2_B.Sat = u0;
  }

  /* End of Saturate: '<S2>/Sat' */
  if (rtmIsMajorTimeStep(helikopter2_M)) {
  }

  /* Sum: '<S2>/Add' incorporates:
   *  Constant: '<S2>/elevation'
   */
  helikopter2_B.Add_j = helikopter2_B.SatB - helikopter2_P.elevation_Value_g;
  if (rtmIsMajorTimeStep(helikopter2_M)) {
    /* S-Function (hil_write_analog_block): '<S2>/HIL Write Analog' */

    /* S-Function Block: helikopter2/Heli 3D/HIL Write Analog (hil_write_analog_block) */
    {
      t_error result;
      helikopter2_DW.HILWriteAnalog_Buffer[0] = helikopter2_B.Add_j;
      helikopter2_DW.HILWriteAnalog_Buffer[1] = helikopter2_B.Sat;
      result = hil_write_analog(helikopter2_DW.HILInitialize_Card,
        helikopter2_P.HILWriteAnalog_channels, 2,
        &helikopter2_DW.HILWriteAnalog_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helikopter2_M, _rt_error_message);
      }
    }
  }
}

/* Model update function */
void helikopter2_update(void)
{
  if (rtmIsMajorTimeStep(helikopter2_M)) {
    rt_ertODEUpdateContinuousStates(&helikopter2_M->solverInfo);
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++helikopter2_M->Timing.clockTick0)) {
    ++helikopter2_M->Timing.clockTickH0;
  }

  helikopter2_M->Timing.t[0] = rtsiGetSolverStopTime(&helikopter2_M->solverInfo);

  {
    /* Update absolute timer for sample time: [0.002s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick1"
     * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++helikopter2_M->Timing.clockTick1)) {
      ++helikopter2_M->Timing.clockTickH1;
    }

    helikopter2_M->Timing.t[1] = helikopter2_M->Timing.clockTick1 *
      helikopter2_M->Timing.stepSize1 + helikopter2_M->Timing.clockTickH1 *
      helikopter2_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Derivatives for root system: '<Root>' */
void helikopter2_derivatives(void)
{
  XDot_helikopter2_T *_rtXdot;
  _rtXdot = ((XDot_helikopter2_T *) helikopter2_M->ModelData.derivs);

  /* Derivatives for TransferFcn: '<S2>/Vandring Lavpass' */
  _rtXdot->VandringLavpass_CSTATE = 0.0;
  _rtXdot->VandringLavpass_CSTATE += helikopter2_P.VandringLavpass_A *
    helikopter2_X.VandringLavpass_CSTATE;
  _rtXdot->VandringLavpass_CSTATE += helikopter2_B.KalibrerVandring;

  /* Derivatives for Integrator: '<S1>/Integrator' */
  {
    boolean_T lsat;
    boolean_T usat;
    lsat = ( helikopter2_X.Integrator_CSTATE <=
            (helikopter2_P.Integrator_LowerSat) );
    usat = ( helikopter2_X.Integrator_CSTATE >=
            helikopter2_P.Integrator_UpperSat );
    if ((!lsat && !usat) ||
        (lsat && (helikopter2_B.K_ei > 0)) ||
        (usat && (helikopter2_B.K_ei < 0)) ) {
      ((XDot_helikopter2_T *) helikopter2_M->ModelData.derivs)
        ->Integrator_CSTATE = helikopter2_B.K_ei;
    } else {
      /* in saturation */
      ((XDot_helikopter2_T *) helikopter2_M->ModelData.derivs)
        ->Integrator_CSTATE = 0.0;
    }
  }

  /* Derivatives for TransferFcn: '<S2>/Vandring Deriv' */
  _rtXdot->VandringDeriv_CSTATE = 0.0;
  _rtXdot->VandringDeriv_CSTATE += helikopter2_P.VandringDeriv_A *
    helikopter2_X.VandringDeriv_CSTATE;
  _rtXdot->VandringDeriv_CSTATE += helikopter2_B.KalibrerVandring;

  /* Derivatives for TransferFcn: '<S2>/Transfer Fcn4' */
  _rtXdot->TransferFcn4_CSTATE = 0.0;
  _rtXdot->TransferFcn4_CSTATE += helikopter2_P.TransferFcn4_A *
    helikopter2_X.TransferFcn4_CSTATE;
  _rtXdot->TransferFcn4_CSTATE += helikopter2_B.KalibrerPitch;

  /* Derivatives for TransferFcn: '<S2>/Transfer Fcn5' */
  _rtXdot->TransferFcn5_CSTATE = 0.0;
  _rtXdot->TransferFcn5_CSTATE += helikopter2_P.TransferFcn5_A *
    helikopter2_X.TransferFcn5_CSTATE;
  _rtXdot->TransferFcn5_CSTATE += helikopter2_B.KalibrerElev;
}

/* Model initialize function */
void helikopter2_initialize(void)
{
  /* Start for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: helikopter2/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q8_usb", "0", &helikopter2_DW.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helikopter2_M, _rt_error_message);
      return;
    }

    is_switching = false;
    result = hil_set_card_specific_options(helikopter2_DW.HILInitialize_Card,
      "update_rate=normal;decimation=1", 32);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helikopter2_M, _rt_error_message);
      return;
    }

    result = hil_watchdog_clear(helikopter2_DW.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helikopter2_M, _rt_error_message);
      return;
    }

    if ((helikopter2_P.HILInitialize_set_analog_input_ && !is_switching) ||
        (helikopter2_P.HILInitialize_set_analog_inpu_m && is_switching)) {
      {
        int_T i1;
        real_T *dw_AIMinimums = &helikopter2_DW.HILInitialize_AIMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMinimums[i1] = helikopter2_P.HILInitialize_analog_input_mini;
        }
      }

      {
        int_T i1;
        real_T *dw_AIMaximums = &helikopter2_DW.HILInitialize_AIMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMaximums[i1] = helikopter2_P.HILInitialize_analog_input_maxi;
        }
      }

      result = hil_set_analog_input_ranges(helikopter2_DW.HILInitialize_Card,
        helikopter2_P.HILInitialize_analog_input_chan, 8U,
        &helikopter2_DW.HILInitialize_AIMinimums[0],
        &helikopter2_DW.HILInitialize_AIMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helikopter2_M, _rt_error_message);
        return;
      }
    }

    if ((helikopter2_P.HILInitialize_set_analog_output && !is_switching) ||
        (helikopter2_P.HILInitialize_set_analog_outp_b && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOMinimums = &helikopter2_DW.HILInitialize_AOMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMinimums[i1] = helikopter2_P.HILInitialize_analog_output_min;
        }
      }

      {
        int_T i1;
        real_T *dw_AOMaximums = &helikopter2_DW.HILInitialize_AOMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMaximums[i1] = helikopter2_P.HILInitialize_analog_output_max;
        }
      }

      result = hil_set_analog_output_ranges(helikopter2_DW.HILInitialize_Card,
        helikopter2_P.HILInitialize_analog_output_cha, 8U,
        &helikopter2_DW.HILInitialize_AOMinimums[0],
        &helikopter2_DW.HILInitialize_AOMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helikopter2_M, _rt_error_message);
        return;
      }
    }

    if ((helikopter2_P.HILInitialize_set_analog_outp_e && !is_switching) ||
        (helikopter2_P.HILInitialize_set_analog_outp_j && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &helikopter2_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = helikopter2_P.HILInitialize_initial_analog_ou;
        }
      }

      result = hil_write_analog(helikopter2_DW.HILInitialize_Card,
        helikopter2_P.HILInitialize_analog_output_cha, 8U,
        &helikopter2_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helikopter2_M, _rt_error_message);
        return;
      }
    }

    if (helikopter2_P.HILInitialize_set_analog_outp_p) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &helikopter2_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = helikopter2_P.HILInitialize_watchdog_analog_o;
        }
      }

      result = hil_watchdog_set_analog_expiration_state
        (helikopter2_DW.HILInitialize_Card,
         helikopter2_P.HILInitialize_analog_output_cha, 8U,
         &helikopter2_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helikopter2_M, _rt_error_message);
        return;
      }
    }

    if ((helikopter2_P.HILInitialize_set_encoder_param && !is_switching) ||
        (helikopter2_P.HILInitialize_set_encoder_par_m && is_switching)) {
      {
        int_T i1;
        int32_T *dw_QuadratureModes =
          &helikopter2_DW.HILInitialize_QuadratureModes[0];
        for (i1=0; i1 < 8; i1++) {
          dw_QuadratureModes[i1] = helikopter2_P.HILInitialize_quadrature;
        }
      }

      result = hil_set_encoder_quadrature_mode(helikopter2_DW.HILInitialize_Card,
        helikopter2_P.HILInitialize_encoder_channels, 8U,
        (t_encoder_quadrature_mode *)
        &helikopter2_DW.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helikopter2_M, _rt_error_message);
        return;
      }
    }

    if ((helikopter2_P.HILInitialize_set_encoder_count && !is_switching) ||
        (helikopter2_P.HILInitialize_set_encoder_cou_k && is_switching)) {
      {
        int_T i1;
        int32_T *dw_InitialEICounts =
          &helikopter2_DW.HILInitialize_InitialEICounts[0];
        for (i1=0; i1 < 8; i1++) {
          dw_InitialEICounts[i1] = helikopter2_P.HILInitialize_initial_encoder_c;
        }
      }

      result = hil_set_encoder_counts(helikopter2_DW.HILInitialize_Card,
        helikopter2_P.HILInitialize_encoder_channels, 8U,
        &helikopter2_DW.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helikopter2_M, _rt_error_message);
        return;
      }
    }

    if ((helikopter2_P.HILInitialize_set_pwm_params_at && !is_switching) ||
        (helikopter2_P.HILInitialize_set_pwm_params__f && is_switching)) {
      uint32_T num_duty_cycle_modes = 0;
      uint32_T num_frequency_modes = 0;

      {
        int_T i1;
        int32_T *dw_POModeValues = &helikopter2_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = helikopter2_P.HILInitialize_pwm_modes;
        }
      }

      result = hil_set_pwm_mode(helikopter2_DW.HILInitialize_Card,
        helikopter2_P.HILInitialize_pwm_channels, 8U, (t_pwm_mode *)
        &helikopter2_DW.HILInitialize_POModeValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helikopter2_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        const uint32_T *p_HILInitialize_pwm_channels =
          helikopter2_P.HILInitialize_pwm_channels;
        int32_T *dw_POModeValues = &helikopter2_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          if (dw_POModeValues[i1] == PWM_DUTY_CYCLE_MODE || dw_POModeValues[i1] ==
              PWM_ONE_SHOT_MODE || dw_POModeValues[i1] == PWM_TIME_MODE) {
            helikopter2_DW.HILInitialize_POSortedChans[num_duty_cycle_modes] =
              p_HILInitialize_pwm_channels[i1];
            helikopter2_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes] =
              helikopter2_P.HILInitialize_pwm_frequency;
            num_duty_cycle_modes++;
          } else {
            helikopter2_DW.HILInitialize_POSortedChans[7U - num_frequency_modes]
              = p_HILInitialize_pwm_channels[i1];
            helikopter2_DW.HILInitialize_POSortedFreqs[7U - num_frequency_modes]
              = helikopter2_P.HILInitialize_pwm_frequency;
            num_frequency_modes++;
          }
        }
      }

      if (num_duty_cycle_modes > 0) {
        result = hil_set_pwm_frequency(helikopter2_DW.HILInitialize_Card,
          &helikopter2_DW.HILInitialize_POSortedChans[0], num_duty_cycle_modes,
          &helikopter2_DW.HILInitialize_POSortedFreqs[0]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(helikopter2_M, _rt_error_message);
          return;
        }
      }

      if (num_frequency_modes > 0) {
        result = hil_set_pwm_duty_cycle(helikopter2_DW.HILInitialize_Card,
          &helikopter2_DW.HILInitialize_POSortedChans[num_duty_cycle_modes],
          num_frequency_modes,
          &helikopter2_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(helikopter2_M, _rt_error_message);
          return;
        }
      }

      {
        int_T i1;
        int32_T *dw_POModeValues = &helikopter2_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = helikopter2_P.HILInitialize_pwm_configuration;
        }
      }

      {
        int_T i1;
        int32_T *dw_POAlignValues = &helikopter2_DW.HILInitialize_POAlignValues
          [0];
        for (i1=0; i1 < 8; i1++) {
          dw_POAlignValues[i1] = helikopter2_P.HILInitialize_pwm_alignment;
        }
      }

      {
        int_T i1;
        int32_T *dw_POPolarityVals =
          &helikopter2_DW.HILInitialize_POPolarityVals[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POPolarityVals[i1] = helikopter2_P.HILInitialize_pwm_polarity;
        }
      }

      result = hil_set_pwm_configuration(helikopter2_DW.HILInitialize_Card,
        helikopter2_P.HILInitialize_pwm_channels, 8U,
        (t_pwm_configuration *) &helikopter2_DW.HILInitialize_POModeValues[0],
        (t_pwm_alignment *) &helikopter2_DW.HILInitialize_POAlignValues[0],
        (t_pwm_polarity *) &helikopter2_DW.HILInitialize_POPolarityVals[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helikopter2_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        real_T *dw_POSortedFreqs = &helikopter2_DW.HILInitialize_POSortedFreqs[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POSortedFreqs[i1] = helikopter2_P.HILInitialize_pwm_leading_deadb;
        }
      }

      {
        int_T i1;
        real_T *dw_POValues = &helikopter2_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helikopter2_P.HILInitialize_pwm_trailing_dead;
        }
      }

      result = hil_set_pwm_deadband(helikopter2_DW.HILInitialize_Card,
        helikopter2_P.HILInitialize_pwm_channels, 8U,
        &helikopter2_DW.HILInitialize_POSortedFreqs[0],
        &helikopter2_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helikopter2_M, _rt_error_message);
        return;
      }
    }

    if ((helikopter2_P.HILInitialize_set_pwm_outputs_a && !is_switching) ||
        (helikopter2_P.HILInitialize_set_pwm_outputs_g && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &helikopter2_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helikopter2_P.HILInitialize_initial_pwm_outpu;
        }
      }

      result = hil_write_pwm(helikopter2_DW.HILInitialize_Card,
        helikopter2_P.HILInitialize_pwm_channels, 8U,
        &helikopter2_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helikopter2_M, _rt_error_message);
        return;
      }
    }

    if (helikopter2_P.HILInitialize_set_pwm_outputs_o) {
      {
        int_T i1;
        real_T *dw_POValues = &helikopter2_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helikopter2_P.HILInitialize_watchdog_pwm_outp;
        }
      }

      result = hil_watchdog_set_pwm_expiration_state
        (helikopter2_DW.HILInitialize_Card,
         helikopter2_P.HILInitialize_pwm_channels, 8U,
         &helikopter2_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helikopter2_M, _rt_error_message);
        return;
      }
    }
  }

  /* Start for ToFile: '<Root>/To File' */
  {
    char fileName[509] = "helicopter2/travel2.mat";
    FILE *fp = (NULL);
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(helikopter2_M,
                        "Error creating .mat file helicopter2/travel2.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp,2,0,"travel2")) {
      rtmSetErrorStatus(helikopter2_M,
                        "Error writing mat file header to file helicopter2/travel2.mat");
      return;
    }

    helikopter2_DW.ToFile_IWORK.Count = 0;
    helikopter2_DW.ToFile_IWORK.Decimation = -1;
    helikopter2_DW.ToFile_PWORK.FilePtr = fp;
  }

  /* Start for ToFile: '<Root>/To File1' */
  {
    char fileName[509] = "helicopter2/pitch2.mat";
    FILE *fp = (NULL);
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(helikopter2_M,
                        "Error creating .mat file helicopter2/pitch2.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp,2,0,"pitch2")) {
      rtmSetErrorStatus(helikopter2_M,
                        "Error writing mat file header to file helicopter2/pitch2.mat");
      return;
    }

    helikopter2_DW.ToFile1_IWORK.Count = 0;
    helikopter2_DW.ToFile1_IWORK.Decimation = -1;
    helikopter2_DW.ToFile1_PWORK.FilePtr = fp;
  }

  /* Start for ToFile: '<Root>/To File2' */
  {
    char fileName[509] = "helicopter2/elevation2.mat";
    FILE *fp = (NULL);
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(helikopter2_M,
                        "Error creating .mat file helicopter2/elevation2.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp,2,0,"elevation2")) {
      rtmSetErrorStatus(helikopter2_M,
                        "Error writing mat file header to file helicopter2/elevation2.mat");
      return;
    }

    helikopter2_DW.ToFile2_IWORK.Count = 0;
    helikopter2_DW.ToFile2_IWORK.Decimation = -1;
    helikopter2_DW.ToFile2_PWORK.FilePtr = fp;
  }

  /* Start for FromWorkspace: '<Root>/From Workspace' */
  {
    static real_T pTimeValues0[] = { 0.0, 0.25, 0.5, 0.75, 1.0, 1.25, 1.5, 1.75,
      2.0, 2.25, 2.5, 2.75, 3.0, 3.25, 3.5, 3.75, 4.0, 4.25, 4.5, 4.75, 5.0,
      5.25, 5.5, 5.75, 6.0, 6.25, 6.5, 6.75, 7.0, 7.25, 7.5, 7.75, 8.0, 8.25,
      8.5, 8.75, 9.0, 9.25, 9.5, 9.75, 10.0, 10.25, 10.5, 10.75, 11.0, 11.25,
      11.5, 11.75, 12.0, 12.25, 12.5, 12.75, 13.0, 13.25, 13.5, 13.75, 14.0,
      14.25, 14.5, 14.75, 15.0, 15.25, 15.5, 15.75, 16.0, 16.25, 16.5, 16.75,
      17.0, 17.25, 17.5, 17.75, 18.0, 18.25, 18.5, 18.75, 19.0, 19.25, 19.5,
      19.75, 20.0, 20.25, 20.5, 20.75, 21.0, 21.25, 21.5, 21.75, 22.0, 22.25,
      22.5, 22.75, 23.0, 23.25, 23.5, 23.75, 24.0, 24.25, 24.5, 24.75, 25.0,
      25.25, 25.5, 25.75, 26.0, 26.25, 26.5, 26.75, 27.0, 27.25, 27.5, 27.75,
      28.0, 28.25, 28.5, 28.75, 29.0, 29.25, 29.5, 29.75, 30.0, 30.25, 30.5,
      30.75, 31.0, 31.25, 31.5, 31.75, 32.0, 32.25, 32.5, 32.75, 33.0, 33.25,
      33.5, 33.75, 34.0, 34.25, 34.5, 34.75, 35.0 } ;

    static real_T pDataValues0[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.23506944006512323,
      0.059942707218504879, 0.52359877558315282, 0.52359877558471124,
      0.52359877557480694, 0.523598775565105, 0.52359877555567735,
      0.52359877465635918, 0.51252527959395233, 0.48228842738851285,
      0.44809910995290847, 0.376817084115197, 0.29836488239794856,
      0.2407129177448577, 0.19910968563022516, 0.15742696852351609,
      0.11182309787619922, 0.068860082090494365, 0.032796719654467579,
      0.0017449511543785753, -0.0273386436590288, -0.054817970739392728,
      -0.079458777826571847, -0.10078054430868449, -0.1193958642900657,
      -0.13594564270150164, -0.15052431606498506, -0.16300212167879255,
      -0.17343780424496469, -0.18207074658731559, -0.18910845313087948,
      -0.19465001462578557, -0.19876473204616835, -0.20156044587830058,
      -0.20316935325720803, -0.20370791622669179, -0.20326885024860919,
      -0.20193839531012384, -0.19980689975507926, -0.196964085616431,
      -0.19349194124919267, -0.18946450439526125, -0.18495146876332477,
      -0.18001975737814802, -0.17473240353084105, -0.16914745779614856,
      -0.16331828032581938, -0.157294351944599, -0.15112158618075858,
      -0.1448421956819641, -0.13849464796248326, -0.13211388424610862,
      -0.12573159473977627, -0.1193763831949958, -0.11307386150490278,
      -0.10684677365383684, -0.10071516514239574, -0.094696552973693143,
      -0.088806070486213917, -0.083056599586182833, -0.077458907717526657,
      -0.072021789374844339, -0.06675220297606918, -0.061655399463621495,
      -0.056735045709696959, -0.051993345561878526, -0.0474311579121312,
      -0.043048110036385763, -0.038842705829208658, -0.034812429690379655,
      -0.030953846547420602, -0.027262697821598188, -0.023733993099681518,
      -0.020362097713122758, -0.0171408166128042, -0.014063474598800436,
      -0.011122992663096415, -0.0083119605806842977, -0.0056227066187019776,
      -0.0030473650343818223, -0.00057794053166175616, 0.0017936318229964893,
      0.0040754302746251695, 0.0062754895683094615, 0.00840174207715008,
      0.010461963302556263, 0.012463729209963024, 0.014414377844825793,
      0.016320954465240869, 0.018190139218582219, 0.02002819719589426,
      0.021840982075372072, 0.023633937673017649, 0.025411994012024462,
      0.027179390395283245, 0.028939653310707723, 0.03069583455362904,
      0.032450638452488474, 0.03420595364816021, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0 } ;

    helikopter2_DW.FromWorkspace_PWORK.TimePtr = (void *) pTimeValues0;
    helikopter2_DW.FromWorkspace_PWORK.DataPtr = (void *) pDataValues0;
    helikopter2_DW.FromWorkspace_IWORK.PrevIndex = 0;
  }

  /* Start for ToFile: '<Root>/To File3' */
  {
    char fileName[509] = "helicopter2/input2.mat";
    FILE *fp = (NULL);
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(helikopter2_M,
                        "Error creating .mat file helicopter2/input2.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp,2,0,"input2")) {
      rtmSetErrorStatus(helikopter2_M,
                        "Error writing mat file header to file helicopter2/input2.mat");
      return;
    }

    helikopter2_DW.ToFile3_IWORK.Count = 0;
    helikopter2_DW.ToFile3_IWORK.Decimation = -1;
    helikopter2_DW.ToFile3_PWORK.FilePtr = fp;
  }

  /* InitializeConditions for TransferFcn: '<S2>/Vandring Lavpass' */
  helikopter2_X.VandringLavpass_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S1>/Integrator' */
  helikopter2_X.Integrator_CSTATE = helikopter2_P.Integrator_IC;

  /* InitializeConditions for TransferFcn: '<S2>/Vandring Deriv' */
  helikopter2_X.VandringDeriv_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S2>/Transfer Fcn4' */
  helikopter2_X.TransferFcn4_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S2>/Transfer Fcn5' */
  helikopter2_X.TransferFcn5_CSTATE = 0.0;
}

/* Model terminate function */
void helikopter2_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: helikopter2/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    t_uint32 num_final_pwm_outputs = 0;
    hil_task_stop_all(helikopter2_DW.HILInitialize_Card);
    hil_monitor_stop_all(helikopter2_DW.HILInitialize_Card);
    is_switching = false;
    if ((helikopter2_P.HILInitialize_set_analog_out_ex && !is_switching) ||
        (helikopter2_P.HILInitialize_set_analog_outp_c && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &helikopter2_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = helikopter2_P.HILInitialize_final_analog_outp;
        }
      }

      num_final_analog_outputs = 8U;
    }

    if ((helikopter2_P.HILInitialize_set_pwm_output_ap && !is_switching) ||
        (helikopter2_P.HILInitialize_set_pwm_outputs_p && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &helikopter2_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helikopter2_P.HILInitialize_final_pwm_outputs;
        }
      }

      num_final_pwm_outputs = 8U;
    }

    if (0
        || num_final_analog_outputs > 0
        || num_final_pwm_outputs > 0
        ) {
      /* Attempt to write the final outputs atomically (due to firmware issue in old Q2-USB). Otherwise write channels individually */
      result = hil_write(helikopter2_DW.HILInitialize_Card
                         , helikopter2_P.HILInitialize_analog_output_cha,
                         num_final_analog_outputs
                         , helikopter2_P.HILInitialize_pwm_channels,
                         num_final_pwm_outputs
                         , NULL, 0
                         , NULL, 0
                         , &helikopter2_DW.HILInitialize_AOVoltages[0]
                         , &helikopter2_DW.HILInitialize_POValues[0]
                         , (t_boolean *) NULL
                         , NULL
                         );
      if (result == -QERR_HIL_WRITE_NOT_SUPPORTED) {
        t_error local_result;
        result = 0;

        /* The hil_write operation is not supported by this card. Write final outputs for each channel type */
        if (num_final_analog_outputs > 0) {
          local_result = hil_write_analog(helikopter2_DW.HILInitialize_Card,
            helikopter2_P.HILInitialize_analog_output_cha,
            num_final_analog_outputs, &helikopter2_DW.HILInitialize_AOVoltages[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (num_final_pwm_outputs > 0) {
          local_result = hil_write_pwm(helikopter2_DW.HILInitialize_Card,
            helikopter2_P.HILInitialize_pwm_channels, num_final_pwm_outputs,
            &helikopter2_DW.HILInitialize_POValues[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(helikopter2_M, _rt_error_message);
        }
      }
    }

    hil_task_delete_all(helikopter2_DW.HILInitialize_Card);
    hil_monitor_delete_all(helikopter2_DW.HILInitialize_Card);
    hil_close(helikopter2_DW.HILInitialize_Card);
    helikopter2_DW.HILInitialize_Card = NULL;
  }

  /* Terminate for ToFile: '<Root>/To File' */
  {
    FILE *fp = (FILE *) helikopter2_DW.ToFile_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "helicopter2/travel2.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helikopter2_M,
                          "Error closing MAT-file helicopter2/travel2.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(helikopter2_M,
                          "Error reopening MAT-file helicopter2/travel2.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 2, helikopter2_DW.ToFile_IWORK.Count,
           "travel2")) {
        rtmSetErrorStatus(helikopter2_M,
                          "Error writing header for travel2 to MAT-file helicopter2/travel2.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helikopter2_M,
                          "Error closing MAT-file helicopter2/travel2.mat");
        return;
      }

      helikopter2_DW.ToFile_PWORK.FilePtr = (NULL);
    }
  }

  /* Terminate for ToFile: '<Root>/To File1' */
  {
    FILE *fp = (FILE *) helikopter2_DW.ToFile1_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "helicopter2/pitch2.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helikopter2_M,
                          "Error closing MAT-file helicopter2/pitch2.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(helikopter2_M,
                          "Error reopening MAT-file helicopter2/pitch2.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 2, helikopter2_DW.ToFile1_IWORK.Count,
           "pitch2")) {
        rtmSetErrorStatus(helikopter2_M,
                          "Error writing header for pitch2 to MAT-file helicopter2/pitch2.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helikopter2_M,
                          "Error closing MAT-file helicopter2/pitch2.mat");
        return;
      }

      helikopter2_DW.ToFile1_PWORK.FilePtr = (NULL);
    }
  }

  /* Terminate for ToFile: '<Root>/To File2' */
  {
    FILE *fp = (FILE *) helikopter2_DW.ToFile2_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "helicopter2/elevation2.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helikopter2_M,
                          "Error closing MAT-file helicopter2/elevation2.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(helikopter2_M,
                          "Error reopening MAT-file helicopter2/elevation2.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 2, helikopter2_DW.ToFile2_IWORK.Count,
           "elevation2")) {
        rtmSetErrorStatus(helikopter2_M,
                          "Error writing header for elevation2 to MAT-file helicopter2/elevation2.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helikopter2_M,
                          "Error closing MAT-file helicopter2/elevation2.mat");
        return;
      }

      helikopter2_DW.ToFile2_PWORK.FilePtr = (NULL);
    }
  }

  /* Terminate for ToFile: '<Root>/To File3' */
  {
    FILE *fp = (FILE *) helikopter2_DW.ToFile3_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "helicopter2/input2.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helikopter2_M,
                          "Error closing MAT-file helicopter2/input2.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(helikopter2_M,
                          "Error reopening MAT-file helicopter2/input2.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 2, helikopter2_DW.ToFile3_IWORK.Count,
           "input2")) {
        rtmSetErrorStatus(helikopter2_M,
                          "Error writing header for input2 to MAT-file helicopter2/input2.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helikopter2_M,
                          "Error closing MAT-file helicopter2/input2.mat");
        return;
      }

      helikopter2_DW.ToFile3_PWORK.FilePtr = (NULL);
    }
  }
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/

/* Solver interface called by GRT_Main */
#ifndef USE_GENERATED_SOLVER

void rt_ODECreateIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEDestroyIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEUpdateContinuousStates(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

#endif

void MdlOutputs(int_T tid)
{
  helikopter2_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  helikopter2_update();
  UNUSED_PARAMETER(tid);
}

void MdlInitializeSizes(void)
{
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
}

void MdlStart(void)
{
  helikopter2_initialize();
}

void MdlTerminate(void)
{
  helikopter2_terminate();
}

/* Registration function */
RT_MODEL_helikopter2_T *helikopter2(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* non-finite (run-time) assignments */
  helikopter2_P.Integrator_UpperSat = rtInf;
  helikopter2_P.Integrator_LowerSat = rtMinusInf;

  /* initialize real-time model */
  (void) memset((void *)helikopter2_M, 0,
                sizeof(RT_MODEL_helikopter2_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&helikopter2_M->solverInfo,
                          &helikopter2_M->Timing.simTimeStep);
    rtsiSetTPtr(&helikopter2_M->solverInfo, &rtmGetTPtr(helikopter2_M));
    rtsiSetStepSizePtr(&helikopter2_M->solverInfo,
                       &helikopter2_M->Timing.stepSize0);
    rtsiSetdXPtr(&helikopter2_M->solverInfo, &helikopter2_M->ModelData.derivs);
    rtsiSetContStatesPtr(&helikopter2_M->solverInfo, (real_T **)
                         &helikopter2_M->ModelData.contStates);
    rtsiSetNumContStatesPtr(&helikopter2_M->solverInfo,
      &helikopter2_M->Sizes.numContStates);
    rtsiSetErrorStatusPtr(&helikopter2_M->solverInfo, (&rtmGetErrorStatus
      (helikopter2_M)));
    rtsiSetRTModelPtr(&helikopter2_M->solverInfo, helikopter2_M);
  }

  rtsiSetSimTimeStep(&helikopter2_M->solverInfo, MAJOR_TIME_STEP);
  helikopter2_M->ModelData.intgData.f[0] = helikopter2_M->ModelData.odeF[0];
  helikopter2_M->ModelData.contStates = ((real_T *) &helikopter2_X);
  rtsiSetSolverData(&helikopter2_M->solverInfo, (void *)
                    &helikopter2_M->ModelData.intgData);
  rtsiSetSolverName(&helikopter2_M->solverInfo,"ode1");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = helikopter2_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    helikopter2_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    helikopter2_M->Timing.sampleTimes = (&helikopter2_M->
      Timing.sampleTimesArray[0]);
    helikopter2_M->Timing.offsetTimes = (&helikopter2_M->
      Timing.offsetTimesArray[0]);

    /* task periods */
    helikopter2_M->Timing.sampleTimes[0] = (0.0);
    helikopter2_M->Timing.sampleTimes[1] = (0.002);

    /* task offsets */
    helikopter2_M->Timing.offsetTimes[0] = (0.0);
    helikopter2_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(helikopter2_M, &helikopter2_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = helikopter2_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    helikopter2_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(helikopter2_M, 35.0);
  helikopter2_M->Timing.stepSize0 = 0.002;
  helikopter2_M->Timing.stepSize1 = 0.002;

  /* External mode info */
  helikopter2_M->Sizes.checksums[0] = (2028408113U);
  helikopter2_M->Sizes.checksums[1] = (1734173546U);
  helikopter2_M->Sizes.checksums[2] = (962683251U);
  helikopter2_M->Sizes.checksums[3] = (2852203752U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[1];
    helikopter2_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(helikopter2_M->extModeInfo,
      &helikopter2_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(helikopter2_M->extModeInfo,
                        helikopter2_M->Sizes.checksums);
    rteiSetTPtr(helikopter2_M->extModeInfo, rtmGetTPtr(helikopter2_M));
  }

  helikopter2_M->solverInfoPtr = (&helikopter2_M->solverInfo);
  helikopter2_M->Timing.stepSize = (0.002);
  rtsiSetFixedStepSize(&helikopter2_M->solverInfo, 0.002);
  rtsiSetSolverMode(&helikopter2_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  helikopter2_M->ModelData.blockIO = ((void *) &helikopter2_B);

  {
    helikopter2_B.KalibrerElev = 0.0;
    helikopter2_B.Add = 0.0;
    helikopter2_B.KalibrerPitch = 0.0;
    helikopter2_B.VandringLavpass = 0.0;
    helikopter2_B.FromWorkspace = 0.0;
    helikopter2_B.KalibrerVandring = 0.0;
    helikopter2_B.K_ei = 0.0;
    helikopter2_B.SatB = 0.0;
    helikopter2_B.Sat = 0.0;
    helikopter2_B.Add_j = 0.0;
  }

  /* parameters */
  helikopter2_M->ModelData.defaultParam = ((real_T *)&helikopter2_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &helikopter2_X;
    helikopter2_M->ModelData.contStates = (x);
    (void) memset((void *)&helikopter2_X, 0,
                  sizeof(X_helikopter2_T));
  }

  /* states (dwork) */
  helikopter2_M->ModelData.dwork = ((void *) &helikopter2_DW);
  (void) memset((void *)&helikopter2_DW, 0,
                sizeof(DW_helikopter2_T));

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      helikopter2_DW.HILInitialize_AIMinimums[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      helikopter2_DW.HILInitialize_AIMaximums[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      helikopter2_DW.HILInitialize_AOMinimums[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      helikopter2_DW.HILInitialize_AOMaximums[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      helikopter2_DW.HILInitialize_AOVoltages[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      helikopter2_DW.HILInitialize_FilterFrequency[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      helikopter2_DW.HILInitialize_POSortedFreqs[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      helikopter2_DW.HILInitialize_POValues[i] = 0.0;
    }
  }

  helikopter2_DW.HILWriteAnalog_Buffer[0] = 0.0;
  helikopter2_DW.HILWriteAnalog_Buffer[1] = 0.0;

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    helikopter2_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 15;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.B = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.P = &rtPTransTable;
  }

  /* Initialize Sizes */
  helikopter2_M->Sizes.numContStates = (5);/* Number of continuous states */
  helikopter2_M->Sizes.numY = (0);     /* Number of model outputs */
  helikopter2_M->Sizes.numU = (0);     /* Number of model inputs */
  helikopter2_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  helikopter2_M->Sizes.numSampTimes = (2);/* Number of sample times */
  helikopter2_M->Sizes.numBlocks = (53);/* Number of blocks */
  helikopter2_M->Sizes.numBlockIO = (10);/* Number of block outputs */
  helikopter2_M->Sizes.numBlockPrms = (172);/* Sum of parameter "widths" */
  return helikopter2_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
