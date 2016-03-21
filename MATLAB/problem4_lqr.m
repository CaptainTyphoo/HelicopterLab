%% Optimal control of Pitch/Travel with Feedback(LQ)

problem4;

%%

LQR.Q = diag([1, 0, 1, 0, 1, 0]);
LQR.R = diag([10 10]);

K = dlqr(A1, B1, LQR.Q, LQR.R);

