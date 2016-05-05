%% Optimal control of Pitch/Travel with Feedback(LQ)
problem2;

% [lambda r p p_dot]
LQR.Q = diag([1, 0, 10, 0]);
LQR.R = 0.5;

K = dlqr(A1, B1, LQR.Q, LQR.R);

