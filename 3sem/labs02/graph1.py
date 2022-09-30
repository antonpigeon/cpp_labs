import matplotlib.pyplot as plt
import numpy as np

x = np.arange(1, 2001)
with open("data.txt", 'r') as fin:
    y = [float(line) for line in fin.readlines()]
plt.scatter(x, y, s=1)
plt.show()
