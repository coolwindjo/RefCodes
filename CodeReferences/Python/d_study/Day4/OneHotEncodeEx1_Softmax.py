# -*- coding: utf-8 -*-
import numpy as np

a = np.array([0.3, 2.9, 4.0])
exp_a = np.exp(a)
print("exp_a:", exp_a)

sum_exp = np.sum(exp_a)
print("sum_exp:", sum_exp)

y = exp_a / sum_exp
print("softmax1(a):", y)

p=print
p("# ----------------------------------------------------")

def softmax(a):
    c = np.max(a)
    exp_a = np.exp(a - c)
    sum_exp_a = np.sum(exp_a)
    y = exp_a / sum_exp_a
    return y

y = softmax(a)
print("softmax2(a):", y)