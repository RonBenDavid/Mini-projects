function [] = PlotSignal(signalsStruct,fs,startTime,endTime)
%Ron ben david
[timeVector, signal] = SignalSampler(signalsStruct, fs, startTime, endTime);
plot(signal);
xlim([0 fs]);
title([signalsStruct.A_header,':',num2str(signalsStruct.A),', ',signalsStruct.f_header,':',num2str(signalsStruct.f)]);
yl = yline(signalsStruct.DC,'--','Color','r');
y2 = yline(0,'LabelVerticalAlignment','bottom','LineWidth',2);
legend('signal',signalsStruct.DC_header)
end

