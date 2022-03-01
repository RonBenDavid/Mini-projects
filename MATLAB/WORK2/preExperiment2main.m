%% 1
clear; clc;

cellArray = MathematicalFunction();
disp('cellArray: ')
disp(cellArray)

%% 2

close all; clear; clc;

load('cellArray.mat');

figure('Name', '2D')
PlotCell(cellArray, '2D')

figure('Name', '3D')
PlotCell(cellArray, '3D')

figure('Name', 'all')
PlotCell(cellArray, 'all')

PlotCell(cellArray, 'abc')

%% 3
clear; clc;

Start = 0;

Stop = 2*pi;

samplingFrequency = 30;

Amplitude = 10;

WaveFrequency = 1/pi;

generatoredWave = NoisyWaveGenerator(Start, Stop,...
    samplingFrequency, Amplitude, WaveFrequency);

disp('generatoredWav =')

disp(generatoredWave)

%% 4
close all; clc; clear;

load('generatoredWave.mat');

StructPlot(generatoredWave, '');

%% 5

SaveDataStruct(generatoredWave, 'generatoredWave');

%% 6
clear; clc;

generatoredWave = LoadDataStruct('generatoredWaveSol.xlsx');

disp('generatoredWav =')

disp(generatoredWave)