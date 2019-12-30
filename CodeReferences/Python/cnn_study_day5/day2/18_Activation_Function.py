import numpy as np

#계단 함수

def step_function(x):
    if x > 0:
        return 1
    else:
        return 0

def step_function2(x):
    y = x > 0
    return y.astype(np.int)

x = np.array([-1.0, 1.0, 2.0])
print(x)
y = x > 0
print(y)
y = y.astype(np.int)
print(y)

print(step_function2(x))

import matplotlib.pyplot as plt

x = np.arange(-5.0, 5.0, 0.1)
y = step_function2(x)
plt.plot(x, y)
plt.ylim(-0.1, 1.1)
plt.show()

#sigmoid 함수
print('\n\n======sigmoid function=======')
def sigmoid(x):
    return 1/(1 + np.exp(-x))

x = np.array([-1.0, 1.0, 2.0])
print(sigmoid(x))

x = np.arange(-5.0, 5.0, 0.1)
y = sigmoid(x)
plt.plot(x, y)
plt.ylim(-0.1, 1.1)
plt.show()

# ReLU 함수

def relu(x):
    return np.maximum(0, x)



