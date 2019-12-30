import tensorflow as tf
import matplotlib.pyplot as plt
tf.set_random_seed(777)

# 02 파일에서 했던 일을 tensorflow가 자체적으로 가지고 있는 train class를 통해 해결
# 매우 간단하게 코드 작성이 가능하다.
# train클래스가 variable에 해당하는 것들을 자동으로 학습시킨다.
# 나중에 graident descent가 어떻게 작동하는지 수동으로 확실하게 배울 것

x_data = [1,2,3]
y_data = [1,2,3]

w = tf.Variable(tf.random_normal([1]), name='weight')

x = tf.placeholder(dtype=tf.float32)
y = tf.placeholder(dtype=tf.float32)
hypothesis = x * w
cost = tf.reduce_mean(tf.square(hypothesis-y))

learning_rate = 0.1
'''
gradient = tf.reduce_mean((w * x - y) * x)
descent = w - learning_rate * gradient
update = w.assign(descent)
'''
## w가 여러개라 하더라도 적용 가능한 tensorflow 내장기능
update = tf.train.GradientDescentOptimizer(learning_rate=learning_rate).minimize(cost)

sess = tf.Session()
sess.run(tf.global_variables_initializer())

for step in range(27):
    _cost, _w, _ = sess.run([cost, w, update], feed_dict={x: x_data, y: y_data})
    print('step:{}, cost:{}, w:{}'.format(step, _cost, _w))