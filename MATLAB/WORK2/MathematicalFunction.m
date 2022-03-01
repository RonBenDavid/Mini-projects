function [cellarray] = MathematicalFunction()
%Ron ben david
t=linspace(0,125,2000);
x=(cos(sqrt(32)*t)+3).*(sin(t));
xaxis='x - axis';
yaxis='y - axis';
zaxis='z - axis';
y=sin(sqrt(32)*t);
z=(cos(sqrt(32)*t)+3).*(cos(t));
cellarray={x,xaxis,y,yaxis,z,zaxis};
end

