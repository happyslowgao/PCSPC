function [f_result] = f(x,y)
%UNTITLED2 此处显示有关此函数的摘要
%   此处显示详细说明
% f_result=0.9735*sign(x)*sign(y)*min(abs(x),abs(y));
f_result=0.9375*sign(x)*sign(y)*min(abs(x),abs(y));
end

