# -*- coding: utf-8 -*-
import numpy as np

x = [2, 4, 6, 8]
y = [81, 93, 91, 97]

mx = np.mean(x)
my = np.mean(y)
print("mean x =", mx)
print("mean y =", my)

denom = sum([(x_i-mx)**2 for x_i in x])

def top(x, mx, y, my):
    return sum([((x_i - mx) * (y_i - my)) for (x_i, y_i) in zip(x, y)])

numer = top(x, mx, y, my)
print("numerator =", numer)
print("denominator =", denom)

a = numer / denom
b = my - (a * mx)
print("slope =", a)
print("offset =", b)