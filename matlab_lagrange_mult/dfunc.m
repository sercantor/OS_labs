% function dLambda = dfunc(X)
function dLambda = dfunc(X)
%
% We compute the partial derivate of the given function
% according to the formula 
%

% initialize the partial derivative vector so it has the same shape
% as the input X
dLambda = zeros(size(X));

% calculating using Finite difference method
h = 1e-5;
  for i=1:prod(size(X))
      dX=zeros(size(X));
      dX(i) = h;
      dLambda(i) = (func(X+dX)-func(X-dX))/(2*h);
  endfor

endfunction
