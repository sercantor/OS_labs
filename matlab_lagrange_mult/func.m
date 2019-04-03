% function gamma = func(X)

function gamma = func(X)
%
% We assing the functions accoring to the formula of lagrange multipliers
% 

x = X(1);
y = X(2);
lambda = X(3);
gamma = (x.*y.^2) + lambda.*(x.^2 + y.^2 - 16);
endfunction