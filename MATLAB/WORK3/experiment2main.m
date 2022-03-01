%% 1
clear
clc

fileName = 'datamine.xlsx';
sheet = 'wave signal';
[signalsStructArray] = Excel2Struct(fileName, sheet);

disp('signalsStructArray:')
disp(signalsStructArray)

disp('signalsStructArray(1):')
disp(signalsStructArray(1))

%% 2
clear
clc

startTime = 0;

endTime = 1;

fs = 128;

load('signalsStructArray.mat');
signalsStruct = signalsStructArray(4);

[timeVector, signal] = SignalSampler(signalsStruct, fs, startTime, endTime);


%% 3
clear
clc
close all

startTime = 1;
endTime = 2;
fs = 128;
load('signalsStructArray.mat');
signalsStruct = signalsStructArray(4);
PlotSignal(signalsStruct, fs, startTime, endTime)