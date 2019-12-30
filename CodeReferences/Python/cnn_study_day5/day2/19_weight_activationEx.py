import numpy as np
# weight들을 어떻게 초기화하는 것이 좋은지를 보여주는 예제
# weight들의 값에 따라 activation function(sigmoid)를 통과한 값들이 가운데에 있을수록 학습이 잘 됨
# tensorflow를 사용하지 않고 행렬 곱셈만을 사용해 계산

def sigmoid(x):
    return 1 / (1 + np.exp(-x))

input_data = np.random.randn(1000,100)
node_num = 100
hidden_layer_size = 5
activations = {}

x = input_data
for i in range(5):
    if i != 0:
        x = activations[i-1]
    #데이터가 몰려있어서 학습에 좋지 않음.
    # w = np.random.randn(node_num, node_num) * 1
    #적당히 0.01을 곱한 값-> 랜덤한 값들의 표준오차가 0.01이라는 의미 -> 데이터가 가운데로 조금씩 몰림
    # w = np.random.randn(node_num, node_num) * 0.01
    #xavier 방법 -> 완전히 이쁘게 가운데로 모임
    w = np.random.randn(node_num, node_num) * np.sqrt(1.0/node_num)
    a = np.dot(x, w)
    z = sigmoid(a)
    activations[i] = z

import matplotlib.pyplot as plt
for i, a in activations.items():
    plt.subplot(1, len(activations), i+1)
    plt.title(str(i+1)+'-layer')
    if i != 0:
        plt.yticks([],[])
    plt.hist(a.flatten(), bins=30, range=(0,1))
plt.show()