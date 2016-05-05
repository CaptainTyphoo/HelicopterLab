% Optimal control of Pitch/Travel and Elevation 
% with Feedback(LQ)

problem4;

%%

LQR.Q = diag([5, 1, 1, 1, 1, 1]);
LQR.R = diag([1 1]);

K = dlqr(A1, B1, LQR.Q, LQR.R);

