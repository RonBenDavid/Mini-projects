# Ron Ben David
import numpy as np
import pandas as pd
from matplotlib import pyplot as plt


def myDictConst(myKey, myVal):
    myDec = {myKey[i]: myVal[i] for i in range(len(myKey))}
    return myDec


def countMyStrings(myStr):
    string_temp = myStr.lower()
    my_list = string_temp.split(' ')
    mykey = list(set(my_list))
    myDec = {mykey[i]: my_list.count(str(mykey[i])) for i in range(len(mykey))}
    return myDec


def myArange(temp, stop=None, step=1, dtypeUser=np.int32):
    myList = []
    if stop is None:
        stop = temp
        start = 0
    else:
        start = temp
    if (start > stop and step > 0) or (start < stop and step < 0):
        myndArray = np.array(myList)
        return myndArray
    myList = [start]
    for i in range(1, (int)(abs(round(0.1 + (stop - start) / step)))):
        myList.append(start + (i) * step)
    myndArray = np.array(myList, dtypeUser)
    return myndArray


def ModBooleanVector(inputVector, x):
    booleanVector = (inputVector % x) == 0
    return booleanVector


def Boolean2intList(booleanVector):
    intList = [int(booleanVector[i]) for i in range(len(booleanVector))]
    return intList


def ImportData(file_data):
    read_file = pd.read_excel(file_data)
    read_file = read_file.to_numpy()
    L = read_file[:, 0:1, ]
    L = L.astype(int)
    XY = read_file[:, 1:3]
    NewXY = read_file[:, 4:6]
    return L, XY, NewXY


def PlotMyData(L, XY, NewXY, type0='ok', type1='ob', type2='or', typeNew='.c'):
    c_0 = L == 0
    c_1 = L == 1
    c_2 = L == 2
    x = XY[:, :1]
    y = XY[:, 1:2]
    NewX = NewXY[:, :1]
    NewY = NewXY[:, 1:2]
    plt.figure()
    plt.plot(x[c_0], y[c_0], type0, x[c_1], y[c_1], type1, x[c_2], y[c_2], type2, NewX, NewY, typeNew)
    plt.show()
    pass
