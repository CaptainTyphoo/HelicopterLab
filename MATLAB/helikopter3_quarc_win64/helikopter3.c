/*
 * helikopter3.c
 *
 * Code generation for model "helikopter3".
 *
 * Model version              : 1.63
 * Simulink Coder version : 8.6 (R2014a) 27-Dec-2013
 * C source code generated on : Tue Apr 19 18:28:07 2016
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#include "helikopter3.h"
#include "helikopter3_private.h"
#include "helikopter3_dt.h"

/* Block signals (auto storage) */
B_helikopter3_T helikopter3_B;

/* Continuous states */
X_helikopter3_T helikopter3_X;

/* Block states (auto storage) */
DW_helikopter3_T helikopter3_DW;

/* Real-time model */
RT_MODEL_helikopter3_T helikopter3_M_;
RT_MODEL_helikopter3_T *const helikopter3_M = &helikopter3_M_;

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
  helikopter3_derivatives();
  rtsiSetT(si, tnew);
  for (i = 0; i < nXc; i++) {
    *x += h * f0[i];
    x++;
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model output function */
void helikopter3_output(void)
{
  /* local block i/o variables */
  real_T rtb_Add[4];
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
  if (rtmIsMajorTimeStep(helikopter3_M)) {
    /* set solver stop time */
    if (!(helikopter3_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&helikopter3_M->solverInfo,
                            ((helikopter3_M->Timing.clockTickH0 + 1) *
        helikopter3_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&helikopter3_M->solverInfo,
                            ((helikopter3_M->Timing.clockTick0 + 1) *
        helikopter3_M->Timing.stepSize0 + helikopter3_M->Timing.clockTickH0 *
        helikopter3_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(helikopter3_M)) {
    helikopter3_M->Timing.t[0] = rtsiGetT(&helikopter3_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(helikopter3_M)) {
    /* S-Function (hil_read_encoder_block): '<S2>/HIL Read Encoder' */

    /* S-Function Block: helikopter3/Heli 3D/HIL Read Encoder (hil_read_encoder_block) */
    {
      t_error result = hil_read_encoder(helikopter3_DW.HILInitialize_Card,
        helikopter3_P.HILReadEncoder_channels, 3,
        &helikopter3_DW.HILReadEncoder_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helikopter3_M, _rt_error_message);
      } else {
        rtb_HILReadEncoder_o1 = helikopter3_DW.HILReadEncoder_Buffer[0];
        rtb_HILReadEncoder_o2 = helikopter3_DW.HILReadEncoder_Buffer[1];
        rtb_HILReadEncoder_o3 = helikopter3_DW.HILReadEncoder_Buffer[2];
      }
    }

    /* Gain: '<S2>/Kalibrer-Elev' */
    helikopter3_B.KalibrerElev = helikopter3_P.KalibElevasjon *
      rtb_HILReadEncoder_o3;

    /* Sum: '<Root>/Add' incorporates:
     *  Constant: '<Root>/Constant'
     */
    helikopter3_B.Add = helikopter3_B.KalibrerElev +
      helikopter3_P.Constant_Value;

    /* Gain: '<S2>/Kalibrer-Pitch' */
    helikopter3_B.KalibrerPitch = helikopter3_P.KalibPitch *
      rtb_HILReadEncoder_o2;
  }

  /* TransferFcn: '<S2>/Vandring Lavpass' */
  helikopter3_B.VandringLavpass = 0.0;
  helikopter3_B.VandringLavpass += helikopter3_P.VandringLavpass_C *
    helikopter3_X.VandringLavpass_CSTATE;
  if (rtmIsMajorTimeStep(helikopter3_M)) {
    /* ToFile: '<Root>/To File' */
    {
      if (!(++helikopter3_DW.ToFile_IWORK.Decimation % 1) &&
          (helikopter3_DW.ToFile_IWORK.Count*2)+1 < 100000000 ) {
        FILE *fp = (FILE *) helikopter3_DW.ToFile_PWORK.FilePtr;
        if (fp != (NULL)) {
          real_T u[2];
          helikopter3_DW.ToFile_IWORK.Decimation = 0;
          u[0] = helikopter3_M->Timing.t[1];
          u[1] = helikopter3_B.VandringLavpass;
          if (fwrite(u, sizeof(real_T), 2, fp) != 2) {
            rtmSetErrorStatus(helikopter3_M,
                              "Error writing to MAT-file helicopter3\\travel3.mat");
            return;
          }

          if (((++helikopter3_DW.ToFile_IWORK.Count)*2)+1 >= 100000000) {
            (void)fprintf(stdout,
                          "*** The ToFile block will stop logging data before\n"
                          "    the simulation has ended, because it has reached\n"
                          "    the maximum number of elements (100000000)\n"
                          "    allowed in MAT-file helicopter3\\travel3.mat.\n");
          }
        }
      }
    }

    /* ToFile: '<Root>/To File1' */
    {
      if (!(++helikopter3_DW.ToFile1_IWORK.Decimation % 1) &&
          (helikopter3_DW.ToFile1_IWORK.Count*2)+1 < 100000000 ) {
        FILE *fp = (FILE *) helikopter3_DW.ToFile1_PWORK.FilePtr;
        if (fp != (NULL)) {
          real_T u[2];
          helikopter3_DW.ToFile1_IWORK.Decimation = 0;
          u[0] = helikopter3_M->Timing.t[1];
          u[1] = helikopter3_B.KalibrerPitch;
          if (fwrite(u, sizeof(real_T), 2, fp) != 2) {
            rtmSetErrorStatus(helikopter3_M,
                              "Error writing to MAT-file helicopter3\\pitch3.mat");
            return;
          }

          if (((++helikopter3_DW.ToFile1_IWORK.Count)*2)+1 >= 100000000) {
            (void)fprintf(stdout,
                          "*** The ToFile block will stop logging data before\n"
                          "    the simulation has ended, because it has reached\n"
                          "    the maximum number of elements (100000000)\n"
                          "    allowed in MAT-file helicopter3\\pitch3.mat.\n");
          }
        }
      }
    }

    /* ToFile: '<Root>/To File2' */
    {
      if (!(++helikopter3_DW.ToFile2_IWORK.Decimation % 1) &&
          (helikopter3_DW.ToFile2_IWORK.Count*2)+1 < 100000000 ) {
        FILE *fp = (FILE *) helikopter3_DW.ToFile2_PWORK.FilePtr;
        if (fp != (NULL)) {
          real_T u[2];
          helikopter3_DW.ToFile2_IWORK.Decimation = 0;
          u[0] = helikopter3_M->Timing.t[1];
          u[1] = helikopter3_B.Add;
          if (fwrite(u, sizeof(real_T), 2, fp) != 2) {
            rtmSetErrorStatus(helikopter3_M,
                              "Error writing to MAT-file helicopter3\\elevation3.mat");
            return;
          }

          if (((++helikopter3_DW.ToFile2_IWORK.Count)*2)+1 >= 100000000) {
            (void)fprintf(stdout,
                          "*** The ToFile block will stop logging data before\n"
                          "    the simulation has ended, because it has reached\n"
                          "    the maximum number of elements (100000000)\n"
                          "    allowed in MAT-file helicopter3\\elevation3.mat.\n");
          }
        }
      }
    }
  }

  /* FromWorkspace: '<Root>/u* Workspace' */
  {
    real_T *pDataValues = (real_T *) helikopter3_DW.uWorkspace_PWORK.DataPtr;
    real_T *pTimeValues = (real_T *) helikopter3_DW.uWorkspace_PWORK.TimePtr;
    int_T currTimeIndex = helikopter3_DW.uWorkspace_IWORK.PrevIndex;
    real_T t = helikopter3_M->Timing.t[0];

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

    helikopter3_DW.uWorkspace_IWORK.PrevIndex = currTimeIndex;

    /* Post output */
    {
      real_T t1 = pTimeValues[currTimeIndex];
      real_T t2 = pTimeValues[currTimeIndex + 1];
      if (t1 == t2) {
        if (t < t1) {
          helikopter3_B.uWorkspace = pDataValues[currTimeIndex];
        } else {
          helikopter3_B.uWorkspace = pDataValues[currTimeIndex + 1];
        }
      } else {
        real_T f1 = (t2 - t) / (t2 - t1);
        real_T f2 = 1.0 - f1;
        real_T d1;
        real_T d2;
        int_T TimeIndex= currTimeIndex;
        d1 = pDataValues[TimeIndex];
        d2 = pDataValues[TimeIndex + 1];
        helikopter3_B.uWorkspace = (real_T) rtInterpolate(d1, d2, f1, f2);
        pDataValues += 141;
      }
    }
  }

  if (rtmIsMajorTimeStep(helikopter3_M)) {
    /* ToFile: '<Root>/To File3' */
    {
      if (!(++helikopter3_DW.ToFile3_IWORK.Decimation % 1) &&
          (helikopter3_DW.ToFile3_IWORK.Count*2)+1 < 100000000 ) {
        FILE *fp = (FILE *) helikopter3_DW.ToFile3_PWORK.FilePtr;
        if (fp != (NULL)) {
          real_T u[2];
          helikopter3_DW.ToFile3_IWORK.Decimation = 0;
          u[0] = helikopter3_M->Timing.t[1];
          u[1] = helikopter3_B.uWorkspace;
          if (fwrite(u, sizeof(real_T), 2, fp) != 2) {
            rtmSetErrorStatus(helikopter3_M,
                              "Error writing to MAT-file helicopter3\\optinput3.mat");
            return;
          }

          if (((++helikopter3_DW.ToFile3_IWORK.Count)*2)+1 >= 100000000) {
            (void)fprintf(stdout,
                          "*** The ToFile block will stop logging data before\n"
                          "    the simulation has ended, because it has reached\n"
                          "    the maximum number of elements (100000000)\n"
                          "    allowed in MAT-file helicopter3\\optinput3.mat.\n");
          }
        }
      }
    }
  }

  /* FromWorkspace: '<Root>/x* Workspace' */
  {
    real_T *pDataValues = (real_T *) helikopter3_DW.xWorkspace_PWORK.DataPtr;
    real_T *pTimeValues = (real_T *) helikopter3_DW.xWorkspace_PWORK.TimePtr;
    int_T currTimeIndex = helikopter3_DW.xWorkspace_IWORK.PrevIndex;
    real_T t = helikopter3_M->Timing.t[0];

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

    helikopter3_DW.xWorkspace_IWORK.PrevIndex = currTimeIndex;

    /* Post output */
    {
      real_T t1 = pTimeValues[currTimeIndex];
      real_T t2 = pTimeValues[currTimeIndex + 1];
      if (t1 == t2) {
        if (t < t1) {
          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 4; ++elIdx) {
              (&rtb_Add[0])[elIdx] = pDataValues[currTimeIndex];
              pDataValues += 141;
            }
          }
        } else {
          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 4; ++elIdx) {
              (&rtb_Add[0])[elIdx] = pDataValues[currTimeIndex + 1];
              pDataValues += 141;
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
          for (elIdx = 0; elIdx < 4; ++elIdx) {
            d1 = pDataValues[TimeIndex];
            d2 = pDataValues[TimeIndex + 1];
            (&rtb_Add[0])[elIdx] = (real_T) rtInterpolate(d1, d2, f1, f2);
            pDataValues += 141;
          }
        }
      }
    }
  }

  if (rtmIsMajorTimeStep(helikopter3_M)) {
    /* Gain: '<S2>/Kalibrer -Vandring' */
    helikopter3_B.KalibrerVandring = helikopter3_P.KalibVandring *
      rtb_HILReadEncoder_o1;
  }

  /* TransferFcn: '<S2>/Transfer Fcn5' */
  rtb_Gain1 = 0.0;
  rtb_Gain1 += helikopter3_P.TransferFcn5_C * helikopter3_X.TransferFcn5_CSTATE;
  rtb_Gain1 += helikopter3_P.TransferFcn5_D * helikopter3_B.KalibrerElev;

  /* SignalConversion: '<Root>/TmpSignal ConversionAtGainInport1' incorporates:
   *  TransferFcn: '<S2>/Transfer Fcn4'
   *  TransferFcn: '<S2>/Vandring Deriv'
   */
  tmp[0] = helikopter3_B.VandringLavpass;
  tmp[1] = helikopter3_P.VandringDeriv_C * helikopter3_X.VandringDeriv_CSTATE +
    helikopter3_P.VandringDeriv_D * helikopter3_B.KalibrerVandring;
  tmp[2] = helikopter3_B.KalibrerPitch;
  tmp[3] = helikopter3_P.TransferFcn4_C * helikopter3_X.TransferFcn4_CSTATE +
    helikopter3_P.TransferFcn4_D * helikopter3_B.KalibrerPitch;
  tmp[4] = helikopter3_B.Add;
  tmp[5] = rtb_Gain1;

  /* Gain: '<Root>/Gain' */
  for (i = 0; i < 6; i++) {
    rtb_Gain[i] = 0.0;
    for (i_0 = 0; i_0 < 6; i_0++) {
      rtb_Gain[i] += helikopter3_P.Gain_Gain[6 * i_0 + i] * tmp[i_0];
    }
  }

  /* End of Gain: '<Root>/Gain' */

  /* Sum: '<S3>/Add2' incorporates:
   *  Constant: '<S3>/Constant'
   */
  rtb_Gain1 = rtb_Gain[0] + helikopter3_P.Constant_Value_b;

  /* Sum: '<S3>/Add' */
  rtb_Add[0] = rtb_Gain1 - rtb_Add[0];
  rtb_Add[1] = rtb_Gain[1] - rtb_Add[1];
  rtb_Add[2] = rtb_Gain[2] - rtb_Add[2];
  rtb_Add[3] = rtb_Gain[3] - rtb_Add[3];

  /* Gain: '<S3>/Gain' */
  rtb_Gain1 = ((helikopter3_P.K[0] * rtb_Add[0] + helikopter3_P.K[1] * rtb_Add[1])
               + helikopter3_P.K[2] * rtb_Add[2]) + helikopter3_P.K[3] *
    rtb_Add[3];

  /* Sum: '<S3>/Add1' */
  helikopter3_B.Add1 = helikopter3_B.uWorkspace - rtb_Gain1;
  if (rtmIsMajorTimeStep(helikopter3_M)) {
    /* ToFile: '<Root>/To File4' */
    {
      if (!(++helikopter3_DW.ToFile4_IWORK.Decimation % 1) &&
          (helikopter3_DW.ToFile4_IWORK.Count*2)+1 < 100000000 ) {
        FILE *fp = (FILE *) helikopter3_DW.ToFile4_PWORK.FilePtr;
        if (fp != (NULL)) {
          real_T u[2];
          helikopter3_DW.ToFile4_IWORK.Decimation = 0;
          u[0] = helikopter3_M->Timing.t[1];
          u[1] = helikopter3_B.Add1;
          if (fwrite(u, sizeof(real_T), 2, fp) != 2) {
            rtmSetErrorStatus(helikopter3_M,
                              "Error writing to MAT-file helicopter3\\input3.mat");
            return;
          }

          if (((++helikopter3_DW.ToFile4_IWORK.Count)*2)+1 >= 100000000) {
            (void)fprintf(stdout,
                          "*** The ToFile block will stop logging data before\n"
                          "    the simulation has ended, because it has reached\n"
                          "    the maximum number of elements (100000000)\n"
                          "    allowed in MAT-file helicopter3\\input3.mat.\n");
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
  if (helikopter3_X.Integrator_CSTATE >= helikopter3_P.Integrator_UpperSat ) {
    helikopter3_X.Integrator_CSTATE = helikopter3_P.Integrator_UpperSat;
  } else if (helikopter3_X.Integrator_CSTATE <=
             (helikopter3_P.Integrator_LowerSat) ) {
    helikopter3_X.Integrator_CSTATE = (helikopter3_P.Integrator_LowerSat);
  }

  rtb_Gain1 = helikopter3_X.Integrator_CSTATE;

  /* Sum: '<S1>/Sum' incorporates:
   *  Constant: '<Root>/elevation'
   */
  rtb_Sum = helikopter3_P.elevation_Value - rtb_Gain[4];

  /* Gain: '<S1>/K_ei' */
  helikopter3_B.K_ei = helikopter3_P.K_ei * rtb_Sum;

  /* Sum: '<S1>/Sum1' incorporates:
   *  Gain: '<S1>/K_ed'
   *  Gain: '<S1>/K_ep'
   */
  rtb_Gain1 = (helikopter3_P.K_ep * rtb_Sum + rtb_Gain1) + -helikopter3_P.K_ed *
    rtb_Gain[5];

  /* Saturate: '<S1>/Saturation' */
  if (rtb_Gain1 > helikopter3_P.Saturation_UpperSat) {
    rtb_Gain1 = helikopter3_P.Saturation_UpperSat;
  } else {
    if (rtb_Gain1 < helikopter3_P.Saturation_LowerSat) {
      rtb_Gain1 = helikopter3_P.Saturation_LowerSat;
    }
  }

  /* End of Saturate: '<S1>/Saturation' */
  if (rtmIsMajorTimeStep(helikopter3_M)) {
  }

  /* Saturate: '<S4>/Saturation' */
  if (helikopter3_B.Add1 > helikopter3_P.Saturation_UpperSat_d) {
    rtb_Sum = helikopter3_P.Saturation_UpperSat_d;
  } else if (helikopter3_B.Add1 < helikopter3_P.Saturation_LowerSat_n) {
    rtb_Sum = helikopter3_P.Saturation_LowerSat_n;
  } else {
    rtb_Sum = helikopter3_B.Add1;
  }

  /* Sum: '<S4>/Sum' incorporates:
   *  Gain: '<S4>/K_pd'
   *  Gain: '<S4>/K_pp'
   *  Saturate: '<S4>/Saturation'
   *  Sum: '<S4>/Sum1'
   */
  rtb_Sum = 0.3 * helikopter3_P.K_pp * (rtb_Sum - rtb_Gain[2]) -
    helikopter3_P.K_pd * rtb_Gain[3];

  /* Gain: '<S5>/Gain2' incorporates:
   *  Sum: '<S5>/Sum4'
   */
  u0 = (rtb_Gain1 - rtb_Sum) * helikopter3_P.V_b_eq;

  /* Saturate: '<S2>/Sat B' */
  if (u0 > helikopter3_P.SatB_UpperSat) {
    helikopter3_B.SatB = helikopter3_P.SatB_UpperSat;
  } else if (u0 < helikopter3_P.SatB_LowerSat) {
    helikopter3_B.SatB = helikopter3_P.SatB_LowerSat;
  } else {
    helikopter3_B.SatB = u0;
  }

  /* End of Saturate: '<S2>/Sat B' */
  if (rtmIsMajorTimeStep(helikopter3_M)) {
  }

  /* Gain: '<S5>/Gain1' incorporates:
   *  Sum: '<S5>/Sum3'
   */
  rtb_Gain1 = (rtb_Sum + rtb_Gain1) * helikopter3_P.V_f_eq;

  /* Saturate: '<S2>/Sat' */
  if (rtb_Gain1 > helikopter3_P.Sat_UpperSat) {
    helikopter3_B.Sat = helikopter3_P.Sat_UpperSat;
  } else if (rtb_Gain1 < helikopter3_P.Sat_LowerSat) {
    helikopter3_B.Sat = helikopter3_P.Sat_LowerSat;
  } else {
    helikopter3_B.Sat = rtb_Gain1;
  }

  /* End of Saturate: '<S2>/Sat' */
  if (rtmIsMajorTimeStep(helikopter3_M)) {
  }

  /* Sum: '<S2>/Add' incorporates:
   *  Constant: '<S2>/elevation'
   */
  helikopter3_B.Add_j = helikopter3_B.SatB - helikopter3_P.elevation_Value_g;
  if (rtmIsMajorTimeStep(helikopter3_M)) {
    /* S-Function (hil_write_analog_block): '<S2>/HIL Write Analog' */

    /* S-Function Block: helikopter3/Heli 3D/HIL Write Analog (hil_write_analog_block) */
    {
      t_error result;
      helikopter3_DW.HILWriteAnalog_Buffer[0] = helikopter3_B.Add_j;
      helikopter3_DW.HILWriteAnalog_Buffer[1] = helikopter3_B.Sat;
      result = hil_write_analog(helikopter3_DW.HILInitialize_Card,
        helikopter3_P.HILWriteAnalog_channels, 2,
        &helikopter3_DW.HILWriteAnalog_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helikopter3_M, _rt_error_message);
      }
    }
  }
}

/* Model update function */
void helikopter3_update(void)
{
  if (rtmIsMajorTimeStep(helikopter3_M)) {
    rt_ertODEUpdateContinuousStates(&helikopter3_M->solverInfo);
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
  if (!(++helikopter3_M->Timing.clockTick0)) {
    ++helikopter3_M->Timing.clockTickH0;
  }

  helikopter3_M->Timing.t[0] = rtsiGetSolverStopTime(&helikopter3_M->solverInfo);

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
    if (!(++helikopter3_M->Timing.clockTick1)) {
      ++helikopter3_M->Timing.clockTickH1;
    }

    helikopter3_M->Timing.t[1] = helikopter3_M->Timing.clockTick1 *
      helikopter3_M->Timing.stepSize1 + helikopter3_M->Timing.clockTickH1 *
      helikopter3_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Derivatives for root system: '<Root>' */
void helikopter3_derivatives(void)
{
  XDot_helikopter3_T *_rtXdot;
  _rtXdot = ((XDot_helikopter3_T *) helikopter3_M->ModelData.derivs);

  /* Derivatives for TransferFcn: '<S2>/Vandring Lavpass' */
  _rtXdot->VandringLavpass_CSTATE = 0.0;
  _rtXdot->VandringLavpass_CSTATE += helikopter3_P.VandringLavpass_A *
    helikopter3_X.VandringLavpass_CSTATE;
  _rtXdot->VandringLavpass_CSTATE += helikopter3_B.KalibrerVandring;

  /* Derivatives for TransferFcn: '<S2>/Vandring Deriv' */
  _rtXdot->VandringDeriv_CSTATE = 0.0;
  _rtXdot->VandringDeriv_CSTATE += helikopter3_P.VandringDeriv_A *
    helikopter3_X.VandringDeriv_CSTATE;
  _rtXdot->VandringDeriv_CSTATE += helikopter3_B.KalibrerVandring;

  /* Derivatives for TransferFcn: '<S2>/Transfer Fcn4' */
  _rtXdot->TransferFcn4_CSTATE = 0.0;
  _rtXdot->TransferFcn4_CSTATE += helikopter3_P.TransferFcn4_A *
    helikopter3_X.TransferFcn4_CSTATE;
  _rtXdot->TransferFcn4_CSTATE += helikopter3_B.KalibrerPitch;

  /* Derivatives for TransferFcn: '<S2>/Transfer Fcn5' */
  _rtXdot->TransferFcn5_CSTATE = 0.0;
  _rtXdot->TransferFcn5_CSTATE += helikopter3_P.TransferFcn5_A *
    helikopter3_X.TransferFcn5_CSTATE;
  _rtXdot->TransferFcn5_CSTATE += helikopter3_B.KalibrerElev;

  /* Derivatives for Integrator: '<S1>/Integrator' */
  {
    boolean_T lsat;
    boolean_T usat;
    lsat = ( helikopter3_X.Integrator_CSTATE <=
            (helikopter3_P.Integrator_LowerSat) );
    usat = ( helikopter3_X.Integrator_CSTATE >=
            helikopter3_P.Integrator_UpperSat );
    if ((!lsat && !usat) ||
        (lsat && (helikopter3_B.K_ei > 0)) ||
        (usat && (helikopter3_B.K_ei < 0)) ) {
      ((XDot_helikopter3_T *) helikopter3_M->ModelData.derivs)
        ->Integrator_CSTATE = helikopter3_B.K_ei;
    } else {
      /* in saturation */
      ((XDot_helikopter3_T *) helikopter3_M->ModelData.derivs)
        ->Integrator_CSTATE = 0.0;
    }
  }
}

/* Model initialize function */
void helikopter3_initialize(void)
{
  /* Start for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: helikopter3/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q8_usb", "0", &helikopter3_DW.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helikopter3_M, _rt_error_message);
      return;
    }

    is_switching = false;
    result = hil_set_card_specific_options(helikopter3_DW.HILInitialize_Card,
      "update_rate=normal;decimation=1", 32);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helikopter3_M, _rt_error_message);
      return;
    }

    result = hil_watchdog_clear(helikopter3_DW.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helikopter3_M, _rt_error_message);
      return;
    }

    if ((helikopter3_P.HILInitialize_set_analog_input_ && !is_switching) ||
        (helikopter3_P.HILInitialize_set_analog_inpu_m && is_switching)) {
      {
        int_T i1;
        real_T *dw_AIMinimums = &helikopter3_DW.HILInitialize_AIMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMinimums[i1] = helikopter3_P.HILInitialize_analog_input_mini;
        }
      }

      {
        int_T i1;
        real_T *dw_AIMaximums = &helikopter3_DW.HILInitialize_AIMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMaximums[i1] = helikopter3_P.HILInitialize_analog_input_maxi;
        }
      }

      result = hil_set_analog_input_ranges(helikopter3_DW.HILInitialize_Card,
        helikopter3_P.HILInitialize_analog_input_chan, 8U,
        &helikopter3_DW.HILInitialize_AIMinimums[0],
        &helikopter3_DW.HILInitialize_AIMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helikopter3_M, _rt_error_message);
        return;
      }
    }

    if ((helikopter3_P.HILInitialize_set_analog_output && !is_switching) ||
        (helikopter3_P.HILInitialize_set_analog_outp_b && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOMinimums = &helikopter3_DW.HILInitialize_AOMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMinimums[i1] = helikopter3_P.HILInitialize_analog_output_min;
        }
      }

      {
        int_T i1;
        real_T *dw_AOMaximums = &helikopter3_DW.HILInitialize_AOMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMaximums[i1] = helikopter3_P.HILInitialize_analog_output_max;
        }
      }

      result = hil_set_analog_output_ranges(helikopter3_DW.HILInitialize_Card,
        helikopter3_P.HILInitialize_analog_output_cha, 8U,
        &helikopter3_DW.HILInitialize_AOMinimums[0],
        &helikopter3_DW.HILInitialize_AOMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helikopter3_M, _rt_error_message);
        return;
      }
    }

    if ((helikopter3_P.HILInitialize_set_analog_outp_e && !is_switching) ||
        (helikopter3_P.HILInitialize_set_analog_outp_j && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &helikopter3_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = helikopter3_P.HILInitialize_initial_analog_ou;
        }
      }

      result = hil_write_analog(helikopter3_DW.HILInitialize_Card,
        helikopter3_P.HILInitialize_analog_output_cha, 8U,
        &helikopter3_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helikopter3_M, _rt_error_message);
        return;
      }
    }

    if (helikopter3_P.HILInitialize_set_analog_outp_p) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &helikopter3_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = helikopter3_P.HILInitialize_watchdog_analog_o;
        }
      }

      result = hil_watchdog_set_analog_expiration_state
        (helikopter3_DW.HILInitialize_Card,
         helikopter3_P.HILInitialize_analog_output_cha, 8U,
         &helikopter3_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helikopter3_M, _rt_error_message);
        return;
      }
    }

    if ((helikopter3_P.HILInitialize_set_encoder_param && !is_switching) ||
        (helikopter3_P.HILInitialize_set_encoder_par_m && is_switching)) {
      {
        int_T i1;
        int32_T *dw_QuadratureModes =
          &helikopter3_DW.HILInitialize_QuadratureModes[0];
        for (i1=0; i1 < 8; i1++) {
          dw_QuadratureModes[i1] = helikopter3_P.HILInitialize_quadrature;
        }
      }

      result = hil_set_encoder_quadrature_mode(helikopter3_DW.HILInitialize_Card,
        helikopter3_P.HILInitialize_encoder_channels, 8U,
        (t_encoder_quadrature_mode *)
        &helikopter3_DW.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helikopter3_M, _rt_error_message);
        return;
      }
    }

    if ((helikopter3_P.HILInitialize_set_encoder_count && !is_switching) ||
        (helikopter3_P.HILInitialize_set_encoder_cou_k && is_switching)) {
      {
        int_T i1;
        int32_T *dw_InitialEICounts =
          &helikopter3_DW.HILInitialize_InitialEICounts[0];
        for (i1=0; i1 < 8; i1++) {
          dw_InitialEICounts[i1] = helikopter3_P.HILInitialize_initial_encoder_c;
        }
      }

      result = hil_set_encoder_counts(helikopter3_DW.HILInitialize_Card,
        helikopter3_P.HILInitialize_encoder_channels, 8U,
        &helikopter3_DW.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helikopter3_M, _rt_error_message);
        return;
      }
    }

    if ((helikopter3_P.HILInitialize_set_pwm_params_at && !is_switching) ||
        (helikopter3_P.HILInitialize_set_pwm_params__f && is_switching)) {
      uint32_T num_duty_cycle_modes = 0;
      uint32_T num_frequency_modes = 0;

      {
        int_T i1;
        int32_T *dw_POModeValues = &helikopter3_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = helikopter3_P.HILInitialize_pwm_modes;
        }
      }

      result = hil_set_pwm_mode(helikopter3_DW.HILInitialize_Card,
        helikopter3_P.HILInitialize_pwm_channels, 8U, (t_pwm_mode *)
        &helikopter3_DW.HILInitialize_POModeValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helikopter3_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        const uint32_T *p_HILInitialize_pwm_channels =
          helikopter3_P.HILInitialize_pwm_channels;
        int32_T *dw_POModeValues = &helikopter3_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          if (dw_POModeValues[i1] == PWM_DUTY_CYCLE_MODE || dw_POModeValues[i1] ==
              PWM_ONE_SHOT_MODE || dw_POModeValues[i1] == PWM_TIME_MODE) {
            helikopter3_DW.HILInitialize_POSortedChans[num_duty_cycle_modes] =
              p_HILInitialize_pwm_channels[i1];
            helikopter3_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes] =
              helikopter3_P.HILInitialize_pwm_frequency;
            num_duty_cycle_modes++;
          } else {
            helikopter3_DW.HILInitialize_POSortedChans[7U - num_frequency_modes]
              = p_HILInitialize_pwm_channels[i1];
            helikopter3_DW.HILInitialize_POSortedFreqs[7U - num_frequency_modes]
              = helikopter3_P.HILInitialize_pwm_frequency;
            num_frequency_modes++;
          }
        }
      }

      if (num_duty_cycle_modes > 0) {
        result = hil_set_pwm_frequency(helikopter3_DW.HILInitialize_Card,
          &helikopter3_DW.HILInitialize_POSortedChans[0], num_duty_cycle_modes,
          &helikopter3_DW.HILInitialize_POSortedFreqs[0]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(helikopter3_M, _rt_error_message);
          return;
        }
      }

      if (num_frequency_modes > 0) {
        result = hil_set_pwm_duty_cycle(helikopter3_DW.HILInitialize_Card,
          &helikopter3_DW.HILInitialize_POSortedChans[num_duty_cycle_modes],
          num_frequency_modes,
          &helikopter3_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(helikopter3_M, _rt_error_message);
          return;
        }
      }

      {
        int_T i1;
        int32_T *dw_POModeValues = &helikopter3_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = helikopter3_P.HILInitialize_pwm_configuration;
        }
      }

      {
        int_T i1;
        int32_T *dw_POAlignValues = &helikopter3_DW.HILInitialize_POAlignValues
          [0];
        for (i1=0; i1 < 8; i1++) {
          dw_POAlignValues[i1] = helikopter3_P.HILInitialize_pwm_alignment;
        }
      }

      {
        int_T i1;
        int32_T *dw_POPolarityVals =
          &helikopter3_DW.HILInitialize_POPolarityVals[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POPolarityVals[i1] = helikopter3_P.HILInitialize_pwm_polarity;
        }
      }

      result = hil_set_pwm_configuration(helikopter3_DW.HILInitialize_Card,
        helikopter3_P.HILInitialize_pwm_channels, 8U,
        (t_pwm_configuration *) &helikopter3_DW.HILInitialize_POModeValues[0],
        (t_pwm_alignment *) &helikopter3_DW.HILInitialize_POAlignValues[0],
        (t_pwm_polarity *) &helikopter3_DW.HILInitialize_POPolarityVals[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helikopter3_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        real_T *dw_POSortedFreqs = &helikopter3_DW.HILInitialize_POSortedFreqs[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POSortedFreqs[i1] = helikopter3_P.HILInitialize_pwm_leading_deadb;
        }
      }

      {
        int_T i1;
        real_T *dw_POValues = &helikopter3_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helikopter3_P.HILInitialize_pwm_trailing_dead;
        }
      }

      result = hil_set_pwm_deadband(helikopter3_DW.HILInitialize_Card,
        helikopter3_P.HILInitialize_pwm_channels, 8U,
        &helikopter3_DW.HILInitialize_POSortedFreqs[0],
        &helikopter3_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helikopter3_M, _rt_error_message);
        return;
      }
    }

    if ((helikopter3_P.HILInitialize_set_pwm_outputs_a && !is_switching) ||
        (helikopter3_P.HILInitialize_set_pwm_outputs_g && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &helikopter3_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helikopter3_P.HILInitialize_initial_pwm_outpu;
        }
      }

      result = hil_write_pwm(helikopter3_DW.HILInitialize_Card,
        helikopter3_P.HILInitialize_pwm_channels, 8U,
        &helikopter3_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helikopter3_M, _rt_error_message);
        return;
      }
    }

    if (helikopter3_P.HILInitialize_set_pwm_outputs_o) {
      {
        int_T i1;
        real_T *dw_POValues = &helikopter3_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helikopter3_P.HILInitialize_watchdog_pwm_outp;
        }
      }

      result = hil_watchdog_set_pwm_expiration_state
        (helikopter3_DW.HILInitialize_Card,
         helikopter3_P.HILInitialize_pwm_channels, 8U,
         &helikopter3_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helikopter3_M, _rt_error_message);
        return;
      }
    }
  }

  /* Start for ToFile: '<Root>/To File' */
  {
    char fileName[509] = "helicopter3\\travel3.mat";
    FILE *fp = (NULL);
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(helikopter3_M,
                        "Error creating .mat file helicopter3\\travel3.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp,2,0,"travel3")) {
      rtmSetErrorStatus(helikopter3_M,
                        "Error writing mat file header to file helicopter3\\travel3.mat");
      return;
    }

    helikopter3_DW.ToFile_IWORK.Count = 0;
    helikopter3_DW.ToFile_IWORK.Decimation = -1;
    helikopter3_DW.ToFile_PWORK.FilePtr = fp;
  }

  /* Start for ToFile: '<Root>/To File1' */
  {
    char fileName[509] = "helicopter3\\pitch3.mat";
    FILE *fp = (NULL);
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(helikopter3_M,
                        "Error creating .mat file helicopter3\\pitch3.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp,2,0,"pitch3")) {
      rtmSetErrorStatus(helikopter3_M,
                        "Error writing mat file header to file helicopter3\\pitch3.mat");
      return;
    }

    helikopter3_DW.ToFile1_IWORK.Count = 0;
    helikopter3_DW.ToFile1_IWORK.Decimation = -1;
    helikopter3_DW.ToFile1_PWORK.FilePtr = fp;
  }

  /* Start for ToFile: '<Root>/To File2' */
  {
    char fileName[509] = "helicopter3\\elevation3.mat";
    FILE *fp = (NULL);
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(helikopter3_M,
                        "Error creating .mat file helicopter3\\elevation3.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp,2,0,"elevation3")) {
      rtmSetErrorStatus(helikopter3_M,
                        "Error writing mat file header to file helicopter3\\elevation3.mat");
      return;
    }

    helikopter3_DW.ToFile2_IWORK.Count = 0;
    helikopter3_DW.ToFile2_IWORK.Decimation = -1;
    helikopter3_DW.ToFile2_PWORK.FilePtr = fp;
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

    helikopter3_DW.uWorkspace_PWORK.TimePtr = (void *) pTimeValues0;
    helikopter3_DW.uWorkspace_PWORK.DataPtr = (void *) pDataValues0;
    helikopter3_DW.uWorkspace_IWORK.PrevIndex = 0;
  }

  /* Start for ToFile: '<Root>/To File3' */
  {
    char fileName[509] = "helicopter3\\optinput3.mat";
    FILE *fp = (NULL);
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(helikopter3_M,
                        "Error creating .mat file helicopter3\\optinput3.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp,2,0,"optinput3")) {
      rtmSetErrorStatus(helikopter3_M,
                        "Error writing mat file header to file helicopter3\\optinput3.mat");
      return;
    }

    helikopter3_DW.ToFile3_IWORK.Count = 0;
    helikopter3_DW.ToFile3_IWORK.Decimation = -1;
    helikopter3_DW.ToFile3_PWORK.FilePtr = fp;
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
      22.5, 22.75, 23.0, 23.25, 23.5, 23.75, 24.0, 24.25, 24.5, 24.75, 25.0,
      25.25, 25.5, 25.75, 26.0, 26.25, 26.5, 26.75, 27.0, 27.25, 27.5, 27.75,
      28.0, 28.25, 28.5, 28.75, 29.0, 29.25, 29.5, 29.75, 30.0, 30.25, 30.5,
      30.75, 31.0, 31.25, 31.5, 31.75, 32.0, 32.25, 32.5, 32.75, 33.0, 33.25,
      33.5, 33.75, 34.0, 34.25, 34.5, 34.75, 35.0 } ;

    static real_T pDataValues0[] = { 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1335163894569176, 3.1173638611911012,
      3.0931350687924946, 3.0608300122612841, 3.0204486915976534,
      2.9719911068017031, 2.9154572578734719, 2.850847144843685,
      2.7785412190221219, 2.6998617619674343, 2.6162181029774461,
      2.5285011270400406, 2.4372901285068784, 2.3432402252469027,
      2.2471262266176688, 2.1496652870439226, 2.0514302447290689,
      1.9529094104693541, 1.8545757236893154, 1.7568852128565176,
      1.6602440061987394, 1.5649992940908095, 1.4714552596929793,
      1.379886264048285, 1.290536293895338, 1.2036145632418849,
      1.1192965702320592, 1.0377291018163446, 0.9590338959303536,
      0.88330872295705209, 0.81062809727002838, 0.74104507868754532,
      0.67459359206108449, 0.61129030720968036, 0.5511360061518038,
      0.49411689494801492, 0.4402060696844497, 0.38936498406472292,
      0.34154475531989259, 0.29668732497478739, 0.25472656468186378,
      0.21558935425618164, 0.17919659810256969, 0.14546415538389681,
      0.11430369380374705, 0.085623485429906207, 0.059329148854332221,
      0.035324332412002619, 0.013511336774359005, -0.006208318517317562,
      -0.02393337937570365, -0.039762389958239511, -0.053793272949021351,
      -0.066122955665302907, -0.076847039421947719, -0.086059509270139889,
      -0.093852481203611254, -0.10031598451451336, -0.10553777832942882,
      -0.10960320163196297, -0.11259505346162015, -0.11459349732883449,
      -0.11567598723263305, -0.11591722067140617, -0.11538912357783068,
      -0.11416085606052877, -0.11229881688739825, -0.1098666483063752,
      -0.10692528219547302, -0.10353305136428324, -0.099745799464796919,
      -0.09561688965315758, -0.091197165707451, -0.086535099565737739,
      -0.0816771907768677, -0.076668202423489817, -0.071550792212210584,
      -0.066365026888671824, -0.06114901169974904, -0.055940587363903609,
      -0.050777627443006811, -0.0456951898295261, -0.040723085605528793,
      -0.035889962360340949, -0.031231414029481062, -0.026788235842593804,
      -0.022589388524142794, -0.018643000714226789, -0.014963509606026376,
      -0.011609857250627074, -0.00866062927071455, -0.0061203950955785423,
      -0.0038991554099893776, -0.001981936438470226, -0.00059582163466634093,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      -0.0323050565315024, -0.064610113063265709, -0.096915169594427988,
      -0.1292202261248421, -0.16152528265452315, -0.19383033918380049,
      -0.22613539571292732, -0.25844045211914707, -0.28922370328625197,
      -0.31471782821875022, -0.33457463595995351, -0.3508679037496224,
      -0.36484399413264856, -0.37619961303990174, -0.38445599451693563,
      -0.38984375829498497, -0.39294016925941327, -0.39408333703885984,
      -0.39333474712015487, -0.39076204333119097, -0.38656482663111308,
      -0.38097884843171936, -0.37417613759132046, -0.36627598257877797,
      -0.35739988061178812, -0.34768692261381229, -0.33727197203930293,
      -0.32626987366285848, -0.31478082354396464, -0.3029006918932059,
      -0.29072250274809447, -0.27833207432993218, -0.26580594650584333,
      -0.25321313940561641, -0.24061720423150612, -0.22807644481515549,
      -0.21564330105426069, -0.20336434247890711, -0.19128091497932143,
      -0.17942972138042071, -0.16784304117169438, -0.15654884170272848,
      -0.14557102461444782, -0.13492977087469146, -0.12464184632059912,
      -0.11472083349536331, -0.10517734630229597, -0.096019265769318379,
      -0.087251982550574467, -0.07887862116670627, -0.070900243433544355,
      -0.063316042330143443, -0.056123531963127353, -0.049318730865126233,
      -0.042896335026579267, -0.0368498793927687, -0.031171887733885496,
      -0.025854013243608396, -0.0208871752596618, -0.016261693210136621,
      -0.011967407318628744, -0.0079937754688574, -0.0043299596151941972,
      -0.00096493375509248774, 0.00211238837430195, 0.0049130700692076026,
      0.0074481566925221196, 0.0097286743240922249, 0.011765464443608735,
      0.013568923324759065, 0.015149007597945307, 0.016515639246557398,
      0.017678895782826304, 0.018648264566853041, 0.019431635155480086,
      0.020035953413511623, 0.020469640845116908, 0.020743061294155051,
      0.020864060755691125, 0.020833697343381731, 0.020651839683587213,
      0.020329750453922837, 0.019888416895989219, 0.019332492980751379,
      0.018634193323439553, 0.017772712747549029, 0.016795389273804039,
      0.015785551239664027, 0.014717964432801645, 0.013414609421597213,
      0.011796911919650094, 0.01016093670054403, 0.0088849587423566589,
      0.0076688758860766074, 0.00554445921521554, 0.0023832865386653637, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.52359877558704193, 0.52359877559127066, 0.52359877558152945,
      0.52359877556940293, 0.52359877555752155, 0.52359877555097822,
      0.523598775548539, 0.52359877355646711, 0.49893342870231183,
      0.41320752948697465, 0.32183816828250034, 0.26408048711084137,
      0.22652378908268742, 0.18405131562214627, 0.13381902699779702,
      0.087324611693154017, 0.050186477405107489, 0.018528407434454455,
      -0.012133108774117204, -0.041698257129996051, -0.06802828290646061,
      -0.090537261335739125, -0.11025800444683308, -0.12804532589136117,
      -0.14386342637628791, -0.15742714797942411, -0.16880500931161965,
      -0.1783214721564394, -0.18621396217167313, -0.1925525925046532,
      -0.19738349378926709, -0.20082345754208036, -0.20302286687361071,
      -0.20410360131866256, -0.20415430098710857, -0.20326001500507132,
      -0.20151578572704118, -0.19901675978401817, -0.19584760167524223,
      -0.19208356597606685, -0.1877963458906714, -0.18305583237161874,
      -0.17792792222595538, -0.17247291994100544, -0.166746177788041,
      -0.16079929043960178, -0.15468037346561722, -0.14843372117670095,
      -0.14209969742918283, -0.13571503160398, -0.12931315591974946,
      -0.12292436039151337, -0.11657585610148412, -0.1102918832397735,
      -0.1040938775055012, -0.098000657061761393, -0.0920286109849572,
      -0.086191849536601292, -0.080502267018094667, -0.074969586735423435,
      -0.069601575611595481, -0.064404430592624226, -0.059382948086895961,
      -0.054540174490945136, -0.049877086500888443, -0.0453933118746176,
      -0.041088559949745994, -0.036962518187527695, -0.0330121945976682,
      -0.029230373303048163, -0.025609928586810667, -0.022150298891877897,
      -0.0188540050220954, -0.015711481820616824, -0.012696832170407778,
      -0.0097947607570860584, -0.0070291846712783384, -0.0044315852596396831,
      -0.0019611533521137108, 0.00049212870103908376, 0.0029475400517154837,
      0.005220406474682528, 0.0071531127126855379, 0.0090103876170047718,
      0.011318006678142718, 0.013962835022078832, 0.015840411042350032,
      0.016367405446306021, 0.017303394728962109, 0.021124714248879177,
      0.026219561958164314, 0.026515806303553924, 0.020680988313128638,
      0.019710211432061992, 0.034432441454323094, 0.05123613206640959,
      0.03862819160527959, 5.169878828456423E-26, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 2.0943951023481677, 1.6914908516393928E-11,
      -3.8964699307350271E-11, -4.8506492740913572E-11, -4.7525559406206548E-11,
      -2.617315095383964E-11, -9.75694836924241E-12, -7.9682871861918355E-9,
      -0.098661379416621356, -0.34290359686134858, -0.36547744481789718,
      -0.23103072468663594, -0.15022679211261578, -0.1698898938421646,
      -0.20092915449739704, -0.18597766121857195, -0.14855253715218608,
      -0.12663227988261214, -0.12264606483428664, -0.11826059342351536,
      -0.10532010310585824, -0.09003591371711403, -0.078882972444375823,
      -0.071149285778112428, -0.063272401939706929, -0.054254886412544827,
      -0.045511445328782159, -0.03806585137927905, -0.0315699600609349,
      -0.025354521331920295, -0.01932360513845555, -0.0137598550112531,
      -0.008797637326121429, -0.0043229377802074184, -0.00020279867378402938,
      0.00357714392814906, 0.0069769171121206782, 0.00999610377209209,
      0.0126766324351037, 0.015056142796701533, 0.017148880341581785,
      0.018962054076210731, 0.020511640582653465, 0.0218200091397997,
      0.022906968611857752, 0.02378754939375681, 0.024475667895938254,
      0.024986609155665144, 0.025336094990072458, 0.025538663300811289,
      0.02560750273692227, 0.025555182112944257, 0.025394017160117015,
      0.025135891446842508, 0.02479202293708916, 0.024372881774959242,
      0.023888184307216793, 0.023347045793423615, 0.022758330074026514,
      0.022130721130684903, 0.021472044495311812, 0.020788580075885025,
      0.020085930022913086, 0.01937109438380331, 0.018652351960226767,
      0.017935098505083354, 0.017219007699486446, 0.016504167048873215,
      0.015801294359437959, 0.015127285178480138, 0.01448177886495,
      0.013838518779731079, 0.013185175479129986, 0.012570092805914302,
      0.01205859860083619, 0.011608285653286875, 0.011062304343230885,
      0.01039039764655462, 0.0098817276301038891, 0.0098131282126111778,
      0.0098216454027056019, 0.0090914656918681756, 0.00773082495201204,
      0.0074290996172769394, 0.00923047624455178, 0.010579313375744453,
      0.0075103040810848131, 0.0021079776158239544, 0.0037439571306243482,
      0.015285278079668266, 0.020379390837140562, 0.0011849773815584387,
      -0.023339271961701148, -0.0038831075242665835, 0.058888920089044436,
      0.067214762448345955, -0.05043176184451998, -0.15451276642111836, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0 } ;

    helikopter3_DW.xWorkspace_PWORK.TimePtr = (void *) pTimeValues0;
    helikopter3_DW.xWorkspace_PWORK.DataPtr = (void *) pDataValues0;
    helikopter3_DW.xWorkspace_IWORK.PrevIndex = 0;
  }

  /* Start for ToFile: '<Root>/To File4' */
  {
    char fileName[509] = "helicopter3\\input3.mat";
    FILE *fp = (NULL);
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(helikopter3_M,
                        "Error creating .mat file helicopter3\\input3.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp,2,0,"input3")) {
      rtmSetErrorStatus(helikopter3_M,
                        "Error writing mat file header to file helicopter3\\input3.mat");
      return;
    }

    helikopter3_DW.ToFile4_IWORK.Count = 0;
    helikopter3_DW.ToFile4_IWORK.Decimation = -1;
    helikopter3_DW.ToFile4_PWORK.FilePtr = fp;
  }

  /* InitializeConditions for TransferFcn: '<S2>/Vandring Lavpass' */
  helikopter3_X.VandringLavpass_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S2>/Vandring Deriv' */
  helikopter3_X.VandringDeriv_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S2>/Transfer Fcn4' */
  helikopter3_X.TransferFcn4_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S2>/Transfer Fcn5' */
  helikopter3_X.TransferFcn5_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S1>/Integrator' */
  helikopter3_X.Integrator_CSTATE = helikopter3_P.Integrator_IC;
}

/* Model terminate function */
void helikopter3_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: helikopter3/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    t_uint32 num_final_pwm_outputs = 0;
    hil_task_stop_all(helikopter3_DW.HILInitialize_Card);
    hil_monitor_stop_all(helikopter3_DW.HILInitialize_Card);
    is_switching = false;
    if ((helikopter3_P.HILInitialize_set_analog_out_ex && !is_switching) ||
        (helikopter3_P.HILInitialize_set_analog_outp_c && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &helikopter3_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = helikopter3_P.HILInitialize_final_analog_outp;
        }
      }

      num_final_analog_outputs = 8U;
    }

    if ((helikopter3_P.HILInitialize_set_pwm_output_ap && !is_switching) ||
        (helikopter3_P.HILInitialize_set_pwm_outputs_p && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &helikopter3_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helikopter3_P.HILInitialize_final_pwm_outputs;
        }
      }

      num_final_pwm_outputs = 8U;
    }

    if (0
        || num_final_analog_outputs > 0
        || num_final_pwm_outputs > 0
        ) {
      /* Attempt to write the final outputs atomically (due to firmware issue in old Q2-USB). Otherwise write channels individually */
      result = hil_write(helikopter3_DW.HILInitialize_Card
                         , helikopter3_P.HILInitialize_analog_output_cha,
                         num_final_analog_outputs
                         , helikopter3_P.HILInitialize_pwm_channels,
                         num_final_pwm_outputs
                         , NULL, 0
                         , NULL, 0
                         , &helikopter3_DW.HILInitialize_AOVoltages[0]
                         , &helikopter3_DW.HILInitialize_POValues[0]
                         , (t_boolean *) NULL
                         , NULL
                         );
      if (result == -QERR_HIL_WRITE_NOT_SUPPORTED) {
        t_error local_result;
        result = 0;

        /* The hil_write operation is not supported by this card. Write final outputs for each channel type */
        if (num_final_analog_outputs > 0) {
          local_result = hil_write_analog(helikopter3_DW.HILInitialize_Card,
            helikopter3_P.HILInitialize_analog_output_cha,
            num_final_analog_outputs, &helikopter3_DW.HILInitialize_AOVoltages[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (num_final_pwm_outputs > 0) {
          local_result = hil_write_pwm(helikopter3_DW.HILInitialize_Card,
            helikopter3_P.HILInitialize_pwm_channels, num_final_pwm_outputs,
            &helikopter3_DW.HILInitialize_POValues[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(helikopter3_M, _rt_error_message);
        }
      }
    }

    hil_task_delete_all(helikopter3_DW.HILInitialize_Card);
    hil_monitor_delete_all(helikopter3_DW.HILInitialize_Card);
    hil_close(helikopter3_DW.HILInitialize_Card);
    helikopter3_DW.HILInitialize_Card = NULL;
  }

  /* Terminate for ToFile: '<Root>/To File' */
  {
    FILE *fp = (FILE *) helikopter3_DW.ToFile_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "helicopter3\\travel3.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helikopter3_M,
                          "Error closing MAT-file helicopter3\\travel3.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(helikopter3_M,
                          "Error reopening MAT-file helicopter3\\travel3.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 2, helikopter3_DW.ToFile_IWORK.Count,
           "travel3")) {
        rtmSetErrorStatus(helikopter3_M,
                          "Error writing header for travel3 to MAT-file helicopter3\\travel3.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helikopter3_M,
                          "Error closing MAT-file helicopter3\\travel3.mat");
        return;
      }

      helikopter3_DW.ToFile_PWORK.FilePtr = (NULL);
    }
  }

  /* Terminate for ToFile: '<Root>/To File1' */
  {
    FILE *fp = (FILE *) helikopter3_DW.ToFile1_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "helicopter3\\pitch3.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helikopter3_M,
                          "Error closing MAT-file helicopter3\\pitch3.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(helikopter3_M,
                          "Error reopening MAT-file helicopter3\\pitch3.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 2, helikopter3_DW.ToFile1_IWORK.Count,
           "pitch3")) {
        rtmSetErrorStatus(helikopter3_M,
                          "Error writing header for pitch3 to MAT-file helicopter3\\pitch3.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helikopter3_M,
                          "Error closing MAT-file helicopter3\\pitch3.mat");
        return;
      }

      helikopter3_DW.ToFile1_PWORK.FilePtr = (NULL);
    }
  }

  /* Terminate for ToFile: '<Root>/To File2' */
  {
    FILE *fp = (FILE *) helikopter3_DW.ToFile2_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "helicopter3\\elevation3.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helikopter3_M,
                          "Error closing MAT-file helicopter3\\elevation3.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(helikopter3_M,
                          "Error reopening MAT-file helicopter3\\elevation3.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 2, helikopter3_DW.ToFile2_IWORK.Count,
           "elevation3")) {
        rtmSetErrorStatus(helikopter3_M,
                          "Error writing header for elevation3 to MAT-file helicopter3\\elevation3.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helikopter3_M,
                          "Error closing MAT-file helicopter3\\elevation3.mat");
        return;
      }

      helikopter3_DW.ToFile2_PWORK.FilePtr = (NULL);
    }
  }

  /* Terminate for ToFile: '<Root>/To File3' */
  {
    FILE *fp = (FILE *) helikopter3_DW.ToFile3_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "helicopter3\\optinput3.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helikopter3_M,
                          "Error closing MAT-file helicopter3\\optinput3.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(helikopter3_M,
                          "Error reopening MAT-file helicopter3\\optinput3.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 2, helikopter3_DW.ToFile3_IWORK.Count,
           "optinput3")) {
        rtmSetErrorStatus(helikopter3_M,
                          "Error writing header for optinput3 to MAT-file helicopter3\\optinput3.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helikopter3_M,
                          "Error closing MAT-file helicopter3\\optinput3.mat");
        return;
      }

      helikopter3_DW.ToFile3_PWORK.FilePtr = (NULL);
    }
  }

  /* Terminate for ToFile: '<Root>/To File4' */
  {
    FILE *fp = (FILE *) helikopter3_DW.ToFile4_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "helicopter3\\input3.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helikopter3_M,
                          "Error closing MAT-file helicopter3\\input3.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(helikopter3_M,
                          "Error reopening MAT-file helicopter3\\input3.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 2, helikopter3_DW.ToFile4_IWORK.Count,
           "input3")) {
        rtmSetErrorStatus(helikopter3_M,
                          "Error writing header for input3 to MAT-file helicopter3\\input3.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helikopter3_M,
                          "Error closing MAT-file helicopter3\\input3.mat");
        return;
      }

      helikopter3_DW.ToFile4_PWORK.FilePtr = (NULL);
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
  helikopter3_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  helikopter3_update();
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
  helikopter3_initialize();
}

void MdlTerminate(void)
{
  helikopter3_terminate();
}

/* Registration function */
RT_MODEL_helikopter3_T *helikopter3(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* non-finite (run-time) assignments */
  helikopter3_P.Integrator_UpperSat = rtInf;
  helikopter3_P.Integrator_LowerSat = rtMinusInf;

  /* initialize real-time model */
  (void) memset((void *)helikopter3_M, 0,
                sizeof(RT_MODEL_helikopter3_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&helikopter3_M->solverInfo,
                          &helikopter3_M->Timing.simTimeStep);
    rtsiSetTPtr(&helikopter3_M->solverInfo, &rtmGetTPtr(helikopter3_M));
    rtsiSetStepSizePtr(&helikopter3_M->solverInfo,
                       &helikopter3_M->Timing.stepSize0);
    rtsiSetdXPtr(&helikopter3_M->solverInfo, &helikopter3_M->ModelData.derivs);
    rtsiSetContStatesPtr(&helikopter3_M->solverInfo, (real_T **)
                         &helikopter3_M->ModelData.contStates);
    rtsiSetNumContStatesPtr(&helikopter3_M->solverInfo,
      &helikopter3_M->Sizes.numContStates);
    rtsiSetErrorStatusPtr(&helikopter3_M->solverInfo, (&rtmGetErrorStatus
      (helikopter3_M)));
    rtsiSetRTModelPtr(&helikopter3_M->solverInfo, helikopter3_M);
  }

  rtsiSetSimTimeStep(&helikopter3_M->solverInfo, MAJOR_TIME_STEP);
  helikopter3_M->ModelData.intgData.f[0] = helikopter3_M->ModelData.odeF[0];
  helikopter3_M->ModelData.contStates = ((real_T *) &helikopter3_X);
  rtsiSetSolverData(&helikopter3_M->solverInfo, (void *)
                    &helikopter3_M->ModelData.intgData);
  rtsiSetSolverName(&helikopter3_M->solverInfo,"ode1");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = helikopter3_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    helikopter3_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    helikopter3_M->Timing.sampleTimes = (&helikopter3_M->
      Timing.sampleTimesArray[0]);
    helikopter3_M->Timing.offsetTimes = (&helikopter3_M->
      Timing.offsetTimesArray[0]);

    /* task periods */
    helikopter3_M->Timing.sampleTimes[0] = (0.0);
    helikopter3_M->Timing.sampleTimes[1] = (0.002);

    /* task offsets */
    helikopter3_M->Timing.offsetTimes[0] = (0.0);
    helikopter3_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(helikopter3_M, &helikopter3_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = helikopter3_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    helikopter3_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(helikopter3_M, 35.0);
  helikopter3_M->Timing.stepSize0 = 0.002;
  helikopter3_M->Timing.stepSize1 = 0.002;

  /* External mode info */
  helikopter3_M->Sizes.checksums[0] = (2851498742U);
  helikopter3_M->Sizes.checksums[1] = (2121467100U);
  helikopter3_M->Sizes.checksums[2] = (827002735U);
  helikopter3_M->Sizes.checksums[3] = (1494999245U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[1];
    helikopter3_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(helikopter3_M->extModeInfo,
      &helikopter3_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(helikopter3_M->extModeInfo,
                        helikopter3_M->Sizes.checksums);
    rteiSetTPtr(helikopter3_M->extModeInfo, rtmGetTPtr(helikopter3_M));
  }

  helikopter3_M->solverInfoPtr = (&helikopter3_M->solverInfo);
  helikopter3_M->Timing.stepSize = (0.002);
  rtsiSetFixedStepSize(&helikopter3_M->solverInfo, 0.002);
  rtsiSetSolverMode(&helikopter3_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  helikopter3_M->ModelData.blockIO = ((void *) &helikopter3_B);

  {
    helikopter3_B.KalibrerElev = 0.0;
    helikopter3_B.Add = 0.0;
    helikopter3_B.KalibrerPitch = 0.0;
    helikopter3_B.VandringLavpass = 0.0;
    helikopter3_B.uWorkspace = 0.0;
    helikopter3_B.KalibrerVandring = 0.0;
    helikopter3_B.Add1 = 0.0;
    helikopter3_B.K_ei = 0.0;
    helikopter3_B.SatB = 0.0;
    helikopter3_B.Sat = 0.0;
    helikopter3_B.Add_j = 0.0;
  }

  /* parameters */
  helikopter3_M->ModelData.defaultParam = ((real_T *)&helikopter3_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &helikopter3_X;
    helikopter3_M->ModelData.contStates = (x);
    (void) memset((void *)&helikopter3_X, 0,
                  sizeof(X_helikopter3_T));
  }

  /* states (dwork) */
  helikopter3_M->ModelData.dwork = ((void *) &helikopter3_DW);
  (void) memset((void *)&helikopter3_DW, 0,
                sizeof(DW_helikopter3_T));

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      helikopter3_DW.HILInitialize_AIMinimums[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      helikopter3_DW.HILInitialize_AIMaximums[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      helikopter3_DW.HILInitialize_AOMinimums[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      helikopter3_DW.HILInitialize_AOMaximums[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      helikopter3_DW.HILInitialize_AOVoltages[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      helikopter3_DW.HILInitialize_FilterFrequency[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      helikopter3_DW.HILInitialize_POSortedFreqs[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      helikopter3_DW.HILInitialize_POValues[i] = 0.0;
    }
  }

  helikopter3_DW.HILWriteAnalog_Buffer[0] = 0.0;
  helikopter3_DW.HILWriteAnalog_Buffer[1] = 0.0;

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    helikopter3_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 15;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.B = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.P = &rtPTransTable;
  }

  /* Initialize Sizes */
  helikopter3_M->Sizes.numContStates = (5);/* Number of continuous states */
  helikopter3_M->Sizes.numY = (0);     /* Number of model outputs */
  helikopter3_M->Sizes.numU = (0);     /* Number of model inputs */
  helikopter3_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  helikopter3_M->Sizes.numSampTimes = (2);/* Number of sample times */
  helikopter3_M->Sizes.numBlocks = (60);/* Number of blocks */
  helikopter3_M->Sizes.numBlockIO = (11);/* Number of block outputs */
  helikopter3_M->Sizes.numBlockPrms = (177);/* Sum of parameter "widths" */
  return helikopter3_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
