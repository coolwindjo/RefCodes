import tensorflow as tf
import matplotlib.pyplot as plt
tf.set_random_seed(777)

#BIAS도 함께 계산해보는 방법

x_data = [2,4,6,8]
y_data = [81,93,91,97]


w = tf.Variable(tf.random_normal([1], 0, 10, dtype=tf.float64, seed=0), name='weight')
b = tf.Variable(tf.random_normal([1], 0, 100, dtype=tf.float64, seed=0), name='bias')

x = tf.placeholder(dtype=tf.float64)
y = tf.placeholder(dtype=tf.float64)
hypothesis = x * w + b
cost = tf.reduce_mean(tf.square(hypothesis-y))

learning_rate = 0.01
'''
gradient = tf.reduce_mean((w * x - y + b) * x)
descent = w - learning_rate * gradient
update = w.assign(descent)
'''
## w가 여러개라 하더라도 적용 가능한 tensorflow 내장기능
update = tf.train.GradientDescentOptimizer(learning_rate=learning_rate).minimize(cost)

sess = tf.Session()
sess.run(tf.global_variables_initializer())

for step in range(1000):
    _cost, _w, _b, _ = sess.run([cost, w, b, update], feed_dict={x: x_data, y: y_data})
    print('step:{}, cost:{}, w:{}, b:{}'.format(step, _cost, _w, _b))

