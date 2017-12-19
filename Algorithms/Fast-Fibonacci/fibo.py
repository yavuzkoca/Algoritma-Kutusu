# Fonksiyonlar
import numpy as np
import math
from matplotlib import pyplot as plt

liste = [-1] * 501


def fibo_fast(x):
    if x == 0:
        return 1
    if x == 1:
        return 1
    if liste[x] != -1:
        return liste[x]
    else:
        a = fibo_fast(x - 2) + fibo_fast(x - 1)
        liste[x] = a
    return a


test = fibo_fast(500)

degrees = np.arange(0, 360, 360 / 501)

liste[0] = 1
liste[1] = 1


#liste = [math.log(elm) for elm in liste]
liste = [math.log(elm) for elm in liste]

xs = [np.cos(alpha) * liste[index] for index, alpha in enumerate(degrees)]
ys = [np.sin(alpha)
      * liste[index] for index, alpha in enumerate(degrees)]


plt.plot(xs, ys)  # , 'ro', MarkerSize=2)
plt.show()

