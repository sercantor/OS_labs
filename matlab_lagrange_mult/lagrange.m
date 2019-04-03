%Euler's Method
clc; close all; clear
syms x;
f(x) = x.^3 + 2*x;
x0 = 1;
maxiter = 50;
tolx = 1e-4

x=x0
xold = x0;
for i = 1:maxiter
  x1 = x0 - f(x0)/diff(f(x),x0);
  x0 = x1;
endfor
