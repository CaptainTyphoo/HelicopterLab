/*
 * helikopter3_data.c
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

/* Block parameters (auto storage) */
P_helikopter3_T helikopter3_P = {
  /*  Variable: K
   * Referenced by: '<S3>/Gain'
   */
  { -0.54449014440016053, -1.7540124796029608, -0.36359658991534327,
    0.1022435156652908 },
  8.0,                                 /* Variable: K_ed
                                        * Referenced by: '<S1>/K_ed'
                                        */
  4.5,                                 /* Variable: K_ei
                                        * Referenced by: '<S1>/K_ei'
                                        */
  10.0,                                /* Variable: K_ep
                                        * Referenced by: '<S1>/K_ep'
                                        */
  2.7840943957927897,                  /* Variable: K_pd
                                        * Referenced by: '<S4>/K_pd'
                                        */
  19.765266348354594,                  /* Variable: K_pp
                                        * Referenced by: '<S4>/K_pp'
                                        */
  -0.1089,                             /* Variable: KalibElevasjon
                                        * Referenced by: '<S2>/Kalibrer-Elev'
                                        */
  0.0879,                              /* Variable: KalibPitch
                                        * Referenced by: '<S2>/Kalibrer-Pitch'
                                        */
  0.04395,                             /* Variable: KalibVandring
                                        * Referenced by: '<S2>/Kalibrer -Vandring'
                                        */
  0.515,                               /* Variable: V_b_eq
                                        * Referenced by: '<S5>/Gain2'
                                        */
  0.5,                                 /* Variable: V_f_eq
                                        * Referenced by: '<S5>/Gain1'
                                        */
  10.0,                                /* Mask Parameter: HILInitialize_analog_input_maxi
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  -10.0,                               /* Mask Parameter: HILInitialize_analog_input_mini
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  10.0,                                /* Mask Parameter: HILInitialize_analog_output_max
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  -10.0,                               /* Mask Parameter: HILInitialize_analog_output_min
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  0.0,                                 /* Mask Parameter: HILInitialize_final_analog_outp
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  0.0,                                 /* Mask Parameter: HILInitialize_final_pwm_outputs
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  0.0,                                 /* Mask Parameter: HILInitialize_initial_analog_ou
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  0.0,                                 /* Mask Parameter: HILInitialize_initial_pwm_outpu
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  24305.934065934067,                  /* Mask Parameter: HILInitialize_pwm_frequency
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  0.0,                                 /* Mask Parameter: HILInitialize_pwm_leading_deadb
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  0.0,                                 /* Mask Parameter: HILInitialize_pwm_trailing_dead
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  0.0,                                 /* Mask Parameter: HILInitialize_set_other_outputs
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  0.0,                                 /* Mask Parameter: HILInitialize_set_other_outpu_m
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  0.0,                                 /* Mask Parameter: HILInitialize_set_other_outpu_k
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  0.0,                                 /* Mask Parameter: HILInitialize_set_other_outpu_j
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  0.0,                                 /* Mask Parameter: HILInitialize_watchdog_analog_o
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  0.0,                                 /* Mask Parameter: HILInitialize_watchdog_pwm_outp
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */

  /*  Mask Parameter: HILInitialize_hardware_clocks
   * Referenced by: '<Root>/HIL Initialize'
   */
  { 0, 1, 2 },
  0,                                   /* Mask Parameter: HILInitialize_initial_encoder_c
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  0,                                   /* Mask Parameter: HILInitialize_pwm_alignment
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  0,                                   /* Mask Parameter: HILInitialize_pwm_configuration
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  0,                                   /* Mask Parameter: HILInitialize_pwm_modes
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  1,                                   /* Mask Parameter: HILInitialize_pwm_polarity
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  1,                                   /* Mask Parameter: HILInitialize_watchdog_digital_
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */

  /*  Mask Parameter: HILInitialize_analog_input_chan
   * Referenced by: '<Root>/HIL Initialize'
   */
  { 0U, 1U, 2U, 3U, 4U, 5U, 6U, 7U },

  /*  Mask Parameter: HILInitialize_analog_output_cha
   * Referenced by: '<Root>/HIL Initialize'
   */
  { 0U, 1U, 2U, 3U, 4U, 5U, 6U, 7U },

  /*  Mask Parameter: HILReadEncoder_channels
   * Referenced by: '<S2>/HIL Read Encoder'
   */
  { 0U, 1U, 2U },

  /*  Mask Parameter: HILWriteAnalog_channels
   * Referenced by: '<S2>/HIL Write Analog'
   */
  { 1U, 0U },

  /*  Mask Parameter: HILInitialize_encoder_channels
   * Referenced by: '<Root>/HIL Initialize'
   */
  { 0U, 1U, 2U, 3U, 4U, 5U, 6U, 7U },

  /*  Mask Parameter: HILInitialize_pwm_channels
   * Referenced by: '<Root>/HIL Initialize'
   */
  { 0U, 1U, 2U, 3U, 4U, 5U, 6U, 7U },
  4U,                                  /* Mask Parameter: HILInitialize_quadrature
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  0,                                   /* Mask Parameter: HILInitialize_active
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  1,                                   /* Mask Parameter: HILInitialize_final_digital_out
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  1,                                   /* Mask Parameter: HILInitialize_initial_digital_o
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  1,                                   /* Mask Parameter: HILInitialize_set_analog_input_
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  0,                                   /* Mask Parameter: HILInitialize_set_analog_inpu_m
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  1,                                   /* Mask Parameter: HILInitialize_set_analog_output
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  0,                                   /* Mask Parameter: HILInitialize_set_analog_outp_b
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  1,                                   /* Mask Parameter: HILInitialize_set_analog_outp_e
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  0,                                   /* Mask Parameter: HILInitialize_set_analog_outp_j
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  0,                                   /* Mask Parameter: HILInitialize_set_analog_outp_c
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  1,                                   /* Mask Parameter: HILInitialize_set_analog_out_ex
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  0,                                   /* Mask Parameter: HILInitialize_set_analog_outp_p
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  0,                                   /* Mask Parameter: HILInitialize_set_clock_frequen
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  0,                                   /* Mask Parameter: HILInitialize_set_clock_frequ_e
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  0,                                   /* Mask Parameter: HILInitialize_set_clock_params_
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  0,                                   /* Mask Parameter: HILInitialize_set_clock_param_c
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  0,                                   /* Mask Parameter: HILInitialize_set_digital_outpu
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  0,                                   /* Mask Parameter: HILInitialize_set_digital_out_b
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  1,                                   /* Mask Parameter: HILInitialize_set_digital_out_c
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  0,                                   /* Mask Parameter: HILInitialize_set_digital_ou_c1
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  0,                                   /* Mask Parameter: HILInitialize_set_digital_out_a
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  1,                                   /* Mask Parameter: HILInitialize_set_digital_out_j
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  0,                                   /* Mask Parameter: HILInitialize_set_digital_out_m
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  1,                                   /* Mask Parameter: HILInitialize_set_encoder_count
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  0,                                   /* Mask Parameter: HILInitialize_set_encoder_cou_k
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  1,                                   /* Mask Parameter: HILInitialize_set_encoder_param
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  0,                                   /* Mask Parameter: HILInitialize_set_encoder_par_m
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  0,                                   /* Mask Parameter: HILInitialize_set_other_outpu_l
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  1,                                   /* Mask Parameter: HILInitialize_set_pwm_outputs_a
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  0,                                   /* Mask Parameter: HILInitialize_set_pwm_outputs_g
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  0,                                   /* Mask Parameter: HILInitialize_set_pwm_outputs_p
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  1,                                   /* Mask Parameter: HILInitialize_set_pwm_output_ap
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  0,                                   /* Mask Parameter: HILInitialize_set_pwm_outputs_o
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  1,                                   /* Mask Parameter: HILInitialize_set_pwm_params_at
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  0,                                   /* Mask Parameter: HILInitialize_set_pwm_params__f
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  -30.0,                               /* Expression: -30
                                        * Referenced by: '<Root>/Constant'
                                        */
  -50.0,                               /* Computed Parameter: VandringLavpass_A
                                        * Referenced by: '<S2>/Vandring Lavpass'
                                        */
  50.0,                                /* Computed Parameter: VandringLavpass_C
                                        * Referenced by: '<S2>/Vandring Lavpass'
                                        */
  -20.0,                               /* Computed Parameter: VandringDeriv_A
                                        * Referenced by: '<S2>/Vandring Deriv'
                                        */
  -400.0,                              /* Computed Parameter: VandringDeriv_C
                                        * Referenced by: '<S2>/Vandring Deriv'
                                        */
  20.0,                                /* Computed Parameter: VandringDeriv_D
                                        * Referenced by: '<S2>/Vandring Deriv'
                                        */
  -100.0,                              /* Computed Parameter: TransferFcn4_A
                                        * Referenced by: '<S2>/Transfer Fcn4'
                                        */
  -10000.0,                            /* Computed Parameter: TransferFcn4_C
                                        * Referenced by: '<S2>/Transfer Fcn4'
                                        */
  100.0,                               /* Computed Parameter: TransferFcn4_D
                                        * Referenced by: '<S2>/Transfer Fcn4'
                                        */
  -50.0,                               /* Computed Parameter: TransferFcn5_A
                                        * Referenced by: '<S2>/Transfer Fcn5'
                                        */
  -2500.0,                             /* Computed Parameter: TransferFcn5_C
                                        * Referenced by: '<S2>/Transfer Fcn5'
                                        */
  50.0,                                /* Computed Parameter: TransferFcn5_D
                                        * Referenced by: '<S2>/Transfer Fcn5'
                                        */

  /*  Expression: eye(6)*pi/180
   * Referenced by: '<Root>/Gain'
   */
  { 0.017453292519943295, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.017453292519943295,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.017453292519943295, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.017453292519943295, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.017453292519943295, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.017453292519943295 },
  3.1415926535897931,                  /* Expression: pi
                                        * Referenced by: '<S3>/Constant'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S1>/Integrator'
                                        */
  0.0,                                 /* Expression: inf
                                        * Referenced by: '<S1>/Integrator'
                                        */
  0.0,                                 /* Expression: -inf
                                        * Referenced by: '<S1>/Integrator'
                                        */
  0.087266462599716474,                /* Expression: 5*pi/180
                                        * Referenced by: '<Root>/elevation'
                                        */
  10.0,                                /* Expression: 10
                                        * Referenced by: '<S1>/Saturation'
                                        */
  -10.0,                               /* Expression: -10
                                        * Referenced by: '<S1>/Saturation'
                                        */
  0.87266462599716477,                 /* Expression: 50*pi/180
                                        * Referenced by: '<S4>/Saturation'
                                        */
  -0.87266462599716477,                /* Expression: -50*pi/180
                                        * Referenced by: '<S4>/Saturation'
                                        */
  5.0,                                 /* Expression: 5
                                        * Referenced by: '<S2>/Sat B'
                                        */
  -5.0,                                /* Expression: -5
                                        * Referenced by: '<S2>/Sat B'
                                        */
  5.0,                                 /* Expression: 5
                                        * Referenced by: '<S2>/Sat'
                                        */
  -5.0,                                /* Expression: -5
                                        * Referenced by: '<S2>/Sat'
                                        */
  0.6,                                 /* Expression: 0.6
                                        * Referenced by: '<S2>/elevation'
                                        */
  1,                                   /* Computed Parameter: HILReadEncoder_Active
                                        * Referenced by: '<S2>/HIL Read Encoder'
                                        */
  0                                    /* Computed Parameter: HILWriteAnalog_Active
                                        * Referenced by: '<S2>/HIL Write Analog'
                                        */
};
