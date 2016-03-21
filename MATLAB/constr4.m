function [ c, ceq ] = constr4( x )
%UNTITLED4 Summary of this function goes here
%   Detailed explanation goes here
%global N mx;
    N = 40;
    mx = 6;
    alpha = 0.2;
    beta = 20;
    lambda_t=2*pi/3;
    
    lambda_k = x(1:6:N*mx);
    e_k = x(5:6:N*mx);
    
    c = alpha*exp(-beta*((lambda_k-lambda_t).^2))-e_k;
    ceq = [];
end

