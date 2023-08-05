import matplotlib.pyplot as plt
import matplotlib
import numpy as np

matplotlib.use('TkAgg')

x = np.arange(0, 2, 0.2)

plt.plot(x, x, 'bo')
plt.grid(True)

plt.show()