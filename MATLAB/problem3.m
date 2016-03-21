%% Optimal control of Pitch/Travel with Feedback(LQ)

problem2;

LQR.Q = diag([10, 1, 5, 0]);
LQR.R = 0.5;

K = dlqr(A1, B1, LQR.Q, LQR.R);

