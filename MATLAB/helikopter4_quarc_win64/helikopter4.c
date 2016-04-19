/*
 * helikopter4.c
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
#include "helikopter4.h"
#include "helikopter4_private.h"
#include "helikopter4_dt.h"

/* Block signals (auto storage) */
B_helikopter4_T helikopter4_B;

/* Continuous states */
X_helikopter4_T helikopter4_X;

/* Block states (auto storage) */
DW_helikopter4_T helikopter4_DW;

/* Real-time model */
RT_MODEL_helikopter4_T helikopter4_M_;
RT_MODEL_helikopter4_T *const helikopter4_M = &helikopter4_M_;

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
  helikopter4_derivatives();
  rtsiSetT(si, tnew);
  for (i = 0; i < nXc; i++) {
    *x += h * f0[i];
    x++;
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model output function */
void helikopter4_output(void)
{
  /* local block i/o variables */
  real_T rtb_Add[6];
  real_T rtb_Gain1;
  real_T rtb_HILReadEncoder_o1;
  real_T rtb_HILReadEncoder_o2;
  real_T rtb_HILReadEncoder_o3;
  real_T rtb_Gain[6];
  real_T rtb_Sum;
  real_T tmp[6];
  int32_T i;
  int32_T i_0;
  real_T u0;
  if (rtmIsMajorTimeStep(helikopter4_M)) {
    /* set solver stop time */
    if (!(helikopter4_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&helikopter4_M->solverInfo,
                            ((helikopter4_M->Timing.clockTickH0 + 1) *
        helikopter4_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&helikopter4_M->solverInfo,
                            ((helikopter4_M->Timing.clockTick0 + 1) *
        helikopter4_M->Timing.stepSize0 + helikopter4_M->Timing.clockTickH0 *
        helikopter4_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(helikopter4_M)) {
    helikopter4_M->Timing.t[0] = rtsiGetT(&helikopter4_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(helikopter4_M)) {
    /* S-Function (hil_read_encoder_block): '<S2>/HIL Read Encoder' */

    /* S-Function Block: helikopter4/Heli 3D/HIL Read Encoder (hil_read_encoder_block) */
    {
      t_error result = hil_read_encoder(helikopter4_DW.HILInitialize_Card,
        helikopter4_P.HILReadEncoder_channels, 3,
        &helikopter4_DW.HILReadEncoder_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helikopter4_M, _rt_error_message);
      } else {
        rtb_HILReadEncoder_o1 = helikopter4_DW.HILReadEncoder_Buffer[0];
        rtb_HILReadEncoder_o2 = helikopter4_DW.HILReadEncoder_Buffer[1];
        rtb_HILReadEncoder_o3 = helikopter4_DW.HILReadEncoder_Buffer[2];
      }
    }

    /* Gain: '<S2>/Kalibrer-Elev' */
    helikopter4_B.KalibrerElev = helikopter4_P.KalibElevasjon *
      rtb_HILReadEncoder_o3;

    /* Sum: '<Root>/Add' incorporates:
     *  Constant: '<Root>/Constant'
     */
    helikopter4_B.Add = helikopter4_B.KalibrerElev +
      helikopter4_P.Constant_Value;

    /* Gain: '<S2>/Kalibrer-Pitch' */
    helikopter4_B.KalibrerPitch = helikopter4_P.KalibPitch *
      rtb_HILReadEncoder_o2;
  }

  /* TransferFcn: '<S2>/Vandring Lavpass' */
  helikopter4_B.VandringLavpass = 0.0;
  helikopter4_B.VandringLavpass += helikopter4_P.VandringLavpass_C *
    helikopter4_X.VandringLavpass_CSTATE;
  if (rtmIsMajorTimeStep(helikopter4_M)) {
    /* ToFile: '<Root>/To File' */
    {
      if (!(++helikopter4_DW.ToFile_IWORK.Decimation % 1) &&
          (helikopter4_DW.ToFile_IWORK.Count*2)+1 < 100000000 ) {
        FILE *fp = (FILE *) helikopter4_DW.ToFile_PWORK.FilePtr;
        if (fp != (NULL)) {
          real_T u[2];
          helikopter4_DW.ToFile_IWORK.Decimation = 0;
          u[0] = helikopter4_M->Timing.t[1];
          u[1] = helikopter4_B.VandringLavpass;
          if (fwrite(u, sizeof(real_T), 2, fp) != 2) {
            rtmSetErrorStatus(helikopter4_M,
                              "Error writing to MAT-file helicopter4\\travel4.mat");
            return;
          }

          if (((++helikopter4_DW.ToFile_IWORK.Count)*2)+1 >= 100000000) {
            (void)fprintf(stdout,
                          "*** The ToFile block will stop logging data before\n"
                          "    the simulation has ended, because it has reached\n"
                          "    the maximum number of elements (100000000)\n"
                          "    allowed in MAT-file helicopter4\\travel4.mat.\n");
          }
        }
      }
    }

    /* ToFile: '<Root>/To File1' */
    {
      if (!(++helikopter4_DW.ToFile1_IWORK.Decimation % 1) &&
          (helikopter4_DW.ToFile1_IWORK.Count*2)+1 < 100000000 ) {
        FILE *fp = (FILE *) helikopter4_DW.ToFile1_PWORK.FilePtr;
        if (fp != (NULL)) {
          real_T u[2];
          helikopter4_DW.ToFile1_IWORK.Decimation = 0;
          u[0] = helikopter4_M->Timing.t[1];
          u[1] = helikopter4_B.KalibrerPitch;
          if (fwrite(u, sizeof(real_T), 2, fp) != 2) {
            rtmSetErrorStatus(helikopter4_M,
                              "Error writing to MAT-file helicopter4\\pitch4.mat");
            return;
          }

          if (((++helikopter4_DW.ToFile1_IWORK.Count)*2)+1 >= 100000000) {
            (void)fprintf(stdout,
                          "*** The ToFile block will stop logging data before\n"
                          "    the simulation has ended, because it has reached\n"
                          "    the maximum number of elements (100000000)\n"
                          "    allowed in MAT-file helicopter4\\pitch4.mat.\n");
          }
        }
      }
    }

    /* ToFile: '<Root>/To File2' */
    {
      if (!(++helikopter4_DW.ToFile2_IWORK.Decimation % 1) &&
          (helikopter4_DW.ToFile2_IWORK.Count*2)+1 < 100000000 ) {
        FILE *fp = (FILE *) helikopter4_DW.ToFile2_PWORK.FilePtr;
        if (fp != (NULL)) {
          real_T u[2];
          helikopter4_DW.ToFile2_IWORK.Decimation = 0;
          u[0] = helikopter4_M->Timing.t[1];
          u[1] = helikopter4_B.Add;
          if (fwrite(u, sizeof(real_T), 2, fp) != 2) {
            rtmSetErrorStatus(helikopter4_M,
                              "Error writing to MAT-file helicopter4\\elevation4.mat");
            return;
          }

          if (((++helikopter4_DW.ToFile2_IWORK.Count)*2)+1 >= 100000000) {
            (void)fprintf(stdout,
                          "*** The ToFile block will stop logging data before\n"
                          "    the simulation has ended, because it has reached\n"
                          "    the maximum number of elements (100000000)\n"
                          "    allowed in MAT-file helicopter4\\elevation4.mat.\n");
          }
        }
      }
    }
  }

  /* FromWorkspace: '<Root>/u* Workspace' */
  {
    real_T *pDataValues = (real_T *) helikopter4_DW.uWorkspace_PWORK.DataPtr;
    real_T *pTimeValues = (real_T *) helikopter4_DW.uWorkspace_PWORK.TimePtr;
    int_T currTimeIndex = helikopter4_DW.uWorkspace_IWORK.PrevIndex;
    real_T t = helikopter4_M->Timing.t[0];

    /* Get index */
    if (t <= pTimeValues[0]) {
      currTimeIndex = 0;
    } else if (t >= pTimeValues[100]) {
      currTimeIndex = 99;
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

    helikopter4_DW.uWorkspace_IWORK.PrevIndex = currTimeIndex;

    /* Post output */
    {
      real_T t1 = pTimeValues[currTimeIndex];
      real_T t2 = pTimeValues[currTimeIndex + 1];
      if (t1 == t2) {
        if (t < t1) {
          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 2; ++elIdx) {
              (&helikopter4_B.uWorkspace[0])[elIdx] = pDataValues[currTimeIndex];
              pDataValues += 101;
            }
          }
        } else {
          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 2; ++elIdx) {
              (&helikopter4_B.uWorkspace[0])[elIdx] = pDataValues[currTimeIndex
                + 1];
              pDataValues += 101;
            }
          }
        }
      } else {
        real_T f1 = (t2 - t) / (t2 - t1);
        real_T f2 = 1.0 - f1;
        real_T d1;
        real_T d2;
        int_T TimeIndex= currTimeIndex;

        {
          int_T elIdx;
          for (elIdx = 0; elIdx < 2; ++elIdx) {
            d1 = pDataValues[TimeIndex];
            d2 = pDataValues[TimeIndex + 1];
            (&helikopter4_B.uWorkspace[0])[elIdx] = (real_T) rtInterpolate(d1,
              d2, f1, f2);
            pDataValues += 101;
          }
        }
      }
    }
  }

  if (rtmIsMajorTimeStep(helikopter4_M)) {
    /* ToFile: '<Root>/To File3' */
    {
      if (!(++helikopter4_DW.ToFile3_IWORK.Decimation % 1) &&
          (helikopter4_DW.ToFile3_IWORK.Count*3)+1 < 100000000 ) {
        FILE *fp = (FILE *) helikopter4_DW.ToFile3_PWORK.FilePtr;
        if (fp != (NULL)) {
          real_T u[3];
          helikopter4_DW.ToFile3_IWORK.Decimation = 0;
          u[0] = helikopter4_M->Timing.t[1];
          u[1] = helikopter4_B.uWorkspace[0];
          u[2] = helikopter4_B.uWorkspace[1];
          if (fwrite(u, sizeof(real_T), 3, fp) != 3) {
            rtmSetErrorStatus(helikopter4_M,
                              "Error writing to MAT-file helicopter4\\optinput4.mat");
            return;
          }

          if (((++helikopter4_DW.ToFile3_IWORK.Count)*3)+1 >= 100000000) {
            (void)fprintf(stdout,
                          "*** The ToFile block will stop logging data before\n"
                          "    the simulation has ended, because it has reached\n"
                          "    the maximum number of elements (100000000)\n"
                          "    allowed in MAT-file helicopter4\\optinput4.mat.\n");
          }
        }
      }
    }
  }

  /* FromWorkspace: '<Root>/x* Workspace' */
  {
    real_T *pDataValues = (real_T *) helikopter4_DW.xWorkspace_PWORK.DataPtr;
    real_T *pTimeValues = (real_T *) helikopter4_DW.xWorkspace_PWORK.TimePtr;
    int_T currTimeIndex = helikopter4_DW.xWorkspace_IWORK.PrevIndex;
    real_T t = helikopter4_M->Timing.t[0];

    /* Get index */
    if (t <= pTimeValues[0]) {
      currTimeIndex = 0;
    } else if (t >= pTimeValues[100]) {
      currTimeIndex = 99;
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

    helikopter4_DW.xWorkspace_IWORK.PrevIndex = currTimeIndex;

    /* Post output */
    {
      real_T t1 = pTimeValues[currTimeIndex];
      real_T t2 = pTimeValues[currTimeIndex + 1];
      if (t1 == t2) {
        if (t < t1) {
          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 6; ++elIdx) {
              (&rtb_Add[0])[elIdx] = pDataValues[currTimeIndex];
              pDataValues += 101;
            }
          }
        } else {
          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 6; ++elIdx) {
              (&rtb_Add[0])[elIdx] = pDataValues[currTimeIndex + 1];
              pDataValues += 101;
            }
          }
        }
      } else {
        real_T f1 = (t2 - t) / (t2 - t1);
        real_T f2 = 1.0 - f1;
        real_T d1;
        real_T d2;
        int_T TimeIndex= currTimeIndex;

        {
          int_T elIdx;
          for (elIdx = 0; elIdx < 6; ++elIdx) {
            d1 = pDataValues[TimeIndex];
            d2 = pDataValues[TimeIndex + 1];
            (&rtb_Add[0])[elIdx] = (real_T) rtInterpolate(d1, d2, f1, f2);
            pDataValues += 101;
          }
        }
      }
    }
  }

  if (rtmIsMajorTimeStep(helikopter4_M)) {
    /* Gain: '<S2>/Kalibrer -Vandring' */
    helikopter4_B.KalibrerVandring = helikopter4_P.KalibVandring *
      rtb_HILReadEncoder_o1;
  }

  /* TransferFcn: '<S2>/Transfer Fcn5' */
  rtb_Gain1 = 0.0;
  rtb_Gain1 += helikopter4_P.TransferFcn5_C * helikopter4_X.TransferFcn5_CSTATE;
  rtb_Gain1 += helikopter4_P.TransferFcn5_D * helikopter4_B.KalibrerElev;

  /* SignalConversion: '<Root>/TmpSignal ConversionAtGainInport1' incorporates:
   *  TransferFcn: '<S2>/Transfer Fcn4'
   *  TransferFcn: '<S2>/Vandring Deriv'
   */
  tmp[0] = helikopter4_B.VandringLavpass;
  tmp[1] = helikopter4_P.VandringDeriv_C * helikopter4_X.VandringDeriv_CSTATE +
    helikopter4_P.VandringDeriv_D * helikopter4_B.KalibrerVandring;
  tmp[2] = helikopter4_B.KalibrerPitch;
  tmp[3] = helikopter4_P.TransferFcn4_C * helikopter4_X.TransferFcn4_CSTATE +
    helikopter4_P.TransferFcn4_D * helikopter4_B.KalibrerPitch;
  tmp[4] = helikopter4_B.Add;
  tmp[5] = rtb_Gain1;

  /* Gain: '<Root>/Gain' */
  for (i = 0; i < 6; i++) {
    rtb_Gain[i] = 0.0;
    for (i_0 = 0; i_0 < 6; i_0++) {
      rtb_Gain[i] += helikopter4_P.Gain_Gain[6 * i_0 + i] * tmp[i_0];
    }
  }

  /* End of Gain: '<Root>/Gain' */

  /* Sum: '<S3>/Add2' incorporates:
   *  Constant: '<S3>/Constant'
   */
  rtb_Gain1 = rtb_Gain[0] + helikopter4_P.Constant_Value_b;

  /* Sum: '<S3>/Add' */
  tmp[0] = rtb_Gain1;
  for (i = 0; i < 5; i++) {
    tmp[i + 1] = rtb_Gain[1 + i];
  }

  for (i = 0; i < 6; i++) {
    rtb_Add[i] = tmp[i] - rtb_Add[i];
  }

  /* End of Sum: '<S3>/Add' */

  /* Sum: '<S3>/Add1' incorporates:
   *  Gain: '<S3>/Gain'
   */
  for (i = 0; i < 2; i++) {
    rtb_Sum = 0.0;
    for (i_0 = 0; i_0 < 6; i_0++) {
      rtb_Sum += helikopter4_P.K[(i_0 << 1) + i] * rtb_Add[i_0];
    }

    helikopter4_B.Add1[i] = helikopter4_B.uWorkspace[i] - rtb_Sum;
  }

  /* End of Sum: '<S3>/Add1' */
  if (rtmIsMajorTimeStep(helikopter4_M)) {
    /* ToFile: '<Root>/To File4' */
    {
      if (!(++helikopter4_DW.ToFile4_IWORK.Decimation % 1) &&
          (helikopter4_DW.ToFile4_IWORK.Count*3)+1 < 100000000 ) {
        FILE *fp = (FILE *) helikopter4_DW.ToFile4_PWORK.FilePtr;
        if (fp != (NULL)) {
          real_T u[3];
          helikopter4_DW.ToFile4_IWORK.Decimation = 0;
          u[0] = helikopter4_M->Timing.t[1];
          u[1] = helikopter4_B.Add1[0];
          u[2] = helikopter4_B.Add1[1];
          if (fwrite(u, sizeof(real_T), 3, fp) != 3) {
            rtmSetErrorStatus(helikopter4_M,
                              "Error writing to MAT-file helicopter4\\input4.mat");
            return;
          }

          if (((++helikopter4_DW.ToFile4_IWORK.Count)*3)+1 >= 100000000) {
            (void)fprintf(stdout,
                          "*** The ToFile block will stop logging data before\n"
                          "    the simulation has ended, because it has reached\n"
                          "    the maximum number of elements (100000000)\n"
                          "    allowed in MAT-file helicopter4\\input4.mat.\n");
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
  if (helikopter4_X.Integrator_CSTATE >= helikopter4_P.Integrator_UpperSat ) {
    helikopter4_X.Integrator_CSTATE = helikopter4_P.Integrator_UpperSat;
  } else if (helikopter4_X.Integrator_CSTATE <=
             (helikopter4_P.Integrator_LowerSat) ) {
    helikopter4_X.Integrator_CSTATE = (helikopter4_P.Integrator_LowerSat);
  }

  rtb_Gain1 = helikopter4_X.Integrator_CSTATE;

  /* Sum: '<S1>/Sum' */
  rtb_Sum = helikopter4_B.Add1[1] - rtb_Gain[4];

  /* Gain: '<S1>/K_ei' */
  helikopter4_B.K_ei = helikopter4_P.K_ei * rtb_Sum;

  /* Sum: '<S1>/Sum1' incorporates:
   *  Gain: '<S1>/K_ed'
   *  Gain: '<S1>/K_ep'
   */
  rtb_Gain1 = (helikopter4_P.K_ep * rtb_Sum + rtb_Gain1) + -helikopter4_P.K_ed *
    rtb_Gain[5];

  /* Saturate: '<S1>/Saturation' */
  if (rtb_Gain1 > helikopter4_P.Saturation_UpperSat) {
    rtb_Gain1 = helikopter4_P.Saturation_UpperSat;
  } else {
    if (rtb_Gain1 < helikopter4_P.Saturation_LowerSat) {
      rtb_Gain1 = helikopter4_P.Saturation_LowerSat;
    }
  }

  /* End of Saturate: '<S1>/Saturation' */
  if (rtmIsMajorTimeStep(helikopter4_M)) {
  }

  /* Saturate: '<S4>/Saturation' */
  if (helikopter4_B.Add1[0] > helikopter4_P.Saturation_UpperSat_d) {
    rtb_Sum = helikopter4_P.Saturation_UpperSat_d;
  } else if (helikopter4_B.Add1[0] < helikopter4_P.Saturation_LowerSat_n) {
    rtb_Sum = helikopter4_P.Saturation_LowerSat_n;
  } else {
    rtb_Sum = helikopter4_B.Add1[0];
  }

  /* Sum: '<S4>/Sum' incorporates:
   *  Gain: '<S4>/K_pd'
   *  Gain: '<S4>/K_pp'
   *  Saturate: '<S4>/Saturation'
   *  Sum: '<S4>/Sum1'
   */
  rtb_Sum = 0.3 * helikopter4_P.K_pp * (rtb_Sum - rtb_Gain[2]) -
    helikopter4_P.K_pd * rtb_Gain[3];

  /* Gain: '<S5>/Gain2' incorporates:
   *  Sum: '<S5>/Sum4'
   */
  u0 = (rtb_Gain1 - rtb_Sum) * helikopter4_P.V_b_eq;

  /* Saturate: '<S2>/Sat B' */
  if (u0 > helikopter4_P.SatB_UpperSat) {
    helikopter4_B.SatB = helikopter4_P.SatB_UpperSat;
  } else if (u0 < helikopter4_P.SatB_LowerSat) {
    helikopter4_B.SatB = helikopter4_P.SatB_LowerSat;
  } else {
    helikopter4_B.SatB = u0;
  }

  /* End of Saturate: '<S2>/Sat B' */
  if (rtmIsMajorTimeStep(helikopter4_M)) {
  }

  /* Gain: '<S5>/Gain1' incorporates:
   *  Sum: '<S5>/Sum3'
   */
  rtb_Gain1 = (rtb_Sum + rtb_Gain1) * helikopter4_P.V_f_eq;

  /* Saturate: '<S2>/Sat' */
  if (rtb_Gain1 > helikopter4_P.Sat_UpperSat) {
    helikopter4_B.Sat = helikopter4_P.Sat_UpperSat;
  } else if (rtb_Gain1 < helikopter4_P.Sat_LowerSat) {
    helikopter4_B.Sat = helikopter4_P.Sat_LowerSat;
  } else {
    helikopter4_B.Sat = rtb_Gain1;
  }

  /* End of Saturate: '<S2>/Sat' */
  if (rtmIsMajorTimeStep(helikopter4_M)) {
  }

  /* Sum: '<S2>/Add' incorporates:
   *  Constant: '<S2>/elevation'
   */
  helikopter4_B.Add_j = helikopter4_B.SatB - helikopter4_P.elevation_Value;
  if (rtmIsMajorTimeStep(helikopter4_M)) {
    /* S-Function (hil_write_analog_block): '<S2>/HIL Write Analog' */

    /* S-Function Block: helikopter4/Heli 3D/HIL Write Analog (hil_write_analog_block) */
    {
      t_error result;
      helikopter4_DW.HILWriteAnalog_Buffer[0] = helikopter4_B.Add_j;
      helikopter4_DW.HILWriteAnalog_Buffer[1] = helikopter4_B.Sat;
      result = hil_write_analog(helikopter4_DW.HILInitialize_Card,
        helikopter4_P.HILWriteAnalog_channels, 2,
        &helikopter4_DW.HILWriteAnalog_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helikopter4_M, _rt_error_message);
      }
    }
  }
}

/* Model update function */
void helikopter4_update(void)
{
  if (rtmIsMajorTimeStep(helikopter4_M)) {
    rt_ertODEUpdateContinuousStates(&helikopter4_M->solverInfo);
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
  if (!(++helikopter4_M->Timing.clockTick0)) {
    ++helikopter4_M->Timing.clockTickH0;
  }

  helikopter4_M->Timing.t[0] = rtsiGetSolverStopTime(&helikopter4_M->solverInfo);

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
    if (!(++helikopter4_M->Timing.clockTick1)) {
      ++helikopter4_M->Timing.clockTickH1;
    }

    helikopter4_M->Timing.t[1] = helikopter4_M->Timing.clockTick1 *
      helikopter4_M->Timing.stepSize1 + helikopter4_M->Timing.clockTickH1 *
      helikopter4_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Derivatives for root system: '<Root>' */
void helikopter4_derivatives(void)
{
  XDot_helikopter4_T *_rtXdot;
  _rtXdot = ((XDot_helikopter4_T *) helikopter4_M->ModelData.derivs);

  /* Derivatives for TransferFcn: '<S2>/Vandring Lavpass' */
  _rtXdot->VandringLavpass_CSTATE = 0.0;
  _rtXdot->VandringLavpass_CSTATE += helikopter4_P.VandringLavpass_A *
    helikopter4_X.VandringLavpass_CSTATE;
  _rtXdot->VandringLavpass_CSTATE += helikopter4_B.KalibrerVandring;

  /* Derivatives for TransferFcn: '<S2>/Vandring Deriv' */
  _rtXdot->VandringDeriv_CSTATE = 0.0;
  _rtXdot->VandringDeriv_CSTATE += helikopter4_P.VandringDeriv_A *
    helikopter4_X.VandringDeriv_CSTATE;
  _rtXdot->VandringDeriv_CSTATE += helikopter4_B.KalibrerVandring;

  /* Derivatives for TransferFcn: '<S2>/Transfer Fcn4' */
  _rtXdot->TransferFcn4_CSTATE = 0.0;
  _rtXdot->TransferFcn4_CSTATE += helikopter4_P.TransferFcn4_A *
    helikopter4_X.TransferFcn4_CSTATE;
  _rtXdot->TransferFcn4_CSTATE += helikopter4_B.KalibrerPitch;

  /* Derivatives for TransferFcn: '<S2>/Transfer Fcn5' */
  _rtXdot->TransferFcn5_CSTATE = 0.0;
  _rtXdot->TransferFcn5_CSTATE += helikopter4_P.TransferFcn5_A *
    helikopter4_X.TransferFcn5_CSTATE;
  _rtXdot->TransferFcn5_CSTATE += helikopter4_B.KalibrerElev;

  /* Derivatives for Integrator: '<S1>/Integrator' */
  {
    boolean_T lsat;
    boolean_T usat;
    lsat = ( helikopter4_X.Integrator_CSTATE <=
            (helikopter4_P.Integrator_LowerSat) );
    usat = ( helikopter4_X.Integrator_CSTATE >=
            helikopter4_P.Integrator_UpperSat );
    if ((!lsat && !usat) ||
        (lsat && (helikopter4_B.K_ei > 0)) ||
        (usat && (helikopter4_B.K_ei < 0)) ) {
      ((XDot_helikopter4_T *) helikopter4_M->ModelData.derivs)
        ->Integrator_CSTATE = helikopter4_B.K_ei;
    } else {
      /* in saturation */
      ((XDot_helikopter4_T *) helikopter4_M->ModelData.derivs)
        ->Integrator_CSTATE = 0.0;
    }
  }
}

/* Model initialize function */
void helikopter4_initialize(void)
{
  /* Start for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: helikopter4/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q8_usb", "0", &helikopter4_DW.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helikopter4_M, _rt_error_message);
      return;
    }

    is_switching = false;
    result = hil_set_card_specific_options(helikopter4_DW.HILInitialize_Card,
      "update_rate=normal;decimation=1", 32);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helikopter4_M, _rt_error_message);
      return;
    }

    result = hil_watchdog_clear(helikopter4_DW.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helikopter4_M, _rt_error_message);
      return;
    }

    if ((helikopter4_P.HILInitialize_set_analog_input_ && !is_switching) ||
        (helikopter4_P.HILInitialize_set_analog_inpu_m && is_switching)) {
      {
        int_T i1;
        real_T *dw_AIMinimums = &helikopter4_DW.HILInitialize_AIMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMinimums[i1] = helikopter4_P.HILInitialize_analog_input_mini;
        }
      }

      {
        int_T i1;
        real_T *dw_AIMaximums = &helikopter4_DW.HILInitialize_AIMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMaximums[i1] = helikopter4_P.HILInitialize_analog_input_maxi;
        }
      }

      result = hil_set_analog_input_ranges(helikopter4_DW.HILInitialize_Card,
        helikopter4_P.HILInitialize_analog_input_chan, 8U,
        &helikopter4_DW.HILInitialize_AIMinimums[0],
        &helikopter4_DW.HILInitialize_AIMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helikopter4_M, _rt_error_message);
        return;
      }
    }

    if ((helikopter4_P.HILInitialize_set_analog_output && !is_switching) ||
        (helikopter4_P.HILInitialize_set_analog_outp_b && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOMinimums = &helikopter4_DW.HILInitialize_AOMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMinimums[i1] = helikopter4_P.HILInitialize_analog_output_min;
        }
      }

      {
        int_T i1;
        real_T *dw_AOMaximums = &helikopter4_DW.HILInitialize_AOMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMaximums[i1] = helikopter4_P.HILInitialize_analog_output_max;
        }
      }

      result = hil_set_analog_output_ranges(helikopter4_DW.HILInitialize_Card,
        helikopter4_P.HILInitialize_analog_output_cha, 8U,
        &helikopter4_DW.HILInitialize_AOMinimums[0],
        &helikopter4_DW.HILInitialize_AOMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helikopter4_M, _rt_error_message);
        return;
      }
    }

    if ((helikopter4_P.HILInitialize_set_analog_outp_e && !is_switching) ||
        (helikopter4_P.HILInitialize_set_analog_outp_j && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &helikopter4_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = helikopter4_P.HILInitialize_initial_analog_ou;
        }
      }

      result = hil_write_analog(helikopter4_DW.HILInitialize_Card,
        helikopter4_P.HILInitialize_analog_output_cha, 8U,
        &helikopter4_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helikopter4_M, _rt_error_message);
        return;
      }
    }

    if (helikopter4_P.HILInitialize_set_analog_outp_p) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &helikopter4_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = helikopter4_P.HILInitialize_watchdog_analog_o;
        }
      }

      result = hil_watchdog_set_analog_expiration_state
        (helikopter4_DW.HILInitialize_Card,
         helikopter4_P.HILInitialize_analog_output_cha, 8U,
         &helikopter4_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helikopter4_M, _rt_error_message);
        return;
      }
    }

    if ((helikopter4_P.HILInitialize_set_encoder_param && !is_switching) ||
        (helikopter4_P.HILInitialize_set_encoder_par_m && is_switching)) {
      {
        int_T i1;
        int32_T *dw_QuadratureModes =
          &helikopter4_DW.HILInitialize_QuadratureModes[0];
        for (i1=0; i1 < 8; i1++) {
          dw_QuadratureModes[i1] = helikopter4_P.HILInitialize_quadrature;
        }
      }

      result = hil_set_encoder_quadrature_mode(helikopter4_DW.HILInitialize_Card,
        helikopter4_P.HILInitialize_encoder_channels, 8U,
        (t_encoder_quadrature_mode *)
        &helikopter4_DW.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helikopter4_M, _rt_error_message);
        return;
      }
    }

    if ((helikopter4_P.HILInitialize_set_encoder_count && !is_switching) ||
        (helikopter4_P.HILInitialize_set_encoder_cou_k && is_switching)) {
      {
        int_T i1;
        int32_T *dw_InitialEICounts =
          &helikopter4_DW.HILInitialize_InitialEICounts[0];
        for (i1=0; i1 < 8; i1++) {
          dw_InitialEICounts[i1] = helikopter4_P.HILInitialize_initial_encoder_c;
        }
      }

      result = hil_set_encoder_counts(helikopter4_DW.HILInitialize_Card,
        helikopter4_P.HILInitialize_encoder_channels, 8U,
        &helikopter4_DW.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helikopter4_M, _rt_error_message);
        return;
      }
    }

    if ((helikopter4_P.HILInitialize_set_pwm_params_at && !is_switching) ||
        (helikopter4_P.HILInitialize_set_pwm_params__f && is_switching)) {
      uint32_T num_duty_cycle_modes = 0;
      uint32_T num_frequency_modes = 0;

      {
        int_T i1;
        int32_T *dw_POModeValues = &helikopter4_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = helikopter4_P.HILInitialize_pwm_modes;
        }
      }

      result = hil_set_pwm_mode(helikopter4_DW.HILInitialize_Card,
        helikopter4_P.HILInitialize_pwm_channels, 8U, (t_pwm_mode *)
        &helikopter4_DW.HILInitialize_POModeValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helikopter4_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        const uint32_T *p_HILInitialize_pwm_channels =
          helikopter4_P.HILInitialize_pwm_channels;
        int32_T *dw_POModeValues = &helikopter4_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          if (dw_POModeValues[i1] == PWM_DUTY_CYCLE_MODE || dw_POModeValues[i1] ==
              PWM_ONE_SHOT_MODE || dw_POModeValues[i1] == PWM_TIME_MODE) {
            helikopter4_DW.HILInitialize_POSortedChans[num_duty_cycle_modes] =
              p_HILInitialize_pwm_channels[i1];
            helikopter4_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes] =
              helikopter4_P.HILInitialize_pwm_frequency;
            num_duty_cycle_modes++;
          } else {
            helikopter4_DW.HILInitialize_POSortedChans[7U - num_frequency_modes]
              = p_HILInitialize_pwm_channels[i1];
            helikopter4_DW.HILInitialize_POSortedFreqs[7U - num_frequency_modes]
              = helikopter4_P.HILInitialize_pwm_frequency;
            num_frequency_modes++;
          }
        }
      }

      if (num_duty_cycle_modes > 0) {
        result = hil_set_pwm_frequency(helikopter4_DW.HILInitialize_Card,
          &helikopter4_DW.HILInitialize_POSortedChans[0], num_duty_cycle_modes,
          &helikopter4_DW.HILInitialize_POSortedFreqs[0]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(helikopter4_M, _rt_error_message);
          return;
        }
      }

      if (num_frequency_modes > 0) {
        result = hil_set_pwm_duty_cycle(helikopter4_DW.HILInitialize_Card,
          &helikopter4_DW.HILInitialize_POSortedChans[num_duty_cycle_modes],
          num_frequency_modes,
          &helikopter4_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(helikopter4_M, _rt_error_message);
          return;
        }
      }

      {
        int_T i1;
        int32_T *dw_POModeValues = &helikopter4_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = helikopter4_P.HILInitialize_pwm_configuration;
        }
      }

      {
        int_T i1;
        int32_T *dw_POAlignValues = &helikopter4_DW.HILInitialize_POAlignValues
          [0];
        for (i1=0; i1 < 8; i1++) {
          dw_POAlignValues[i1] = helikopter4_P.HILInitialize_pwm_alignment;
        }
      }

      {
        int_T i1;
        int32_T *dw_POPolarityVals =
          &helikopter4_DW.HILInitialize_POPolarityVals[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POPolarityVals[i1] = helikopter4_P.HILInitialize_pwm_polarity;
        }
      }

      result = hil_set_pwm_configuration(helikopter4_DW.HILInitialize_Card,
        helikopter4_P.HILInitialize_pwm_channels, 8U,
        (t_pwm_configuration *) &helikopter4_DW.HILInitialize_POModeValues[0],
        (t_pwm_alignment *) &helikopter4_DW.HILInitialize_POAlignValues[0],
        (t_pwm_polarity *) &helikopter4_DW.HILInitialize_POPolarityVals[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helikopter4_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        real_T *dw_POSortedFreqs = &helikopter4_DW.HILInitialize_POSortedFreqs[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POSortedFreqs[i1] = helikopter4_P.HILInitialize_pwm_leading_deadb;
        }
      }

      {
        int_T i1;
        real_T *dw_POValues = &helikopter4_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helikopter4_P.HILInitialize_pwm_trailing_dead;
        }
      }

      result = hil_set_pwm_deadband(helikopter4_DW.HILInitialize_Card,
        helikopter4_P.HILInitialize_pwm_channels, 8U,
        &helikopter4_DW.HILInitialize_POSortedFreqs[0],
        &helikopter4_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helikopter4_M, _rt_error_message);
        return;
      }
    }

    if ((helikopter4_P.HILInitialize_set_pwm_outputs_a && !is_switching) ||
        (helikopter4_P.HILInitialize_set_pwm_outputs_g && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &helikopter4_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helikopter4_P.HILInitialize_initial_pwm_outpu;
        }
      }

      result = hil_write_pwm(helikopter4_DW.HILInitialize_Card,
        helikopter4_P.HILInitialize_pwm_channels, 8U,
        &helikopter4_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helikopter4_M, _rt_error_message);
        return;
      }
    }

    if (helikopter4_P.HILInitialize_set_pwm_outputs_o) {
      {
        int_T i1;
        real_T *dw_POValues = &helikopter4_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helikopter4_P.HILInitialize_watchdog_pwm_outp;
        }
      }

      result = hil_watchdog_set_pwm_expiration_state
        (helikopter4_DW.HILInitialize_Card,
         helikopter4_P.HILInitialize_pwm_channels, 8U,
         &helikopter4_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helikopter4_M, _rt_error_message);
        return;
      }
    }
  }

  /* Start for ToFile: '<Root>/To File' */
  {
    char fileName[509] = "helicopter4\\travel4.mat";
    FILE *fp = (NULL);
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(helikopter4_M,
                        "Error creating .mat file helicopter4\\travel4.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp,2,0,"travel4")) {
      rtmSetErrorStatus(helikopter4_M,
                        "Error writing mat file header to file helicopter4\\travel4.mat");
      return;
    }

    helikopter4_DW.ToFile_IWORK.Count = 0;
    helikopter4_DW.ToFile_IWORK.Decimation = -1;
    helikopter4_DW.ToFile_PWORK.FilePtr = fp;
  }

  /* Start for ToFile: '<Root>/To File1' */
  {
    char fileName[509] = "helicopter4\\pitch4.mat";
    FILE *fp = (NULL);
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(helikopter4_M,
                        "Error creating .mat file helicopter4\\pitch4.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp,2,0,"pitch4")) {
      rtmSetErrorStatus(helikopter4_M,
                        "Error writing mat file header to file helicopter4\\pitch4.mat");
      return;
    }

    helikopter4_DW.ToFile1_IWORK.Count = 0;
    helikopter4_DW.ToFile1_IWORK.Decimation = -1;
    helikopter4_DW.ToFile1_PWORK.FilePtr = fp;
  }

  /* Start for ToFile: '<Root>/To File2' */
  {
    char fileName[509] = "helicopter4\\elevation4.mat";
    FILE *fp = (NULL);
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(helikopter4_M,
                        "Error creating .mat file helicopter4\\elevation4.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp,2,0,"elevation4")) {
      rtmSetErrorStatus(helikopter4_M,
                        "Error writing mat file header to file helicopter4\\elevation4.mat");
      return;
    }

    helikopter4_DW.ToFile2_IWORK.Count = 0;
    helikopter4_DW.ToFile2_IWORK.Decimation = -1;
    helikopter4_DW.ToFile2_PWORK.FilePtr = fp;
  }

  /* Start for FromWorkspace: '<Root>/u* Workspace' */
  {
    static real_T pTimeValues0[] = { 0.0, 0.25, 0.5, 0.75, 1.0, 1.25, 1.5, 1.75,
      2.0, 2.25, 2.5, 2.75, 3.0, 3.25, 3.5, 3.75, 4.0, 4.25, 4.5, 4.75, 5.0,
      5.25, 5.5, 5.75, 6.0, 6.25, 6.5, 6.75, 7.0, 7.25, 7.5, 7.75, 8.0, 8.25,
      8.5, 8.75, 9.0, 9.25, 9.5, 9.75, 10.0, 10.25, 10.5, 10.75, 11.0, 11.25,
      11.5, 11.75, 12.0, 12.25, 12.5, 12.75, 13.0, 13.25, 13.5, 13.75, 14.0,
      14.25, 14.5, 14.75, 15.0, 15.25, 15.5, 15.75, 16.0, 16.25, 16.5, 16.75,
      17.0, 17.25, 17.5, 17.75, 18.0, 18.25, 18.5, 18.75, 19.0, 19.25, 19.5,
      19.75, 20.0, 20.25, 20.5, 20.75, 21.0, 21.25, 21.5, 21.75, 22.0, 22.25,
      22.5, 22.75, 23.0, 23.25, 23.5, 23.75, 24.0, 24.25, 24.5, 24.75, 25.0 } ;

    static real_T pDataValues0[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.058766219099568993, 0.073751041536672612, 0.20464669067601096,
      0.33553454050375842, 0.40767708044884016, 0.52356148409019687,
      0.52357556696089091, 0.52357159525064034, 0.52356380480567466,
      0.5235575032874481, 0.52355159693693409, 0.52354295788450411,
      0.52352944860333306, 0.52351051956633221, 0.52349100363370116,
      0.52346729310211138, 0.52337427272607218, 0.50702316207429921,
      0.46052763781311712, 0.41318802601088422, 0.28272550176064892,
      0.15218157529177223, 0.02174471828037405, -0.10836719631312135,
      -0.23496568218239561, -0.338232702314089, -0.43425288679196006,
      -0.49092798118317, -0.50456895274485525, -0.52002501064946138,
      -0.516441448156887, -0.51706821949822324, -0.51776389431383052,
      -0.512004080940788, -0.50172194845425944, -0.49006616976257666,
      -0.467510531415811, -0.44200326671084045, -0.40790168733484666,
      -0.37929689549288625, -0.342974373166515, -0.31362524989997032,
      -0.27875402550933265, -0.25052299017333968, -0.21943326171236988,
      -0.19675461104723541, -0.16744757592372758, -0.14100318273159462,
      -0.11102460653048082, -0.095116131607589027, -0.066081951397259892,
      -0.050985564773249538, -0.025072230940733433, 0.00025211867844729261,
      0.023437242340765409, 0.054037587720332417, 0.068564753304439827,
      0.079133817675984569, 0.10480473291951367, 0.11162081643041841,
      0.11162081643041841, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0091586606429230159, 0.0087351345103652382, 0.00896829055231694,
      0.006364936584061026, -0.0044198604382818191, 0.00898628162581064,
      0.010460239047499494, -0.0019436162790927483, -0.0050164087761628631,
      -0.010073839800028237, 0.018360706390263225, 0.0026851318240763851,
      0.017169358615724783, 0.014579362269312758, 0.20332975594454256,
      -0.046267254712004921, 1.0455486753305678, -0.79035557437335746,
      0.63406178479061992, -0.32197496084696425, -0.25695508304097159,
      0.21435256812123052, 0.13280769666696843, 0.012502833657412369,
      0.033082523101820263, -0.025833060091801183, 0.016269976951922657,
      -0.00032328082879799004, 0.010427859735668767, 0.013515036177678892,
      0.01712951635663959, -0.023478053907843376, 0.008167369264095314,
      -0.00907369860610345, 0.015523113129520164, 0.00065884895545624707,
      0.019363871224372858, 0.007516983385046013, 0.005743577914968585,
      0.0016170006055779872, -0.0062838773174147683, 0.0096383127601185,
      0.011182087170080322, 0.017557304795237719, 0.00086501856526086975,
      0.013334583731763487, 0.0053057819105816221, 0.00095735990504615788,
      0.0073019112408816917, 0.0049817644544781856, -0.0014366232116252828,
      0.0090539345820721609, 0.010712937134851289, 0.012097266819739216,
      -0.0037956914238078733, -0.0031185913332274816, 0.00031215755297890515,
      -0.0061690572987314974, 0.01068174590072651, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0 } ;

    helikopter4_DW.uWorkspace_PWORK.TimePtr = (void *) pTimeValues0;
    helikopter4_DW.uWorkspace_PWORK.DataPtr = (void *) pDataValues0;
    helikopter4_DW.uWorkspace_IWORK.PrevIndex = 0;
  }

  /* Start for ToFile: '<Root>/To File3' */
  {
    char fileName[509] = "helicopter4\\optinput4.mat";
    FILE *fp = (NULL);
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(helikopter4_M,
                        "Error creating .mat file helicopter4\\optinput4.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp,3,0,"optinput4")) {
      rtmSetErrorStatus(helikopter4_M,
                        "Error writing mat file header to file helicopter4\\optinput4.mat");
      return;
    }

    helikopter4_DW.ToFile3_IWORK.Count = 0;
    helikopter4_DW.ToFile3_IWORK.Decimation = -1;
    helikopter4_DW.ToFile3_PWORK.FilePtr = fp;
  }

  /* Start for FromWorkspace: '<Root>/x* Workspace' */
  {
    static real_T pTimeValues0[] = { 0.0, 0.25, 0.5, 0.75, 1.0, 1.25, 1.5, 1.75,
      2.0, 2.25, 2.5, 2.75, 3.0, 3.25, 3.5, 3.75, 4.0, 4.25, 4.5, 4.75, 5.0,
      5.25, 5.5, 5.75, 6.0, 6.25, 6.5, 6.75, 7.0, 7.25, 7.5, 7.75, 8.0, 8.25,
      8.5, 8.75, 9.0, 9.25, 9.5, 9.75, 10.0, 10.25, 10.5, 10.75, 11.0, 11.25,
      11.5, 11.75, 12.0, 12.25, 12.5, 12.75, 13.0, 13.25, 13.5, 13.75, 14.0,
      14.25, 14.5, 14.75, 15.0, 15.25, 15.5, 15.75, 16.0, 16.25, 16.5, 16.75,
      17.0, 17.25, 17.5, 17.75, 18.0, 18.25, 18.5, 18.75, 19.0, 19.25, 19.5,
      19.75, 20.0, 20.25, 20.5, 20.75, 21.0, 21.25, 21.5, 21.75, 22.0, 22.25,
      22.5, 22.75, 23.0, 23.25, 23.5, 23.75, 24.0, 24.25, 24.5, 24.75, 25.0 } ;

    static real_T pDataValues0[] = { 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926534741416, 3.1415926533715384,
      3.141592653358142, 3.1395736269033874, 3.1335165674765637,
      3.1214025170589967, 3.1012127861075194, 3.0729471060330673,
      3.0366055807701904, 2.9921883854794102, 2.9396956624374404,
      2.87912754524615, 2.8104841765340702, 2.7337656576318317,
      2.6489719980611968, 2.5561031474077729, 2.4551590535432473,
      2.3461394659381143, 2.2290378555750427, 2.103863697088725,
      1.9711816107208768, 1.8330053287724877, 1.6913522841145094,
      1.548245308443879, 1.4056838872681996, 1.2656749145424602,
      1.1302148845940438, 1.0011799415684641, 0.87957657728814209,
      0.76575277993842883, 0.659930175163015, 0.56205689750582488,
      0.47218896646965353, 0.39034793866560796, 0.31646136440971728,
      0.25045692771307382, 0.19222591490693333, 0.14147678161056709,
      0.09780633053270954, 0.060714297306130809, 0.029746912582563404,
      0.0043812259897207193, -0.015860108577976442, -0.031549165612744366,
      -0.043178958549582855, -0.051186478445751832, -0.055894784921536482,
      -0.057750774346901942, -0.057229343504672132, -0.05480972212721108,
      -0.050820787784603146, -0.045592282958996054, -0.039267746886334713,
      -0.032301250341703912, -0.025266621634528079, -0.018586046376044454,
      -0.012312288317575831, -0.0064484980402834454, -0.0019442842610067907,
      8.4036892694742229E-18, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 1.5888126189799725E-10, 6.380449694417656E-10, -0.0080761053152586613,
      -0.024228239017036975, -0.048456210462264684, -0.080758955836153043,
      -0.11306281256555717, -0.14536632836946, -0.17766927394883036,
      -0.20997184335811886, -0.24227410916807185, -0.27457599387594434,
      -0.30687747713183605, -0.33917855392190738, -0.37147892909142477,
      -0.40377803567693304, -0.43607626989922982, -0.46837453577665561,
      -0.50066132549880316, -0.53069260951968744, -0.55267266834311879,
      -0.56659341179886169, -0.57245765127171977, -0.57027499148798522,
      -0.5600613625911014, -0.54186001058686128, -0.51615384382890828,
      -0.4864225038503982, -0.45530047349791897, -0.42329321436927858,
      -0.39149444112311638, -0.35947228719962959, -0.32736431824561363,
      -0.29554635979713545, -0.26401776006808519, -0.23292405126873483,
      -0.20299653132698786, -0.1746818030470656, -0.14836813230648216,
      -0.12386953865819737, -0.10146274628987283, -0.08096533824549329,
      -0.06275622813189187, -0.0465191717454795, -0.032030079584220675,
      -0.018833225903039454, -0.0074239577014343413, 0.0020857233689176957,
      0.00967848550984819, 0.015955737370431235, 0.0209140193024266,
      0.025298144290648583, 0.027865986178519438, 0.028138514828706197,
      0.026722301033934134, 0.025095032233874548, 0.023455161109167975,
      0.018016855117110514, 0.0077771370440232182, 1.7008575818290299E-15, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 7.5960927936680092E-10,
      0.13089715166171945, 0.26179305226561062, 0.39268591783978662,
      0.52356163094413977, 0.52357996294611131, 0.52357495829663858,
      0.52356643768021593, 0.5235611121993442, 0.52355659789236886,
      0.52354970726258776, 0.52354033623232987, 0.52352772930676483,
      0.523506771760607, 0.52347387826026748, 0.52344728581417654,
      0.52343939015058449, 0.52327873717587292, 0.4867535758045744,
      0.35629398924324296, 0.22569961798634083, 0.095132828333180153,
      -0.035327967715333808, -0.16552660676275055, -0.29501490210257358,
      -0.41666536011238953, -0.48190874196174882, -0.50444653401034223,
      -0.518789088405968, -0.51540445499905618, -0.519020486466472,
      -0.52040823829287286, -0.51570585008537662, -0.51101489495331065,
      -0.50396568980618706, -0.48506392719540659, -0.45892378420367591,
      -0.42649070584038745, -0.39707201276571119, -0.36316819595972838,
      -0.33222098710869069, -0.29513236585693375, -0.26316941546608374,
      -0.23483849681006422, -0.21389395875038569, -0.18492086075348865,
      -0.15413244549111829, -0.12306311726255544, -0.10174139101487892,
      -0.0803635909478161, -0.0710576832919227, -0.041619455680046491,
      -0.0044171310225834069, 0.022953923888717049, 0.026374693089080779,
      0.026578950950528049, 0.088143797428664142, 0.16596484949670134,
      0.12605145668114512, -2.6511867650206658E-14, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.52358861042490856, 0.52358359733761106,
      0.52357146604118188, 0.52350285420855958, 7.3333612740898382E-5,
      -2.0008032079203482E-5, -3.4064947548122713E-5, -2.1277592241877498E-5,
      -1.8032780497464865E-5, -2.7556444810897081E-5, -3.7530426796869108E-5,
      -5.0564519972183392E-5, -8.4108012661006211E-5, -0.00013189476468798708,
      -0.00010680012251856545, -3.15695998155149E-5, -0.00064222803203582322,
      -0.14609992087751905, -0.52183714951258309, -0.52237714226463394,
      -0.52226679241053131, -0.52184392377762545, -0.52079533891711149,
      -0.51795376212990485, -0.48660215540978491, -0.26097357284508638,
      -0.090151073116562216, -0.057370075051879008, 0.013538661240083991,
      -0.014464035189503769, -0.0055509523812180142, 0.018809582167527521,
      0.018763834543177631, 0.028196826676654626, 0.07560705287700771,
      0.10456057283198213, 0.12973231372368224, 0.11767477246526477,
      0.13561526713541672, 0.12378883553847442, 0.14835448490732123,
      0.12785180161142826, 0.11332367461976751, 0.083778152243284817,
      0.11589239195268933, 0.12315366110819509, 0.12427731285739305,
      0.08528690502406848, 0.085511200263953535, 0.0372236306055962,
      0.11775291048067908, 0.14880929859100586, 0.10948421967213978,
      0.013683076796108916, 0.00081703144463000064, 0.24625938589589877,
      0.31128420831065295, -0.15965357130224481, -0.50420582670808489,
      4.703186049167383E-13, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 4.2173567518755812E-11, 0.0013918032321430462, 0.0034342273832763215,
      0.0056348069411716033, 0.0072106329939536336, 0.0064921838507102231,
      0.0063929460022839387, 0.0069449701129618438, 0.0059616657225803633,
      0.0036387946245309195, 8.6706779727831387E-6, 0.00038121773284698583,
      0.00097987090484715281, 0.0038398156075352546, 0.007377853088966619,
      0.039514735708052168, 0.04787747683431736, 0.20506529051319511,
      0.15843583623782506, 0.19969433688097488, 0.14791211877188967,
      0.05194884959799409, 0.012772217277694935, 0.004871973229372795,
      0.00076324472805748219, 0.0029367830902561065, 1.2828715833785048E-5,
      0.00053964976220423355, 0.00076172715212617561, 0.0023801782385424117,
      0.0051502064314606988, 0.00881463914334044, 0.0063465326085288013,
      0.0049802468163922409, 0.0019350107060767824, 0.0019727948649347531,
      0.0017982709328407803, 0.0043514649827672541, 0.0065321136762386718,
      0.0078638871422573274, 0.0078011027204954965, 0.0056188734902285122,
      0.004777034794946425, 0.0051899924947915715, 0.0073442966724355753,
      0.0077937349849285858, 0.0089349344350362243, 0.0091430956092769054,
      0.0080377115069454885, 0.0071900681956219908, 0.0062902263866082631,
      0.0045170071153122849, 0.00402607672927641, 0.0047154505863199348,
      0.0062961332794385823, 0.0058147424482235827, 0.0041367313060003937,
      0.0024385164249794439, 1.6053863025437881E-11, 1.2540833594654126E-11, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0055672126301299684,
      0.0081696964134195, 0.008802317983026893, 0.0063033041470255662,
      -0.0028737953789856312, -0.00039694499500556317, 0.0022081189221711613,
      -0.0039331593958023287, -0.0092913799730918612, -0.014520435721328653,
      0.0014897277300969965, 0.0023924906926450834, 0.011434528268918146,
      0.014141716147753978, 0.12852904262295048, 0.033420310174086691,
      0.62870308847859246, -0.18655531682102736, 0.16494542057067804,
      -0.20727638239365281, -0.38404568161261804, -0.15689215371858242,
      -0.0314505126003569, -0.01631964341897783, 0.0087690237877534952,
      -0.011656065248149685, 0.0021226955025861207, 0.00089037671386786067,
      0.0064705503140744, 0.011077334766735204, 0.01465644063155345,
      -0.0098728607511705119, -0.0054652465196512578, -0.01218095477901647,
      0.00015114129861207534, -0.000698091487969108, 0.01021277838515354,
      0.0087225956166953212, 0.0053270941241450468, -0.00025113761991352765,
      -0.0087289169035899249, -0.0033673547729588184, 0.0016518308067232452,
      0.0086172167182133226, 0.0017977532577943688, 0.0045647978085131468,
      0.00083264470486604553, -0.0044215364015273914, -0.0033905732375149708,
      -0.0035993672282673391, -0.0070928770774342674, -0.0019637215364490053,
      0.0027574954358094896, 0.0063227307801230733, -0.0019255633169296326,
      -0.00671204456015227, -0.0067928595132565337, -0.0097540656203155,
      8.36648721136744E-12, -2.7087499168740488E-12, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0
    } ;

    helikopter4_DW.xWorkspace_PWORK.TimePtr = (void *) pTimeValues0;
    helikopter4_DW.xWorkspace_PWORK.DataPtr = (void *) pDataValues0;
    helikopter4_DW.xWorkspace_IWORK.PrevIndex = 0;
  }

  /* Start for ToFile: '<Root>/To File4' */
  {
    char fileName[509] = "helicopter4\\input4.mat";
    FILE *fp = (NULL);
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(helikopter4_M,
                        "Error creating .mat file helicopter4\\input4.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp,3,0,"input4")) {
      rtmSetErrorStatus(helikopter4_M,
                        "Error writing mat file header to file helicopter4\\input4.mat");
      return;
    }

    helikopter4_DW.ToFile4_IWORK.Count = 0;
    helikopter4_DW.ToFile4_IWORK.Decimation = -1;
    helikopter4_DW.ToFile4_PWORK.FilePtr = fp;
  }

  /* InitializeConditions for TransferFcn: '<S2>/Vandring Lavpass' */
  helikopter4_X.VandringLavpass_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S2>/Vandring Deriv' */
  helikopter4_X.VandringDeriv_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S2>/Transfer Fcn4' */
  helikopter4_X.TransferFcn4_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S2>/Transfer Fcn5' */
  helikopter4_X.TransferFcn5_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S1>/Integrator' */
  helikopter4_X.Integrator_CSTATE = helikopter4_P.Integrator_IC;
}

/* Model terminate function */
void helikopter4_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: helikopter4/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    t_uint32 num_final_pwm_outputs = 0;
    hil_task_stop_all(helikopter4_DW.HILInitialize_Card);
    hil_monitor_stop_all(helikopter4_DW.HILInitialize_Card);
    is_switching = false;
    if ((helikopter4_P.HILInitialize_set_analog_out_ex && !is_switching) ||
        (helikopter4_P.HILInitialize_set_analog_outp_c && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &helikopter4_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = helikopter4_P.HILInitialize_final_analog_outp;
        }
      }

      num_final_analog_outputs = 8U;
    }

    if ((helikopter4_P.HILInitialize_set_pwm_output_ap && !is_switching) ||
        (helikopter4_P.HILInitialize_set_pwm_outputs_p && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &helikopter4_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helikopter4_P.HILInitialize_final_pwm_outputs;
        }
      }

      num_final_pwm_outputs = 8U;
    }

    if (0
        || num_final_analog_outputs > 0
        || num_final_pwm_outputs > 0
        ) {
      /* Attempt to write the final outputs atomically (due to firmware issue in old Q2-USB). Otherwise write channels individually */
      result = hil_write(helikopter4_DW.HILInitialize_Card
                         , helikopter4_P.HILInitialize_analog_output_cha,
                         num_final_analog_outputs
                         , helikopter4_P.HILInitialize_pwm_channels,
                         num_final_pwm_outputs
                         , NULL, 0
                         , NULL, 0
                         , &helikopter4_DW.HILInitialize_AOVoltages[0]
                         , &helikopter4_DW.HILInitialize_POValues[0]
                         , (t_boolean *) NULL
                         , NULL
                         );
      if (result == -QERR_HIL_WRITE_NOT_SUPPORTED) {
        t_error local_result;
        result = 0;

        /* The hil_write operation is not supported by this card. Write final outputs for each channel type */
        if (num_final_analog_outputs > 0) {
          local_result = hil_write_analog(helikopter4_DW.HILInitialize_Card,
            helikopter4_P.HILInitialize_analog_output_cha,
            num_final_analog_outputs, &helikopter4_DW.HILInitialize_AOVoltages[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (num_final_pwm_outputs > 0) {
          local_result = hil_write_pwm(helikopter4_DW.HILInitialize_Card,
            helikopter4_P.HILInitialize_pwm_channels, num_final_pwm_outputs,
            &helikopter4_DW.HILInitialize_POValues[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(helikopter4_M, _rt_error_message);
        }
      }
    }

    hil_task_delete_all(helikopter4_DW.HILInitialize_Card);
    hil_monitor_delete_all(helikopter4_DW.HILInitialize_Card);
    hil_close(helikopter4_DW.HILInitialize_Card);
    helikopter4_DW.HILInitialize_Card = NULL;
  }

  /* Terminate for ToFile: '<Root>/To File' */
  {
    FILE *fp = (FILE *) helikopter4_DW.ToFile_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "helicopter4\\travel4.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helikopter4_M,
                          "Error closing MAT-file helicopter4\\travel4.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(helikopter4_M,
                          "Error reopening MAT-file helicopter4\\travel4.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 2, helikopter4_DW.ToFile_IWORK.Count,
           "travel4")) {
        rtmSetErrorStatus(helikopter4_M,
                          "Error writing header for travel4 to MAT-file helicopter4\\travel4.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helikopter4_M,
                          "Error closing MAT-file helicopter4\\travel4.mat");
        return;
      }

      helikopter4_DW.ToFile_PWORK.FilePtr = (NULL);
    }
  }

  /* Terminate for ToFile: '<Root>/To File1' */
  {
    FILE *fp = (FILE *) helikopter4_DW.ToFile1_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "helicopter4\\pitch4.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helikopter4_M,
                          "Error closing MAT-file helicopter4\\pitch4.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(helikopter4_M,
                          "Error reopening MAT-file helicopter4\\pitch4.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 2, helikopter4_DW.ToFile1_IWORK.Count,
           "pitch4")) {
        rtmSetErrorStatus(helikopter4_M,
                          "Error writing header for pitch4 to MAT-file helicopter4\\pitch4.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helikopter4_M,
                          "Error closing MAT-file helicopter4\\pitch4.mat");
        return;
      }

      helikopter4_DW.ToFile1_PWORK.FilePtr = (NULL);
    }
  }

  /* Terminate for ToFile: '<Root>/To File2' */
  {
    FILE *fp = (FILE *) helikopter4_DW.ToFile2_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "helicopter4\\elevation4.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helikopter4_M,
                          "Error closing MAT-file helicopter4\\elevation4.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(helikopter4_M,
                          "Error reopening MAT-file helicopter4\\elevation4.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 2, helikopter4_DW.ToFile2_IWORK.Count,
           "elevation4")) {
        rtmSetErrorStatus(helikopter4_M,
                          "Error writing header for elevation4 to MAT-file helicopter4\\elevation4.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helikopter4_M,
                          "Error closing MAT-file helicopter4\\elevation4.mat");
        return;
      }

      helikopter4_DW.ToFile2_PWORK.FilePtr = (NULL);
    }
  }

  /* Terminate for ToFile: '<Root>/To File3' */
  {
    FILE *fp = (FILE *) helikopter4_DW.ToFile3_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "helicopter4\\optinput4.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helikopter4_M,
                          "Error closing MAT-file helicopter4\\optinput4.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(helikopter4_M,
                          "Error reopening MAT-file helicopter4\\optinput4.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 3, helikopter4_DW.ToFile3_IWORK.Count,
           "optinput4")) {
        rtmSetErrorStatus(helikopter4_M,
                          "Error writing header for optinput4 to MAT-file helicopter4\\optinput4.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helikopter4_M,
                          "Error closing MAT-file helicopter4\\optinput4.mat");
        return;
      }

      helikopter4_DW.ToFile3_PWORK.FilePtr = (NULL);
    }
  }

  /* Terminate for ToFile: '<Root>/To File4' */
  {
    FILE *fp = (FILE *) helikopter4_DW.ToFile4_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "helicopter4\\input4.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helikopter4_M,
                          "Error closing MAT-file helicopter4\\input4.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(helikopter4_M,
                          "Error reopening MAT-file helicopter4\\input4.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 3, helikopter4_DW.ToFile4_IWORK.Count,
           "input4")) {
        rtmSetErrorStatus(helikopter4_M,
                          "Error writing header for input4 to MAT-file helicopter4\\input4.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helikopter4_M,
                          "Error closing MAT-file helicopter4\\input4.mat");
        return;
      }

      helikopter4_DW.ToFile4_PWORK.FilePtr = (NULL);
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
  helikopter4_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  helikopter4_update();
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
  helikopter4_initialize();
}

void MdlTerminate(void)
{
  helikopter4_terminate();
}

/* Registration function */
RT_MODEL_helikopter4_T *helikopter4(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* non-finite (run-time) assignments */
  helikopter4_P.Integrator_UpperSat = rtInf;
  helikopter4_P.Integrator_LowerSat = rtMinusInf;

  /* initialize real-time model */
  (void) memset((void *)helikopter4_M, 0,
                sizeof(RT_MODEL_helikopter4_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&helikopter4_M->solverInfo,
                          &helikopter4_M->Timing.simTimeStep);
    rtsiSetTPtr(&helikopter4_M->solverInfo, &rtmGetTPtr(helikopter4_M));
    rtsiSetStepSizePtr(&helikopter4_M->solverInfo,
                       &helikopter4_M->Timing.stepSize0);
    rtsiSetdXPtr(&helikopter4_M->solverInfo, &helikopter4_M->ModelData.derivs);
    rtsiSetContStatesPtr(&helikopter4_M->solverInfo, (real_T **)
                         &helikopter4_M->ModelData.contStates);
    rtsiSetNumContStatesPtr(&helikopter4_M->solverInfo,
      &helikopter4_M->Sizes.numContStates);
    rtsiSetErrorStatusPtr(&helikopter4_M->solverInfo, (&rtmGetErrorStatus
      (helikopter4_M)));
    rtsiSetRTModelPtr(&helikopter4_M->solverInfo, helikopter4_M);
  }

  rtsiSetSimTimeStep(&helikopter4_M->solverInfo, MAJOR_TIME_STEP);
  helikopter4_M->ModelData.intgData.f[0] = helikopter4_M->ModelData.odeF[0];
  helikopter4_M->ModelData.contStates = ((real_T *) &helikopter4_X);
  rtsiSetSolverData(&helikopter4_M->solverInfo, (void *)
                    &helikopter4_M->ModelData.intgData);
  rtsiSetSolverName(&helikopter4_M->solverInfo,"ode1");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = helikopter4_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    helikopter4_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    helikopter4_M->Timing.sampleTimes = (&helikopter4_M->
      Timing.sampleTimesArray[0]);
    helikopter4_M->Timing.offsetTimes = (&helikopter4_M->
      Timing.offsetTimesArray[0]);

    /* task periods */
    helikopter4_M->Timing.sampleTimes[0] = (0.0);
    helikopter4_M->Timing.sampleTimes[1] = (0.002);

    /* task offsets */
    helikopter4_M->Timing.offsetTimes[0] = (0.0);
    helikopter4_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(helikopter4_M, &helikopter4_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = helikopter4_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    helikopter4_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(helikopter4_M, 25.0);
  helikopter4_M->Timing.stepSize0 = 0.002;
  helikopter4_M->Timing.stepSize1 = 0.002;

  /* External mode info */
  helikopter4_M->Sizes.checksums[0] = (3477297458U);
  helikopter4_M->Sizes.checksums[1] = (2982350384U);
  helikopter4_M->Sizes.checksums[2] = (2355304348U);
  helikopter4_M->Sizes.checksums[3] = (3262901489U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[1];
    helikopter4_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(helikopter4_M->extModeInfo,
      &helikopter4_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(helikopter4_M->extModeInfo,
                        helikopter4_M->Sizes.checksums);
    rteiSetTPtr(helikopter4_M->extModeInfo, rtmGetTPtr(helikopter4_M));
  }

  helikopter4_M->solverInfoPtr = (&helikopter4_M->solverInfo);
  helikopter4_M->Timing.stepSize = (0.002);
  rtsiSetFixedStepSize(&helikopter4_M->solverInfo, 0.002);
  rtsiSetSolverMode(&helikopter4_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  helikopter4_M->ModelData.blockIO = ((void *) &helikopter4_B);

  {
    helikopter4_B.KalibrerElev = 0.0;
    helikopter4_B.Add = 0.0;
    helikopter4_B.KalibrerPitch = 0.0;
    helikopter4_B.VandringLavpass = 0.0;
    helikopter4_B.uWorkspace[0] = 0.0;
    helikopter4_B.uWorkspace[1] = 0.0;
    helikopter4_B.KalibrerVandring = 0.0;
    helikopter4_B.Add1[0] = 0.0;
    helikopter4_B.Add1[1] = 0.0;
    helikopter4_B.K_ei = 0.0;
    helikopter4_B.SatB = 0.0;
    helikopter4_B.Sat = 0.0;
    helikopter4_B.Add_j = 0.0;
  }

  /* parameters */
  helikopter4_M->ModelData.defaultParam = ((real_T *)&helikopter4_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &helikopter4_X;
    helikopter4_M->ModelData.contStates = (x);
    (void) memset((void *)&helikopter4_X, 0,
                  sizeof(X_helikopter4_T));
  }

  /* states (dwork) */
  helikopter4_M->ModelData.dwork = ((void *) &helikopter4_DW);
  (void) memset((void *)&helikopter4_DW, 0,
                sizeof(DW_helikopter4_T));

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      helikopter4_DW.HILInitialize_AIMinimums[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      helikopter4_DW.HILInitialize_AIMaximums[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      helikopter4_DW.HILInitialize_AOMinimums[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      helikopter4_DW.HILInitialize_AOMaximums[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      helikopter4_DW.HILInitialize_AOVoltages[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      helikopter4_DW.HILInitialize_FilterFrequency[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      helikopter4_DW.HILInitialize_POSortedFreqs[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      helikopter4_DW.HILInitialize_POValues[i] = 0.0;
    }
  }

  helikopter4_DW.HILWriteAnalog_Buffer[0] = 0.0;
  helikopter4_DW.HILWriteAnalog_Buffer[1] = 0.0;

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    helikopter4_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 15;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.B = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.P = &rtPTransTable;
  }

  /* Initialize Sizes */
  helikopter4_M->Sizes.numContStates = (5);/* Number of continuous states */
  helikopter4_M->Sizes.numY = (0);     /* Number of model outputs */
  helikopter4_M->Sizes.numU = (0);     /* Number of model inputs */
  helikopter4_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  helikopter4_M->Sizes.numSampTimes = (2);/* Number of sample times */
  helikopter4_M->Sizes.numBlocks = (59);/* Number of blocks */
  helikopter4_M->Sizes.numBlockIO = (11);/* Number of block outputs */
  helikopter4_M->Sizes.numBlockPrms = (184);/* Sum of parameter "widths" */
  return helikopter4_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
