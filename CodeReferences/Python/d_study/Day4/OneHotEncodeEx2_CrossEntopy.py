# -*- coding: utf-8 -*-
import numpy as np

t = [0, 0, 1, 0, 0, 0, 0, 0, 0, 0]
y1 = [0.1, 0.05, 0.6, 0.0, 0.05, 0.1, 0.0, 0.1, 0.0, 0.0]
y2 = [0.1, 0.05, 0.1, 0.0, 0.05, 0.1, 0.0, 0.6, 0.0, 0.0]

# Loss functions
def mse(y, t):
    return 0.5 * np.sum((y - t)**2)

print("mse(y1):{}".format(mse(np.array(y1), np.array(t))))
print("mse(y2):{}".format(mse(np.array(y2), np.array(t))))

p=print
p("# ----------------------------------------------------")

def cross_entropy(y, t):
    delta = 1e-7
    return -np.sum(t * np.log(y + delta))

print("cross_entropy(y1):{}".format(cross_entropy(np.array(y1), np.array(t))))
print("cross_entropy(y2):{}".format(cross_entropy(np.array(y2), np.array(t))))
