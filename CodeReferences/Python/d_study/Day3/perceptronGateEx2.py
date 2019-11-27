# -*- coding: utf-8 -*-
import numpy as np

def add_matmul_bias(w, x, b):
    tmp = np.sum(w*x) + b
    if tmp <= 0:
        return 0
    else:
        return 1

#NAND
#neg_w = np.array([-0.5, -0.5])
#b = 0.7
w11 = np.array([-2, -2])
b1 = 3

#OR
#w = np.array([0.5, 0.5])
#b = -0.3
w12 = np.array([2, 2])
b2 = -1

#AND
#w = np.array([0.5, 0.5])
#b = -0.7
w2 = np.array([1, 1])
b3 = -1

def MLP(x, w, b):
    return add_matmul_bias(w, x, b)

def AND(x1, x2):
    global w2, b3
    x = np.array([x1, x2])
    return MLP(x, w2, b3)

def OR(x1, x2):
    global w12, b2
    x = np.array([x1, x2])
    return MLP(x, w12, b2)

def NAND(x1, x2):
    global w11, b1
    x = np.array([x1, x2])
    return MLP(x, w11, b1)
    #return 1-AND(x1, x2)
    
def XOR(x1, x2):
    s1 = NAND(x1, x2)
    s2 = OR(x1, x2)
    return AND(s1, s2)


print("\nAND logic")
for xs in [(0, 0), (1, 0), (0, 1), (1, 1)]:
    y = AND(xs[0], xs[1])
    print(str(xs) + " -> " + str(y))

print("\nOR logic")
for xs in [(0, 0), (1, 0), (0, 1), (1, 1)]:
    y = OR(xs[0], xs[1])
    print(str(xs) + " -> " + str(y))

print("\nNAND logic")
for xs in [(0, 0), (1, 0), (0, 1), (1, 1)]:
    y = NAND(xs[0], xs[1])
    print(str(xs) + " -> " + str(y))

print("\nXOR logic")
for xs in [(0, 0), (1, 0), (0, 1), (1, 1)]:
    y = XOR(xs[0], xs[1])
    print(str(xs) + " -> " + str(y))
