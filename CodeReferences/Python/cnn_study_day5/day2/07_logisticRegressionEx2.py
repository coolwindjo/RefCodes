import tensorflow as tf
import numpy as np
tf.set_random_seed(777)

#x변수가 두개인 경우 logstic regression으로 계산하는 방법
x_data = [[1,2],[2,3],[3,1],[4,3],[5,3],[6,2]]
y_data = [0,0,0,1,1,1]
x1_data = [x[0] for x in x_data]
x2_data = [x[1] for x in x_data]

# y = w1x1 + w2x2 + b

w1 = tf.Variable(tf.random_normal([1], dtype=tf.float64, seed=0))
w2 = tf.Variable(tf.random_normal([1], dtype=tf.float64, seed=0))
b = tf.Variable(tf.random_normal([1], dtype=tf.float64, seed=0))

hypothesis = 1 / (1 + np.e**(w1*x1_data + w2*x2_data + b)) #sigmoid 함수-> 변수는 vector
cost_vector = -(np.array(y_data) * tf.log(hypothesis) + (1-np.array(y_data)) * tf.log(1-hypothesis))
cost = tf.reduce_mean(cost_vector)

learning_rate = 0.01
train = tf.train.GradientDescentOptimizer(learning_rate).minimize(cost)

with tf.Session() as sess:
    sess.run(tf.global_variables_initializer())
    for step in range(600001):
        _cost, _w1, _w2, _b, _ = sess.run([cost, w1, w2, b, train])
        if step % 6000 == 0:
            print('step:{} cost:{} w1:{} w2:{} b:{}'.format(step, _cost, _w1, _w2, _b))
