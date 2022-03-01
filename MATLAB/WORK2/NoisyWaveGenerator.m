function [struct] = NoisyWaveGenerator(startTime,endTime,fs,A,f)
%Ron ben david
dt=1/fs;
t=startTime:dt:endTime;
wave=A.*sin(2*pi*f*t)./(2*pi*f*t);
random = normrnd(startTime,endTime,size(t));

struct.xName='time [sec]';
struct.x=t;
struct.yName='Amplitude [V]';
struct.y=wave+random;

end

