# -*- coding: utf-8 -*-
import numpy as np

def add_matmul_bias(w, x, b):
    tmp = np.sum(w*x) + b
    if tmp <= 0:
        return 0
    else:
        return 1

w = np.array([0.5, 0.5])
def AND(x1, x2):
    global w
    x = np.array([x1, x2])
    b = -0.7
    return add_matmul_bias(w, x, b)

def OR(x1, x2):
    global w
    x = np.array([x1, x2])
    b = -0.3
    return add_matmul_bias(w, x, b)

neg_w = np.array([-0.5, -0.5])
def NAND(x1, x2):
    global neg_w
    x = np.array([x1, x2])
    b = 0.7
    return add_matmul_bias(neg_w, x, b)
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
