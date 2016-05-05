

%% problem 2
clear all;
close all;
clc;
ratio = 5;
name1 = {
    'problem2plots',
    'problem2plots_q_0.1',
    'problem2plots_q_1.0',
    'problem2plots_q_10'
    };
name2 = {
    'elevation2.mat',
    'input2.mat',
    'pitch2.mat',
    'travel2.mat'
    };
for i = 1:numel(name1)
    i=name1{i}
    for k = 1:numel(name2)
        filename = strcat('./',i,'/',name2{k});
        load(filename)
    end
    
    csvwrite_with_headers(strcat('./Export/',i,'.csv'),...
      downsample([input2(1,:)',input2(2,:)',travel2(2,:)',pitch2(2,:)',...
      elevation2(2,:)'],ratio),...
      {'t','u','lambda','p','e'},0,0);

end

%% problem 3

name1 = {
    'problem3plot',
    'problem3plot_1010_1',
    'problem3plot_1050_1',
    'problem3plot_5010_1',
    'problem3plot_10150_0.5'
    };
name2 = {
    'elevation2.mat',
    'input2.mat',
    'pitch2.mat',
    'travel2.mat',
    'optinput3.mat'
    };
for i = 1:numel(name1)
    i=name1{i}
    for k = 1:numel(name2)
        filename = strcat('./',i,'/',name2{k});
        load(filename)
    end
    
    csvwrite_with_headers(strcat('./Export/',i,'.csv'),...
      downsample([input2(1,:)',input2(2,:)',travel2(2,:)',pitch2(2,:)',...
      elevation2(2,:)',optinput3(2,:)'],ratio),...
      {'t','u','lambda','p','e','uopt'},0,0);

end

%% problem 3 second tround

name1 = {
    'LQR[1,0,10,10]',
    'LQR[1,0,10,0]',
    'LQR[5,0,0,5]',
    'LQR[10,1,5,0]'
    };
name2 = {
    'elevation3.mat',
    'input3.mat',
    'pitch3.mat',
    'travel3.mat',
    'optinput3.mat'
    };
for i = 1:numel(name1)
    i=name1{i}
    for k = 1:numel(name2)
        filename = strcat('./helicopter3/',i,'/',name2{k});
        load(filename)
    end
    
    csvwrite_with_headers(strcat('./Export/problem3_',i,'.csv'),...
      downsample([input3(1,:)',input3(2,:)',travel3(2,:)',pitch3(2,:)',...
      elevation3(2,:)',optinput3(2,:)'],ratio),...
      {'t','u','lambda','p','e','uopt'},0,0);

end

%% problem 4

ratio = 5;
name1 = {
    'problem4plot_101010_11',
    'problem4plot_111111_11',
    'problem4plot_111111_11_opt_ed_1_lambdad_1',
    'problem4plot_111111_11_opt_ed_1_pd_1',
    'problem4plot_211111_11',
    'problem4plot_511111_11',
    'problem4plot_10011111_11',
    'problem4plot_21100111_11',
    'problem4plot_100110111_11',
    'problem4plot_111111_1001',
    'problem4plot_111111_1100',
    'problem4plot_without_feedback'
    };
name2 = {
    'elevation2.mat',
    'input2.mat',
    'pitch2.mat',
    'travel2.mat',
    'optinput3.mat'
    };
for i = 1:numel(name1)
    i=name1{i}
    for k = 1:numel(name2)
        filename = strcat('./',i,'/',name2{k});
        load(filename)
    end
    
    csvwrite_with_headers(strcat('./Export/',i,'.csv'),...
      downsample([input2(1,:)',input2(2,:)',input2(3,:)',travel2(2,:)',pitch2(2,:)',...
      elevation2(2,:)',optinput3(2,:)',optinput3(3,:)'],ratio),...
      {'t','u1','u2','lambda','p','e','u1opt','u2opt'},0,0);

end

%% problem 4 second round

ratio = 5;
name1 = {
    'NoLQR',
    'NoLQR_bothconstraints',
    'NoLQR_noAdditionalConstraintsN=60',
    'NoLQR_onlyedotN=40',
    'NoLQR_onlylambdadotN=60',
    };
name2 = {
    'elevation4.mat',
    'input4.mat',
    'pitch4.mat',
    'travel4.mat',
    'optinput4.mat'
    };
for i = 1:numel(name1)
    i=name1{i}
    for k = 1:numel(name2)
        filename = strcat('./helicopter4/',i,'/',name2{k});
        load(filename)
    end
    
    csvwrite_with_headers(strcat('./Export/problem4_',i,'.csv'),...
      downsample([input4(1,:)',input4(2,:)',input4(3,:)',travel4(2,:)',pitch4(2,:)',...
      elevation4(2,:)',optinput4(2,:)',optinput4(3,:)'],ratio),...
      {'t','u1','u2','lambda','p','e','u1opt','u2opt'},0,0);

end

%% problem 4 third round

ratio = 5;
name1 = {
    'LQR_bothconstraintsN=60',
    'LQR_noadditionalN=40_active-set_t=8.0595s',
    'LQR_noadditionalN=40_sqp_t=0.33s',
    'LQR_noadditionalN=60',
    'LQR_onlyedotN=40',
    'LQR_onlylambdadotN=60_time_to_complete=553.53s',
    'LQR_onlylamdadotN=40_sqp_time=0.30s',
    'LQR_onlylamdadotN=60_sqp_time=0.4186s',
    };
name2 = {
    'elevation4.mat',
    'input4.mat',
    'pitch4.mat',
    'travel4.mat',
    'optinput4.mat'
    };
for i = 1:numel(name1)
    i=name1{i}
    for k = 1:numel(name2)
        filename = strcat('./helicopter4/',i,'/',name2{k});
        load(filename)
    end
    
    csvwrite_with_headers(strcat('./Export/problem4_',i,'.csv'),...
      downsample([input4(1,:)',input4(2,:)',input4(3,:)',travel4(2,:)',pitch4(2,:)',...
      elevation4(2,:)',optinput4(2,:)',optinput4(3,:)'],ratio),...
      {'t','u1','u2','lambda','p','e','u1opt','u2opt'},0,0);

end

%% problem 4 fourth round

ratio = 5;
name1 = {
    'LQR_bothconstraint_N=100_LQR[5,1,1,1,1,1]',
    
    };
name2 = {
    'elevation4.mat',
    'input4.mat',
    'pitch4.mat',
    'travel4.mat',
    'optinput4.mat'
    };
for i = 1:numel(name1)
    i=name1{i}
    for k = 1:numel(name2)
        filename = strcat('./helicopter4/',i,'/Data/ran35s_prettysure_it_was_ran_correctly/helicopter4/',name2{k});
        load(filename)
    end
    
    csvwrite_with_headers(strcat('./Export/problem4_',i,'.csv'),...
      downsample([input4(1,:)',input4(2,:)',input4(3,:)',travel4(2,:)',pitch4(2,:)',...
      elevation4(2,:)',optinput4(2,:)',optinput4(3,:)'],ratio),...
      {'t','u1','u2','lambda','p','e','u1opt','u2opt'},0,0);

end