function []= PlotFun(first,theend,numelement)
%UNTITLED10 Summary of this function goes here
%   Detailed explanation goes here
timevector=linspace(first,theend,numelement);
R=10000;
C=0.1*(10^(-6));
for t=numelement
y1=1:1000;
y2=1:1000;
y1(t)=(1/R*C)*(exp(-2*t));
y2(t)=(0.2)*(tan(t)^(-1))/(pi);
end
plot(timevector,y1,'g',timevector,y2,'r');
title('func');
legend('(1/R*C)*(exp(-2*t))','(0.2)*(tan(t)^(-1))/(pi)');
end

