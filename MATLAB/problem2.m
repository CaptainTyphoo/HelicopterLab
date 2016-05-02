% ****************************************************
% *                                                  *
% *       Optimization and Control                   *
% *                                                  *
% *       Helikopterlab                              *
% *                                                  *
% * problem2.m                                       *
% *                                                  *
% *                                                  *
% * Updated on 04/2009 by Agus Ismail Hasan          *
% *                                                  *
% ****************************************************

init01;
delta_t	  = 0.25;	                   % sampling time
sek_forst = 5;

% System model. x=[lambda r p p_dot]'

Ac = [0 1 0 0; 
      0 0 -K_2 0; 
      0 0 0 1; 
      0 0 -K_1*K_pp -K_1*K_pd];
Bc = [0; 0; 0; K_1*K_pp];

A1 = eye(4) + Ac*delta_t;
B1 = Bc*delta_t;

% Number of states and inputs

mx = size(A1,2);  % Number of states
mu = size(B1,2);  % Number of inputs

% Initial values

x1_0 = pi;                            % Lambda
x2_0 = 0;                             % r
x3_0 = 0;                             % p
x4_0 = 0;                             % p_dot
x0   = [x1_0 x2_0 x3_0 x4_0]';        % Initial values
xf   = [0 0 0 0]';

% Time horizon and initialization

N  = 100;                   % Time horizon for states
M  = N;                     % Time horizon for inputs
z  = zeros(N*mx+M*mu,1);% Initialize z for the whole horizon
z0 = z;               % Initial value for optimization

% Bounds

ul 	    = -30*pi/180;   % Lower bound on control -- u1
uu 	    = 30*pi/180;    % Upper bound on control -- u1

xl      = -Inf*ones(mx,1); % Lower bound on states
xu      = Inf*ones(mx,1);  % Upper bound on states
xl(3)   = ul;              % Lower bound on state x3
xu(3)   = uu;              % Upper bound on state x3

% Generate constraints on measurements and inputs

vlb      = [kron(ones(N,1),xl);kron(ones(N*mu,1),ul)];
vub      = [kron(ones(N,1),xu);kron(ones(N*mu,1),uu)];
vlb(N*mx+M*mu)  = 0; 
vub(N*mx+M*mu)  = 0; 

% Generate the matrix Q and the vector c 

Q1 = zeros(mx,mx);
Q1(1,1) = 1;                 % Weight on state x1
%Q1(2,2) = ;                 % Weight on state x2
Q1(3,3) = 0;                 % Weight on state x3
%Q1(4,4) = ;                 % Weight on state x4
P1 = 10;                     % Weight on input
Q = 2*genq2(Q1,P1,N,M,mu);   % Generate Q
c = zeros(N*mx+M*mu,1);      % Generate c

% Generate system matrixes for linear model
Aeq = gena2(A1,B1,N,mx,mu);
Aeq = [ Aeq; [zeros(mx,(N-1)*mx), eye(4), zeros(mx,N*mu)]];

beq = [A1*x0; zeros((N-1)*mx,1);xf];      % Generate b

% Solve Qp problem with linear model
tic
[z,lambda] = quadprog(Q,[],[],[],Aeq,beq,vlb,vub);
t1=toc;

% Calculate objective value

phi1 = 0.0;
PhiOut = zeros(N*mx+M*mu,1);
for i=1:N*mx+M*mu
  phi1=phi1+Q(i,i)*z(i)*z(i);
  PhiOut(i) = phi1;
end

% Extract control inputs and states

u  = [z(N*mx+1:N*mx+M*mu);z(N*mx+M*mu)];

x1 = [x0(1);z(1:mx:N*mx)];    % State x1 from solution
x2 = [x0(2);z(2:mx:N*mx)];    % State x2 from solution
x3 = [x0(3);z(3:mx:N*mx)];    % State x3 from solution
x4 = [x0(4);z(4:mx:N*mx)];    % State x4 from solution

Antall = 5/delta_t;
Nuller = zeros(Antall,1);
Enere  = ones(Antall,1);

u   = [Nuller; u; Nuller];
x1  = [pi*Enere; x1; Nuller];
x2  = [Nuller; x2; Nuller];
x3  = [Nuller; x3; Nuller];
x4  = [Nuller; x4; Nuller];

%save trajektor1ny

% figure
t = 0:delta_t:delta_t*(length(u)-1);    % real time

figure(2)
subplot(511)
stairs(t,u),grid
ylabel('u')
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
