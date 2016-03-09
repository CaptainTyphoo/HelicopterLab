%% Optimal control of Pitch/Travel with Feedback(LQ)

problem2;

LQR.Q = diag([1, 0, 1, 0]);
LQR.R = 1;

K = dlqr(A1, B1, LQR.Q, LQR.R);

