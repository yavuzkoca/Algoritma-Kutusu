import numpy as np
from matplotlib import pyplot as plt


def fourier(x, repeat):
    value = 0
    for i in range(repeat):
        value += np.sin((2 * i + 1) * x) / (2 * i + 1)
    return value

series = [fourier(val, 1000) * (5 / 8) +
          0.5 for val in np.arange(-20, 20, 0.1)]

axes = plt.gca()
axes.set_ylim([-2, 2])

plt.plot(np.arange(-20, 20, 0.1), series)

plt.show()
