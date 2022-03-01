%% 1
clear, clc
MyNameAndAge()



%% 2
clear, clc
inputVector1 = [1, 2, 3, 4, 5, 8, 8, 8, 8];
myMatID1 = MyMatID(inputVector1);

inputVector2 = [1, 2, 3, 4, 5, 8, 8, 8];
myMatID2 = MyMatID(inputVector2);

inputVector3 = '123458888';
myMatID3 = MyMatID(inputVector3);

%% 3
clear, clc
myPhone = '0525123230';
[newMat, newRow] = MyRepmat(myPhone);

%% 4
clear, clc
PlotFun(0, 10, 10000)

%% 5
clear, clc
UserPlotFun()


