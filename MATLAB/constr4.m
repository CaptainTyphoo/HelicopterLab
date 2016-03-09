function [ c, ceq ] = constr4( z )
%UNTITLED4 Summary of this function goes here
%   Detailed explanation goes here
global N
global mx
    alpha = 0.2;
    beta = 20;
    lambda_t=2^pi/3;
    
    lambda_k = z(1:6:N*mx);
    e_k = z(5:6:N*mx);
    
    c = alpha*exp(-beta*(lambda_k-lambda_t).^2)-e_k;
    ceq = 0;
end

