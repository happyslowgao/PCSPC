function [f_result] = f(x,y)
%UNTITLED2 �˴���ʾ�йش˺�����ժҪ
%   �˴���ʾ��ϸ˵��
% f_result=0.9735*sign(x)*sign(y)*min(abs(x),abs(y));
f_result=0.9375*sign(x)*sign(y)*min(abs(x),abs(y));
end

