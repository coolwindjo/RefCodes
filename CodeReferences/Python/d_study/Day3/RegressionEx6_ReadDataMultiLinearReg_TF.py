# -*- coding: utf-8 -*-
import tensorflow as tf
import numpy as np

xy = np.loadtxt('data-01-test-score.csv', delimiter=',', dtype=np.float32)

x_data = xy[:, 0:-1]
y_data = xy[:, [-1]]

X = tf.placeholder(dtype=tf.float32, shape=[None, 3], name='X')
Y = tf.placeholder(dtype=tf.float32, shape=[None, 1], name='Y')

tf.set_random_seed(777)
weight = tf.Variable(tf.random_normal([3, 1], seed=0, dtype=tf.float32), name='Weight')
bias = tf.Variable(tf.random_normal([1], seed=0, dtype=tf.float32), name='Bias')
init = tf.global_variables_initializer()

#hypothesis = slope * x
#y = slope * x_data + offset
with tf.name_scope('Hypothesis'):
    hypotheis = tf.add(tf.matmul(X, weight), bias)
#cost = tf.reduce_mean(tf.square(y - slope * x), name='Mean_square')
with tf.name_scope('Cost'):
    cost = tf.reduce_mean(tf.square(hypotheis - Y))

learn_rate = 1e-5
optimizer = tf.train.GradientDescentOptimizer(learning_rate=learn_rate, name='GradientDescentOptimizer')
train = optimizer.minimize(cost)
#gradient = tf.reduce_mean(((weight*x - y) * x), name='Gradient')
#descent = weight - learn_rate * gradient
#gradient_descent = weight.assign(descent, name='GradientDescent')

with tf.Session() as sess:
    tf.summary.FileWriter('./graph_logs', sess.graph)
    sess.run(init)
    for step in range(2001):
        [_cost, _hypothesis, _] = sess.run([cost, hypotheis, train], feed_dict={X:x_data, Y:y_data})
        if step % 10 == 0:
            print("Epoch:{} Cost={:.04f} PredictedValue={:.4f}".format(step, _cost, _hypothesis[0][0]))

    print("Your score will be {}".format(sess.run(hypotheis, feed_dict={X:[[100, 70, 101]]})))
    print("Others' scores will be {}".format(sess.run(hypotheis, feed_dict={X:[[60, 70, 110], [90, 100, 80]]})))

