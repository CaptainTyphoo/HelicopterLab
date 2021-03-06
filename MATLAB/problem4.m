% ****************************************************
% *                                                  *
% *       Optimization and Control                   *
% *                                                  *
% *       Helikopterlab                              *
% *                                                  *
% * problem4.m                                       *
% *                                                  *
% *                                                  *
% * Updated on 04/2009 by Agus Ismail Hasan          *
% *                                                  *
% ****************************************************

init01;
delta_t	  = 0.25;	                   % sampling time
sek_forst = 5;

% System model. x=[lambda r p p_dot e e_dot]'
% u = [p_c, e_c]

Ac = [ 0 1 0 0 0 0; 
       0 0 -K_2 0 0 0; 
       0 0 0 1 0 0; 
       0 0 -K_1*K_pp -K_1*K_pd 0 0
       0 0 0 0 0 1;
       0 0 0 0 -K_3*K_ep, -K_3*K_ed];
Bc = [0 0; 
      0 0 ; 
      0 0 ; 
      K_1*K_pp 0; 
      0 0; 
      0 K_3*K_ep];

A1 = eye(6) + Ac*delta_t;
B1 = Bc*delta_t;

% Number of states and inputs

mx = size(A1,2);  % Number of states
mu = size(B1,2);  % Number of inputs

% Initial values

x1_0 = pi;                              % Lambda
x2_0 = 0;                               % r
x3_0 = 0;                               % p
x4_0 = 0;                               % p_dot
x5_0 = 0;                               % e
x6_0 = 0;                               % e_dot
x0 = [x1_0 x2_0 x3_0 x4_0 x5_0 x6_0]'; %Initial values
xf = [0 0 0 0 0 0]';% final values

% Time horizon and initialization

N  = 60;         % Time horizon for states
M  = N;          % Time horizon for inputs
z  = [x0; kron(ones(N-1,1), [0;0;0;0;0;0.1]); ...
    kron(ones(N,1), [0;0.1])];
z0 = z;          % Initial value for optimization

% Bounds

ul 	   = [-30*pi/180; -60*pi/180]; % Lower bound on u
uu 	   = [30*pi/180; 60*pi/180];   % Upper bound on u

xl     = -Inf*ones(mx,1); % Lower bound on states
xu     = Inf*ones(mx,1);  % Upper bound on states
xl(3)  = ul(1);           % Lower bound on state x3
xu(3)  = uu(1);           % Upper bound on state x3
%xl(2)   = -0.15;
%xu(2)   = 0.15;
%xl(6)   = -0.12;
%xu(6)   = 0.12;

% Generate constraints on measurements and inputs

vlb         = [kron(ones(N,1),xl);kron(ones(N,1),ul)];
vub         = [kron(ones(N,1),xu);kron(ones(N,1),uu)];
vlb(N*mx+M*mu) = 0; %We want the last input to be zero
vub(N*mx+M*mu) = 0; %We want the last input to be zero


% Generate the matrix Q and the vector c

Q1 = zeros(mx,mx);
Q1(1,1) = 1;                     % Weight on state x1
%Q1(2,2) = ;                     % Weight on state x2
Q1(3,3) = 0;                     % Weight on state x3
%Q1(4,4) = ;                     % Weight on state x4
P1 = diag([1,2]);                % Weight on input
Q = genq2(Q1,P1,N,M,mu);         % Generate Q
c = zeros(N*mx+M*mu,1);          % Generate c

% Generate system matrixes for linear model
Aeq = gena2(A1,B1,N,mx,mu);
Aeq = [ Aeq; [zeros(mx,(N-1)*mx), eye(6), ...
    zeros(mx,N*mu)]];

beq = [A1*x0; zeros((N-1)*mx,1); xf];     % Generate b

% Solve nonlinear problem with linear model
phi = @ (x) (x'*Q*x);
options = optimset('Display','notify', ...
    'Diagnostics','on',...
    'MaxFunEvals',Inf,'MaxIter',Inf);
tic
[z, lambda] = fmincon(phi, z0,[],[],Aeq,beq,vlb,...
    vub,@constr4,options);
t1=toc


% Calculate objective value

phi1 = 0.0;
PhiOut = zeros(N*mx+M*mu,1);
for i=1:N*mx+M*mu
  phi1=phi1+Q(i,i)*z(i)*z(i);
  PhiOut(i) = phi1;
end

% Extract control inputs and states

u1 = [z(N*mx+1:mu:N*mx+M*mu);z(N*mx+M*mu-1)];
u2 = [z(N*mx+2:mu:N*mx+M*mu);z(N*mx+M*mu)];

x1 = [x0(1);z(1:mx:N*mx)];    % State x1 from solution
x2 = [x0(2);z(2:mx:N*mx)];    % State x2 from solution
x3 = [x0(3);z(3:mx:N*mx)];    % State x3 from solution
x4 = [x0(4);z(4:mx:N*mx)];    % State x4 from solution
x5 = [x0(4);z(5:mx:N*mx)];    % State x5 from solution
x6 = [x0(4);z(6:mx:N*mx)];    % State x6 from solution

Antall = 5/delta_t;
Nuller = zeros(Antall,1);
Enere  = ones(Antall,1);

u1   = [Nuller; u1; Nuller];
u2   = [Nuller; u2; Nuller];
x1  = [pi*Enere; x1; Nuller];
x2  = [Nuller; x2; Nuller];
x3  = [Nuller; x3; Nuller];
x4  = [Nuller; x4; Nuller];
x5  = [Nuller; x5; Nuller];
x6  = [Nuller; x6; Nuller];
u =  [u1 u2];
%save trajektor1ny
%%
 K = 0;
% figure
t = 0:delta_t:delta_t*(length(u1)-1);      % real time


figure(2)
subplot(511)
stairs(t,u1),grid
ylabel('u1')
subplot(512)
plot(t,x1,'m',t,x1,'mo'),grid
ylabel('lambda')
subplot(513)
plot(t,x2,'m',t,x2','mo'),grid
ylabel('r')
subplot(514)
plot(t,x3,'m',t,x3,'mo'),grid
ylabel('p')
subplot(515)
plot(t,x4,'m',t,x4','mo'),grid
xlabel('tid (s)'),ylabel('pdot')

figure(3)
subplot(311)
stairs(t,u2),grid
ylabel('u2')
subplot(312)
plot(t,x5,'m',t,x5,'mo'),grid
ylabel('e')
subplot(313)
plot(t,x6,'m',t,x6','mo'),grid
ylabel('e_dot')

