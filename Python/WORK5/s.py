# Ron Ben David
import numpy as np
import pandas as pd
from matplotlib import pyplot as plt


def ReadData(name_file, tup):
    read_file = pd.read_excel(name_file, usecols=tup)
    read_file = read_file.reindex(columns=tup)
    read_file = read_file.to_numpy()
    return read_file


def PearsonCorrelation(X, Y):
    x_av = np.average(X)
    y_av = np.average(Y)
    R = np.sum((X-x_av)*(Y-y_av))/np.sqrt(np.sum((X-x_av)**2)*np.sum((Y-y_av)**2))
    return R


def PlotMyData(data, array_1, array_2):
    for i in range(len(array_1)):
        numbers_columns = array_1[i]
        first_num = int(numbers_columns[0])
        second_num = int(numbers_columns[1])
        name_columns = array_2[i]
        first_name = name_columns[0]
        second_name = name_columns[1]
        plt.subplot(len(array_1), 1, i+1)
        plt.title("{}: R={: .5f}".format(array_2[i], PearsonCorrelation(data[:, first_num], data[:, second_num])))
        plt.plot(data[:, first_num])
        plt.plot(data[:, second_num])
        plt.legend([first_name, second_name], loc='upper right')
    plt.show()
    pass