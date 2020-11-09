import math
import numpy
import matplotlib.pyplot as plt

x_file = open('cmake-build-debug/x.txt', 'r')
Y_file = open('cmake-build-debug/Y.txt', 'r')
x = []
Y = []
while 1:
    float_num_str = x_file.readline()
    if len(float_num_str) != 0:
        x.append(float(float_num_str))
    else:
        break

while 1:
    float_num_str = Y_file.readline()
    if len(float_num_str) != 0:
        Y.append(float(float_num_str))
    else:
        break

Y_file.close()
x_file.close()

plt.plot(x, Y)
plt.grid()
plt.show()
