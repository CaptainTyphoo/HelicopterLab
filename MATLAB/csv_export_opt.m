
%%
csvwrite_with_headers(strcat('./Export/problem2plots_opt.csv'),...
      [t',u,x1,x3],...
      {'t','u','lambda','p'},0,0);
  
%%
csvwrite_with_headers(strcat('./Export/problem2plots_q_0.1_opt.csv'),...
      [t',u,x1,x3],...
      {'t','u','lambda','p'},0,0);
%%
csvwrite_with_headers(strcat('./Export/problem2plots_q_1.0_opt.csv'),...
      [t',u,x1,x3],...
      {'t','u','lambda','p'},0,0);
%%
csvwrite_with_headers(strcat('./Export/problem2plots_q_10_opt.csv'),...
      [t',u,x1,x3],...
      {'t','u','lambda','p'},0,0);

%%
csvwrite_with_headers(strcat('./Export/problem4plots_opt.csv'),...
      [t',u1,u2,x1,x3,x5],...
      {'t','u1','u2','lambda','p','e'},0,0);

%%
csvwrite_with_headers(strcat('./Export/problem4plots_ed_1_lambdad_1_opt.csv'),...
      [t',u1,u2,x1,x3,x5],...
      {'t','u1','u2','lambda','p','e'},0,0);

%%
csvwrite_with_headers(strcat('./Export/problem4plots_ed_1_pd_1_opt.csv'),...
      [t',u1,u2,x1,x3,x5],...
      {'t','u1','u2','lambda','p','e'},0,0);
  
%% 
csvwrite_with_headers(strcat('./Export/problem4plots_bothconstraints_opt.csv'),...
      [t',u1,u2,x1,x3,x5],...
      {'t','u1','u2','lambda','p','e'},0,0);
  
%% 
csvwrite_with_headers(strcat('./Export/problem4plots_NoLQR_onlylambdadotN=60_opt.csv'),...
      [t',u1,u2,x1,x3,x5],...
      {'t','u1','u2','lambda','p','e'},0,0);
  
%% 
csvwrite_with_headers(strcat('./Export/problem4plots_NoLQR_onlyedotN=40_opt.csv'),...
      [t',u1,u2,x1,x3,x5],...
      {'t','u1','u2','lambda','p','e'},0,0);

%% 
csvwrite_with_headers(strcat('./Export/problem4plots_LQR_bothconstraintsN=60_opt.csv'),...
      [t',u1,u2,x1,x3,x5],...
      {'t','u1','u2','lambda','p','e'},0,0);
%% 
csvwrite_with_headers(strcat('./Export/problem4plots_LQR_noadditionalN=40_active-set_t=8.0595s_opt.csv'),...
      [t',u1,u2,x1,x3,x5],...
      {'t','u1','u2','lambda','p','e'},0,0);
%% 
csvwrite_with_headers(strcat('./Export/problem4plots_LQR_noadditionalN=40_sqp_t=0.33s_opt.csv'),...
      [t',u1,u2,x1,x3,x5],...
      {'t','u1','u2','lambda','p','e'},0,0);
%% 
csvwrite_with_headers(strcat('./Export/problem4plots_LQR_noadditionalN=60_opt.csv'),...
      [t',u1,u2,x1,x3,x5],...
      {'t','u1','u2','lambda','p','e'},0,0);
%% 
csvwrite_with_headers(strcat('./Export/problem4plots_LQR_onlyedotN=40_opt.csv'),...
      [t',u1,u2,x1,x3,x5],...
      {'t','u1','u2','lambda','p','e'},0,0);
%% 
csvwrite_with_headers(strcat('./Export/problem4plots_LQR_onlylambdadotN=60_time_to_complete=553.53s_opt.csv'),...
      [t',u1,u2,x1,x3,x5],...
      {'t','u1','u2','lambda','p','e'},0,0);
%% 
csvwrite_with_headers(strcat('./Export/problem4plots_LQR_onlylamdadotN=40_sqp_time=0.30s_opt.csv'),...
      [t',u1,u2,x1,x3,x5],...
      {'t','u1','u2','lambda','p','e'},0,0);
%% 
csvwrite_with_headers(strcat('./Export/problem4plots_LQR_onlylamdadotN=60_sqp_time=0.4186s_opt.csv'),...
      [t',u1,u2,x1,x3,x5],...
      {'t','u1','u2','lambda','p','e'},0,0);
