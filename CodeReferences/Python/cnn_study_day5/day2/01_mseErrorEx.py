import tensorflow as tf
import matplotlib.pyplot as plt
tf.set_random_seed(777)

# 예측값 = 가중치 * 값
# y= w * x 와 같은 아주 간단한 예측을 할 때 cost의 변화량을 관찰하는 예제
# x와 y(입력값, 정답)이 같으므로 w는 1이다.
# 가중치 w는 1일 때 가장 최소값을 가진다.
# cost는 MSE(Mean Squared Error)를 사용

x = [1,2,3]
y = [1,2,3]

w = tf.placeholder(dtype=tf.float32)
hypothesis = x * w
cost_vector = tf.square(hypothesis - y)
cost = tf.reduce_mean(cost_vector)

sess = tf.Session()

w_history = []
cost_history = []

for i in range(-30, 50):
    curr_w = i * 0.1
    curr_cost = sess.run(cost, feed_dict={w: curr_w})
    w_history.append(curr_w)
    cost_history.append(curr_cost)

plt.plot(w_history, cost_history)
plt.show()