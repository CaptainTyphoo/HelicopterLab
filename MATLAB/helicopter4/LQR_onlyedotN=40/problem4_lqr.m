%% Optimal control of Pitch/Travel with Feedback(LQ)

problem4;

%% Feedbackloop

LQR.Q = diag([1, 1, 1, 1, 1, 1]);
LQR.R = diag([1 1]);

K = dlqr(A1, B1, LQR.Q, LQR.R);

