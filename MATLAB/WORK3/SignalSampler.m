function [timeVector,signal] = SignalSampler(signalsStruct,fs,startTime,endTime)
%Ron ben david
f=signalsStruct.f;
A=signalsStruct.A;
DC=signalsStruct.DC;
phase=signalsStruct.phase;
   if isnan(phase)
       phase=0;
   end
dt=1/fs;
timeVector=(startTime:dt:endTime)';
signal=(A*cos(pi*f*timeVector+phase)+DC);
end

