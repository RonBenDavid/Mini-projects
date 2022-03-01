# Ron Ben David
import numpy as np
import pandas as pd
from matplotlib import pyplot as plt
import numbers

def PlusMat(ms,half_width=1):
    if (not isinstance(ms,numbers.Number)) or (not isinstance(half_width,numbers.Number)):
        return None
    if ms!=int(ms):
        return None
    else:
        ms=int(ms) #if input is float number

    if half_width!=int(half_width):
        return None
    else:
        half_width=int(half_width) #if input is float number

    if ms%2!=0:
        ms=ms+1
    my_Matrix = np.ones((ms, ms), dtype = int)
    if ms<=2*half_width:
        return my_Matrix
    half_Row=int(ms/2)
    my_Matrix[half_Row-half_width:half_Row+half_width,:]=0
    my_Matrix[:,half_Row-half_width:half_Row+half_width] = 0
    return my_Matrix


def ReadMyData(file_data):
    read_file = pd.read_excel(file_data)
    read_file = read_file.to_numpy()
    read_file[:, 0:1] = 1000 * read_file[:, 0:1, ]
    read_file[:, 2:3] = 1000 * read_file[:, 2:3]
    return read_file

def SignalGenerator(matrix_data,row,freq,time):
    print(matrix_data)
    dt=1/freq
    t=np.arange(time[0],time[1],dt)
    freq_1=matrix_data[row, 0:1]
    amplitude_1=matrix_data[row, 1:2]
    freq_2=matrix_data[row, 2:3]
    amplitude_2=matrix_data[row, 3:4]
    sin_signal = amplitude_2*np.sin(t*freq_2*2*np.pi)
    cos_signal = amplitude_1*np.cos(t*freq_1*2*np.pi)
    signal=sin_signal+cos_signal
    plt.figure()
    plt.plot(t, cos_signal,'--y')
    plt.plot(t,sin_signal,'--r')
    plt.plot(t, signal,'b',linewidth=2)
    plt.legend(['cos:f1={};A1={}'.format(float(freq_1),float(amplitude_1)),'sin:f2={};A2={}'.format(float(freq_2),float(amplitude_2)),'signal'], loc=2)
    plt.legend
    plt.hlines(0,time[0],time[1],colors='k')
    plt.show()