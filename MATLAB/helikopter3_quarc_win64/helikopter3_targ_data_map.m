  function targMap = targDataMap(),

  ;%***********************
  ;% Create Parameter Map *
  ;%***********************
      
    nTotData      = 0; %add to this count as we go
    nTotSects     = 6;
    sectIdxOffset = 0;
    
    ;%
    ;% Define dummy sections & preallocate arrays
    ;%
    dumSection.nData = -1;  
    dumSection.data  = [];
    
    dumData.logicalSrcIdx = -1;
    dumData.dtTransOffset = -1;
    
    ;%
    ;% Init/prealloc paramMap
    ;%
    paramMap.nSections           = nTotSects;
    paramMap.sectIdxOffset       = sectIdxOffset;
      paramMap.sections(nTotSects) = dumSection; %prealloc
    paramMap.nTotData            = -1;
    
    ;%
    ;% Auto data (helikopter3_P)
    ;%
      section.nData     = 28;
      section.data(28)  = dumData; %prealloc
      
	  ;% helikopter3_P.K
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% helikopter3_P.K_ed
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 4;
	
	  ;% helikopter3_P.K_ei
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 5;
	
	  ;% helikopter3_P.K_ep
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 6;
	
	  ;% helikopter3_P.K_pd
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 7;
	
	  ;% helikopter3_P.K_pp
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 8;
	
	  ;% helikopter3_P.KalibElevasjon
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 9;
	
	  ;% helikopter3_P.KalibPitch
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 10;
	
	  ;% helikopter3_P.KalibVandring
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 11;
	
	  ;% helikopter3_P.V_b_eq
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 12;
	
	  ;% helikopter3_P.V_f_eq
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 13;
	
	  ;% helikopter3_P.HILInitialize_analog_input_maxi
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 14;
	
	  ;% helikopter3_P.HILInitialize_analog_input_mini
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 15;
	
	  ;% helikopter3_P.HILInitialize_analog_output_max
	  section.data(14).logicalSrcIdx = 13;
	  section.data(14).dtTransOffset = 16;
	
	  ;% helikopter3_P.HILInitialize_analog_output_min
	  section.data(15).logicalSrcIdx = 14;
	  section.data(15).dtTransOffset = 17;
	
	  ;% helikopter3_P.HILInitialize_final_analog_outp
	  section.data(16).logicalSrcIdx = 15;
	  section.data(16).dtTransOffset = 18;
	
	  ;% helikopter3_P.HILInitialize_final_pwm_outputs
	  section.data(17).logicalSrcIdx = 16;
	  section.data(17).dtTransOffset = 19;
	
	  ;% helikopter3_P.HILInitialize_initial_analog_ou
	  section.data(18).logicalSrcIdx = 17;
	  section.data(18).dtTransOffset = 20;
	
	  ;% helikopter3_P.HILInitialize_initial_pwm_outpu
	  section.data(19).logicalSrcIdx = 18;
	  section.data(19).dtTransOffset = 21;
	
	  ;% helikopter3_P.HILInitialize_pwm_frequency
	  section.data(20).logicalSrcIdx = 19;
	  section.data(20).dtTransOffset = 22;
	
	  ;% helikopter3_P.HILInitialize_pwm_leading_deadb
	  section.data(21).logicalSrcIdx = 20;
	  section.data(21).dtTransOffset = 23;
	
	  ;% helikopter3_P.HILInitialize_pwm_trailing_dead
	  section.data(22).logicalSrcIdx = 21;
	  section.data(22).dtTransOffset = 24;
	
	  ;% helikopter3_P.HILInitialize_set_other_outputs
	  section.data(23).logicalSrcIdx = 22;
	  section.data(23).dtTransOffset = 25;
	
	  ;% helikopter3_P.HILInitialize_set_other_outpu_m
	  section.data(24).logicalSrcIdx = 23;
	  section.data(24).dtTransOffset = 26;
	
	  ;% helikopter3_P.HILInitialize_set_other_outpu_k
	  section.data(25).logicalSrcIdx = 24;
	  section.data(25).dtTransOffset = 27;
	
	  ;% helikopter3_P.HILInitialize_set_other_outpu_j
	  section.data(26).logicalSrcIdx = 25;
	  section.data(26).dtTransOffset = 28;
	
	  ;% helikopter3_P.HILInitialize_watchdog_analog_o
	  section.data(27).logicalSrcIdx = 26;
	  section.data(27).dtTransOffset = 29;
	
	  ;% helikopter3_P.HILInitialize_watchdog_pwm_outp
	  section.data(28).logicalSrcIdx = 27;
	  section.data(28).dtTransOffset = 30;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(1) = section;
      clear section
      
      section.nData     = 7;
      section.data(7)  = dumData; %prealloc
      
	  ;% helikopter3_P.HILInitialize_hardware_clocks
	  section.data(1).logicalSrcIdx = 28;
	  section.data(1).dtTransOffset = 0;
	
	  ;% helikopter3_P.HILInitialize_initial_encoder_c
	  section.data(2).logicalSrcIdx = 29;
	  section.data(2).dtTransOffset = 3;
	
	  ;% helikopter3_P.HILInitialize_pwm_alignment
	  section.data(3).logicalSrcIdx = 30;
	  section.data(3).dtTransOffset = 4;
	
	  ;% helikopter3_P.HILInitialize_pwm_configuration
	  section.data(4).logicalSrcIdx = 31;
	  section.data(4).dtTransOffset = 5;
	
	  ;% helikopter3_P.HILInitialize_pwm_modes
	  section.data(5).logicalSrcIdx = 32;
	  section.data(5).dtTransOffset = 6;
	
	  ;% helikopter3_P.HILInitialize_pwm_polarity
	  section.data(6).logicalSrcIdx = 33;
	  section.data(6).dtTransOffset = 7;
	
	  ;% helikopter3_P.HILInitialize_watchdog_digital_
	  section.data(7).logicalSrcIdx = 34;
	  section.data(7).dtTransOffset = 8;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(2) = section;
      clear section
      
      section.nData     = 7;
      section.data(7)  = dumData; %prealloc
      
	  ;% helikopter3_P.HILInitialize_analog_input_chan
	  section.data(1).logicalSrcIdx = 35;
	  section.data(1).dtTransOffset = 0;
	
	  ;% helikopter3_P.HILInitialize_analog_output_cha
	  section.data(2).logicalSrcIdx = 36;
	  section.data(2).dtTransOffset = 8;
	
	  ;% helikopter3_P.HILReadEncoder_channels
	  section.data(3).logicalSrcIdx = 37;
	  section.data(3).dtTransOffset = 16;
	
	  ;% helikopter3_P.HILWriteAnalog_channels
	  section.data(4).logicalSrcIdx = 38;
	  section.data(4).dtTransOffset = 19;
	
	  ;% helikopter3_P.HILInitialize_encoder_channels
	  section.data(5).logicalSrcIdx = 39;
	  section.data(5).dtTransOffset = 21;
	
	  ;% helikopter3_P.HILInitialize_pwm_channels
	  section.data(6).logicalSrcIdx = 40;
	  section.data(6).dtTransOffset = 29;
	
	  ;% helikopter3_P.HILInitialize_quadrature
	  section.data(7).logicalSrcIdx = 41;
	  section.data(7).dtTransOffset = 37;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(3) = section;
      clear section
      
      section.nData     = 35;
      section.data(35)  = dumData; %prealloc
      
	  ;% helikopter3_P.HILInitialize_active
	  section.data(1).logicalSrcIdx = 42;
	  section.data(1).dtTransOffset = 0;
	
	  ;% helikopter3_P.HILInitialize_final_digital_out
	  section.data(2).logicalSrcIdx = 43;
	  section.data(2).dtTransOffset = 1;
	
	  ;% helikopter3_P.HILInitialize_initial_digital_o
	  section.data(3).logicalSrcIdx = 44;
	  section.data(3).dtTransOffset = 2;
	
	  ;% helikopter3_P.HILInitialize_set_analog_input_
	  section.data(4).logicalSrcIdx = 45;
	  section.data(4).dtTransOffset = 3;
	
	  ;% helikopter3_P.HILInitialize_set_analog_inpu_m
	  section.data(5).logicalSrcIdx = 46;
	  section.data(5).dtTransOffset = 4;
	
	  ;% helikopter3_P.HILInitialize_set_analog_output
	  section.data(6).logicalSrcIdx = 47;
	  section.data(6).dtTransOffset = 5;
	
	  ;% helikopter3_P.HILInitialize_set_analog_outp_b
	  section.data(7).logicalSrcIdx = 48;
	  section.data(7).dtTransOffset = 6;
	
	  ;% helikopter3_P.HILInitialize_set_analog_outp_e
	  section.data(8).logicalSrcIdx = 49;
	  section.data(8).dtTransOffset = 7;
	
	  ;% helikopter3_P.HILInitialize_set_analog_outp_j
	  section.data(9).logicalSrcIdx = 50;
	  section.data(9).dtTransOffset = 8;
	
	  ;% helikopter3_P.HILInitialize_set_analog_outp_c
	  section.data(10).logicalSrcIdx = 51;
	  section.data(10).dtTransOffset = 9;
	
	  ;% helikopter3_P.HILInitialize_set_analog_out_ex
	  section.data(11).logicalSrcIdx = 52;
	  section.data(11).dtTransOffset = 10;
	
	  ;% helikopter3_P.HILInitialize_set_analog_outp_p
	  section.data(12).logicalSrcIdx = 53;
	  section.data(12).dtTransOffset = 11;
	
	  ;% helikopter3_P.HILInitialize_set_clock_frequen
	  section.data(13).logicalSrcIdx = 54;
	  section.data(13).dtTransOffset = 12;
	
	  ;% helikopter3_P.HILInitialize_set_clock_frequ_e
	  section.data(14).logicalSrcIdx = 55;
	  section.data(14).dtTransOffset = 13;
	
	  ;% helikopter3_P.HILInitialize_set_clock_params_
	  section.data(15).logicalSrcIdx = 56;
	  section.data(15).dtTransOffset = 14;
	
	  ;% helikopter3_P.HILInitialize_set_clock_param_c
	  section.data(16).logicalSrcIdx = 57;
	  section.data(16).dtTransOffset = 15;
	
	  ;% helikopter3_P.HILInitialize_set_digital_outpu
	  section.data(17).logicalSrcIdx = 58;
	  section.data(17).dtTransOffset = 16;
	
	  ;% helikopter3_P.HILInitialize_set_digital_out_b
	  section.data(18).logicalSrcIdx = 59;
	  section.data(18).dtTransOffset = 17;
	
	  ;% helikopter3_P.HILInitialize_set_digital_out_c
	  section.data(19).logicalSrcIdx = 60;
	  section.data(19).dtTransOffset = 18;
	
	  ;% helikopter3_P.HILInitialize_set_digital_ou_c1
	  section.data(20).logicalSrcIdx = 61;
	  section.data(20).dtTransOffset = 19;
	
	  ;% helikopter3_P.HILInitialize_set_digital_out_a
	  section.data(21).logicalSrcIdx = 62;
	  section.data(21).dtTransOffset = 20;
	
	  ;% helikopter3_P.HILInitialize_set_digital_out_j
	  section.data(22).logicalSrcIdx = 63;
	  section.data(22).dtTransOffset = 21;
	
	  ;% helikopter3_P.HILInitialize_set_digital_out_m
	  section.data(23).logicalSrcIdx = 64;
	  section.data(23).dtTransOffset = 22;
	
	  ;% helikopter3_P.HILInitialize_set_encoder_count
	  section.data(24).logicalSrcIdx = 65;
	  section.data(24).dtTransOffset = 23;
	
	  ;% helikopter3_P.HILInitialize_set_encoder_cou_k
	  section.data(25).logicalSrcIdx = 66;
	  section.data(25).dtTransOffset = 24;
	
	  ;% helikopter3_P.HILInitialize_set_encoder_param
	  section.data(26).logicalSrcIdx = 67;
	  section.data(26).dtTransOffset = 25;
	
	  ;% helikopter3_P.HILInitialize_set_encoder_par_m
	  section.data(27).logicalSrcIdx = 68;
	  section.data(27).dtTransOffset = 26;
	
	  ;% helikopter3_P.HILInitialize_set_other_outpu_l
	  section.data(28).logicalSrcIdx = 69;
	  section.data(28).dtTransOffset = 27;
	
	  ;% helikopter3_P.HILInitialize_set_pwm_outputs_a
	  section.data(29).logicalSrcIdx = 70;
	  section.data(29).dtTransOffset = 28;
	
	  ;% helikopter3_P.HILInitialize_set_pwm_outputs_g
	  section.data(30).logicalSrcIdx = 71;
	  section.data(30).dtTransOffset = 29;
	
	  ;% helikopter3_P.HILInitialize_set_pwm_outputs_p
	  section.data(31).logicalSrcIdx = 72;
	  section.data(31).dtTransOffset = 30;
	
	  ;% helikopter3_P.HILInitialize_set_pwm_output_ap
	  section.data(32).logicalSrcIdx = 73;
	  section.data(32).dtTransOffset = 31;
	
	  ;% helikopter3_P.HILInitialize_set_pwm_outputs_o
	  section.data(33).logicalSrcIdx = 74;
	  section.data(33).dtTransOffset = 32;
	
	  ;% helikopter3_P.HILInitialize_set_pwm_params_at
	  section.data(34).logicalSrcIdx = 75;
	  section.data(34).dtTransOffset = 33;
	
	  ;% helikopter3_P.HILInitialize_set_pwm_params__f
	  section.data(35).logicalSrcIdx = 76;
	  section.data(35).dtTransOffset = 34;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(4) = section;
      clear section
      
      section.nData     = 27;
      section.data(27)  = dumData; %prealloc
      
	  ;% helikopter3_P.Constant_Value
	  section.data(1).logicalSrcIdx = 77;
	  section.data(1).dtTransOffset = 0;
	
	  ;% helikopter3_P.VandringLavpass_A
	  section.data(2).logicalSrcIdx = 78;
	  section.data(2).dtTransOffset = 1;
	
	  ;% helikopter3_P.VandringLavpass_C
	  section.data(3).logicalSrcIdx = 79;
	  section.data(3).dtTransOffset = 2;
	
	  ;% helikopter3_P.VandringDeriv_A
	  section.data(4).logicalSrcIdx = 80;
	  section.data(4).dtTransOffset = 3;
	
	  ;% helikopter3_P.VandringDeriv_C
	  section.data(5).logicalSrcIdx = 81;
	  section.data(5).dtTransOffset = 4;
	
	  ;% helikopter3_P.VandringDeriv_D
	  section.data(6).logicalSrcIdx = 82;
	  section.data(6).dtTransOffset = 5;
	
	  ;% helikopter3_P.TransferFcn4_A
	  section.data(7).logicalSrcIdx = 83;
	  section.data(7).dtTransOffset = 6;
	
	  ;% helikopter3_P.TransferFcn4_C
	  section.data(8).logicalSrcIdx = 84;
	  section.data(8).dtTransOffset = 7;
	
	  ;% helikopter3_P.TransferFcn4_D
	  section.data(9).logicalSrcIdx = 85;
	  section.data(9).dtTransOffset = 8;
	
	  ;% helikopter3_P.TransferFcn5_A
	  section.data(10).logicalSrcIdx = 86;
	  section.data(10).dtTransOffset = 9;
	
	  ;% helikopter3_P.TransferFcn5_C
	  section.data(11).logicalSrcIdx = 87;
	  section.data(11).dtTransOffset = 10;
	
	  ;% helikopter3_P.TransferFcn5_D
	  section.data(12).logicalSrcIdx = 88;
	  section.data(12).dtTransOffset = 11;
	
	  ;% helikopter3_P.Gain_Gain
	  section.data(13).logicalSrcIdx = 89;
	  section.data(13).dtTransOffset = 12;
	
	  ;% helikopter3_P.Constant_Value_b
	  section.data(14).logicalSrcIdx = 90;
	  section.data(14).dtTransOffset = 48;
	
	  ;% helikopter3_P.Integrator_IC
	  section.data(15).logicalSrcIdx = 91;
	  section.data(15).dtTransOffset = 49;
	
	  ;% helikopter3_P.Integrator_UpperSat
	  section.data(16).logicalSrcIdx = 92;
	  section.data(16).dtTransOffset = 50;
	
	  ;% helikopter3_P.Integrator_LowerSat
	  section.data(17).logicalSrcIdx = 93;
	  section.data(17).dtTransOffset = 51;
	
	  ;% helikopter3_P.elevation_Value
	  section.data(18).logicalSrcIdx = 94;
	  section.data(18).dtTransOffset = 52;
	
	  ;% helikopter3_P.Saturation_UpperSat
	  section.data(19).logicalSrcIdx = 95;
	  section.data(19).dtTransOffset = 53;
	
	  ;% helikopter3_P.Saturation_LowerSat
	  section.data(20).logicalSrcIdx = 96;
	  section.data(20).dtTransOffset = 54;
	
	  ;% helikopter3_P.Saturation_UpperSat_d
	  section.data(21).logicalSrcIdx = 97;
	  section.data(21).dtTransOffset = 55;
	
	  ;% helikopter3_P.Saturation_LowerSat_n
	  section.data(22).logicalSrcIdx = 98;
	  section.data(22).dtTransOffset = 56;
	
	  ;% helikopter3_P.SatB_UpperSat
	  section.data(23).logicalSrcIdx = 99;
	  section.data(23).dtTransOffset = 57;
	
	  ;% helikopter3_P.SatB_LowerSat
	  section.data(24).logicalSrcIdx = 100;
	  section.data(24).dtTransOffset = 58;
	
	  ;% helikopter3_P.Sat_UpperSat
	  section.data(25).logicalSrcIdx = 101;
	  section.data(25).dtTransOffset = 59;
	
	  ;% helikopter3_P.Sat_LowerSat
	  section.data(26).logicalSrcIdx = 102;
	  section.data(26).dtTransOffset = 60;
	
	  ;% helikopter3_P.elevation_Value_g
	  section.data(27).logicalSrcIdx = 103;
	  section.data(27).dtTransOffset = 61;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(5) = section;
      clear section
      
      section.nData     = 2;
      section.data(2)  = dumData; %prealloc
      
	  ;% helikopter3_P.HILReadEncoder_Active
	  section.data(1).logicalSrcIdx = 104;
	  section.data(1).dtTransOffset = 0;
	
	  ;% helikopter3_P.HILWriteAnalog_Active
	  section.data(2).logicalSrcIdx = 105;
	  section.data(2).dtTransOffset = 1;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(6) = section;
      clear section
      
    
      ;%
      ;% Non-auto Data (parameter)
      ;%
    

    ;%
    ;% Add final counts to struct.
    ;%
    paramMap.nTotData = nTotData;
    


  ;%**************************
  ;% Create Block Output Map *
  ;%**************************
      
    nTotData      = 0; %add to this count as we go
    nTotSects     = 1;
    sectIdxOffset = 0;
    
    ;%
    ;% Define dummy sections & preallocate arrays
    ;%
    dumSection.nData = -1;  
    dumSection.data  = [];
    
    dumData.logicalSrcIdx = -1;
    dumData.dtTransOffset = -1;
    
    ;%
    ;% Init/prealloc sigMap
    ;%
    sigMap.nSections           = nTotSects;
    sigMap.sectIdxOffset       = sectIdxOffset;
      sigMap.sections(nTotSects) = dumSection; %prealloc
    sigMap.nTotData            = -1;
    
    ;%
    ;% Auto data (helikopter3_B)
    ;%
      section.nData     = 11;
      section.data(11)  = dumData; %prealloc
      
	  ;% helikopter3_B.KalibrerElev
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% helikopter3_B.Add
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% helikopter3_B.KalibrerPitch
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% helikopter3_B.VandringLavpass
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 3;
	
	  ;% helikopter3_B.uWorkspace
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 4;
	
	  ;% helikopter3_B.KalibrerVandring
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 5;
	
	  ;% helikopter3_B.Add1
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 6;
	
	  ;% helikopter3_B.K_ei
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 7;
	
	  ;% helikopter3_B.SatB
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 8;
	
	  ;% helikopter3_B.Sat
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 9;
	
	  ;% helikopter3_B.Add_j
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 10;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(1) = section;
      clear section
      
    
      ;%
      ;% Non-auto Data (signal)
      ;%
    

    ;%
    ;% Add final counts to struct.
    ;%
    sigMap.nTotData = nTotData;
    


  ;%*******************
  ;% Create DWork Map *
  ;%*******************
      
    nTotData      = 0; %add to this count as we go
    nTotSects     = 6;
    sectIdxOffset = 1;
    
    ;%
    ;% Define dummy sections & preallocate arrays
    ;%
    dumSection.nData = -1;  
    dumSection.data  = [];
    
    dumData.logicalSrcIdx = -1;
    dumData.dtTransOffset = -1;
    
    ;%
    ;% Init/prealloc dworkMap
    ;%
    dworkMap.nSections           = nTotSects;
    dworkMap.sectIdxOffset       = sectIdxOffset;
      dworkMap.sections(nTotSects) = dumSection; %prealloc
    dworkMap.nTotData            = -1;
    
    ;%
    ;% Auto data (helikopter3_DW)
    ;%
      section.nData     = 9;
      section.data(9)  = dumData; %prealloc
      
	  ;% helikopter3_DW.HILInitialize_AIMinimums
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% helikopter3_DW.HILInitialize_AIMaximums
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 8;
	
	  ;% helikopter3_DW.HILInitialize_AOMinimums
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 16;
	
	  ;% helikopter3_DW.HILInitialize_AOMaximums
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 24;
	
	  ;% helikopter3_DW.HILInitialize_AOVoltages
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 32;
	
	  ;% helikopter3_DW.HILInitialize_FilterFrequency
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 40;
	
	  ;% helikopter3_DW.HILInitialize_POSortedFreqs
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 48;
	
	  ;% helikopter3_DW.HILInitialize_POValues
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 56;
	
	  ;% helikopter3_DW.HILWriteAnalog_Buffer
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 64;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(1) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% helikopter3_DW.HILInitialize_Card
	  section.data(1).logicalSrcIdx = 9;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(2) = section;
      clear section
      
      section.nData     = 22;
      section.data(22)  = dumData; %prealloc
      
	  ;% helikopter3_DW.HILReadEncoder_PWORK
	  section.data(1).logicalSrcIdx = 10;
	  section.data(1).dtTransOffset = 0;
	
	  ;% helikopter3_DW.Elevation_PWORK.LoggedData
	  section.data(2).logicalSrcIdx = 11;
	  section.data(2).dtTransOffset = 1;
	
	  ;% helikopter3_DW.Pitch_PWORK.LoggedData
	  section.data(3).logicalSrcIdx = 12;
	  section.data(3).dtTransOffset = 2;
	
	  ;% helikopter3_DW.ToFile_PWORK.FilePtr
	  section.data(4).logicalSrcIdx = 13;
	  section.data(4).dtTransOffset = 3;
	
	  ;% helikopter3_DW.ToFile1_PWORK.FilePtr
	  section.data(5).logicalSrcIdx = 14;
	  section.data(5).dtTransOffset = 4;
	
	  ;% helikopter3_DW.ToFile2_PWORK.FilePtr
	  section.data(6).logicalSrcIdx = 15;
	  section.data(6).dtTransOffset = 5;
	
	  ;% helikopter3_DW.uWorkspace_PWORK.TimePtr
	  section.data(7).logicalSrcIdx = 16;
	  section.data(7).dtTransOffset = 6;
	
	  ;% helikopter3_DW.ToFile3_PWORK.FilePtr
	  section.data(8).logicalSrcIdx = 17;
	  section.data(8).dtTransOffset = 7;
	
	  ;% helikopter3_DW.xWorkspace_PWORK.TimePtr
	  section.data(9).logicalSrcIdx = 18;
	  section.data(9).dtTransOffset = 8;
	
	  ;% helikopter3_DW.ToFile4_PWORK.FilePtr
	  section.data(10).logicalSrcIdx = 19;
	  section.data(10).dtTransOffset = 9;
	
	  ;% helikopter3_DW.ToWorkspace_PWORK.LoggedData
	  section.data(11).logicalSrcIdx = 20;
	  section.data(11).dtTransOffset = 10;
	
	  ;% helikopter3_DW.ToWorkspace1_PWORK.LoggedData
	  section.data(12).logicalSrcIdx = 21;
	  section.data(12).dtTransOffset = 11;
	
	  ;% helikopter3_DW.ToWorkspace2_PWORK.LoggedData
	  section.data(13).logicalSrcIdx = 22;
	  section.data(13).dtTransOffset = 12;
	
	  ;% helikopter3_DW.Travel_PWORK.LoggedData
	  section.data(14).logicalSrcIdx = 23;
	  section.data(14).dtTransOffset = 13;
	
	  ;% helikopter3_DW.Elevasjon_PWORK.LoggedData
	  section.data(15).logicalSrcIdx = 24;
	  section.data(15).dtTransOffset = 14;
	
	  ;% helikopter3_DW.Pitch_PWORK_h.LoggedData
	  section.data(16).logicalSrcIdx = 25;
	  section.data(16).dtTransOffset = 15;
	
	  ;% helikopter3_DW.Vandring_PWORK.LoggedData
	  section.data(17).logicalSrcIdx = 26;
	  section.data(17).dtTransOffset = 16;
	
	  ;% helikopter3_DW.Bakmotorvolts_PWORK.LoggedData
	  section.data(18).logicalSrcIdx = 27;
	  section.data(18).dtTransOffset = 17;
	
	  ;% helikopter3_DW.Frontmotorvolt_PWORK.LoggedData
	  section.data(19).logicalSrcIdx = 28;
	  section.data(19).dtTransOffset = 18;
	
	  ;% helikopter3_DW.HILWriteAnalog_PWORK
	  section.data(20).logicalSrcIdx = 29;
	  section.data(20).dtTransOffset = 19;
	
	  ;% helikopter3_DW.v_back_PWORK.LoggedData
	  section.data(21).logicalSrcIdx = 30;
	  section.data(21).dtTransOffset = 20;
	
	  ;% helikopter3_DW.v_front1_PWORK.LoggedData
	  section.data(22).logicalSrcIdx = 31;
	  section.data(22).dtTransOffset = 21;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(3) = section;
      clear section
      
      section.nData     = 7;
      section.data(7)  = dumData; %prealloc
      
	  ;% helikopter3_DW.HILInitialize_ClockModes
	  section.data(1).logicalSrcIdx = 32;
	  section.data(1).dtTransOffset = 0;
	
	  ;% helikopter3_DW.HILInitialize_QuadratureModes
	  section.data(2).logicalSrcIdx = 33;
	  section.data(2).dtTransOffset = 3;
	
	  ;% helikopter3_DW.HILInitialize_InitialEICounts
	  section.data(3).logicalSrcIdx = 34;
	  section.data(3).dtTransOffset = 11;
	
	  ;% helikopter3_DW.HILInitialize_POModeValues
	  section.data(4).logicalSrcIdx = 35;
	  section.data(4).dtTransOffset = 19;
	
	  ;% helikopter3_DW.HILInitialize_POAlignValues
	  section.data(5).logicalSrcIdx = 36;
	  section.data(5).dtTransOffset = 27;
	
	  ;% helikopter3_DW.HILInitialize_POPolarityVals
	  section.data(6).logicalSrcIdx = 37;
	  section.data(6).dtTransOffset = 35;
	
	  ;% helikopter3_DW.HILReadEncoder_Buffer
	  section.data(7).logicalSrcIdx = 38;
	  section.data(7).dtTransOffset = 43;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(4) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% helikopter3_DW.HILInitialize_POSortedChans
	  section.data(1).logicalSrcIdx = 39;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(5) = section;
      clear section
      
      section.nData     = 7;
      section.data(7)  = dumData; %prealloc
      
	  ;% helikopter3_DW.ToFile_IWORK.Count
	  section.data(1).logicalSrcIdx = 40;
	  section.data(1).dtTransOffset = 0;
	
	  ;% helikopter3_DW.ToFile1_IWORK.Count
	  section.data(2).logicalSrcIdx = 41;
	  section.data(2).dtTransOffset = 1;
	
	  ;% helikopter3_DW.ToFile2_IWORK.Count
	  section.data(3).logicalSrcIdx = 42;
	  section.data(3).dtTransOffset = 2;
	
	  ;% helikopter3_DW.uWorkspace_IWORK.PrevIndex
	  section.data(4).logicalSrcIdx = 43;
	  section.data(4).dtTransOffset = 3;
	
	  ;% helikopter3_DW.ToFile3_IWORK.Count
	  section.data(5).logicalSrcIdx = 44;
	  section.data(5).dtTransOffset = 4;
	
	  ;% helikopter3_DW.xWorkspace_IWORK.PrevIndex
	  section.data(6).logicalSrcIdx = 45;
	  section.data(6).dtTransOffset = 5;
	
	  ;% helikopter3_DW.ToFile4_IWORK.Count
	  section.data(7).logicalSrcIdx = 46;
	  section.data(7).dtTransOffset = 6;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(6) = section;
      clear section
      
    
      ;%
      ;% Non-auto Data (dwork)
      ;%
    

    ;%
    ;% Add final counts to struct.
    ;%
    dworkMap.nTotData = nTotData;
    


  ;%
  ;% Add individual maps to base struct.
  ;%

  targMap.paramMap  = paramMap;    
  targMap.signalMap = sigMap;
  targMap.dworkMap  = dworkMap;
  
  ;%
  ;% Add checksums to base struct.
  ;%


  targMap.checksum0 = 2851498742;
  targMap.checksum1 = 2121467100;
  targMap.checksum2 = 827002735;
  targMap.checksum3 = 1494999245;

