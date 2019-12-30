import tensorflow as tf
import matplotlib.pyplot as plt
tf.set_random_seed(777)

#01 파일에서 cost를 측정하였다.
# 이번에는 w를 학습하는 예제
# MSE로 cost를 계산하고 gradient descent 방법을 통해
# weight을 업데이트한다. 이 때, learning rate가 사용된다.

x_data = [1,2,3]
y_data = [1,2,3]

w = tf.Variable(tf.random_normal([1]), name='weight')

x = tf.placeholder(dtype=tf.float32)
y = tf.placeholder(dtype=tf.float32)
hypothesis = x * w
cost = tf.reduce_mean(tf.square(hypothesis-y))

learning_rate = 0.1
gradient = tf.reduce_mean((w * x - y) * x)
descent = w - learning_rate * gradient
update = w.assign(descent)

sess = tf.Session()
sess.run(tf.global_variables_initializer())

for step in range(27):
    _cost, _w, _ = sess.run([cost, w, update], feed_dict={x: x_data, y: y_data})
    print('step:{}, cost:{}, w:{}'.format(step, _cost, _w))