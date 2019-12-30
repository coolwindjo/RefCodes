import numpy as np

# Cross entropy 에러가 왜 더 좋은지에 대한 설명
# MSE로는 cost의 합이 cross entropy로 계산한 cost의 합보다 적게 나옴
# y1은 정답이 60%로 적당히 맞는 분류기. 아직 많이 학습이 필요함
# y2는 정답을 완전히 잘못 찍은 분류기. 학습이 매우 많이 필요
# MSE는 y1 : 0.089, y2 : 0.51 정도의 cost가 보이며
# Cross entropy는 y1 : 0.5, y2 : 2.3 정도의 cost가 나타난다.
# 그럼 gradient descent 예제에 cross entropy를 사용하면 더 향상되나??

def mean_squared_error(y, t):
    return 0.5 * np.sum((y - t)**2)

def cross_entropy_error(y, t):
    #delta는 너무 작은 값이 로그에 들어가는 것을 방지하기 위함
    delta = 1e-7
    return -np.sum(t * np.log(y + delta))

t = [0,0,1,0,0,0,0,0,0,0]
y1 = [0.1, 0.05, 0.6, 0.0, 0.05, 0.0, 0.1, 0.0, 0.1, 0.0]
y2 = [0.1, 0.05, 0.1, 0.0, 0.05, 0.0, 0.6, 0.0, 0.1, 0.0]

mse1 = mean_squared_error(np.array(y1), np.array(t))
print('mse1:', mse1)
mse2 = mean_squared_error(np.array(y2), np.array(t))
print('mse2:', mse2)

cee1 = cross_entropy_error(np.array(y1), np.array(t))
print('cee1:', cee1)
cee2 = cross_entropy_error(np.array(y2), np.array(t))
print('cee2:', cee2)