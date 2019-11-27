# -*- coding: utf-8 -*-
import tensorflow as tf
import numpy as np

data = [[2, 0], [4, 0], [6, 0], [8, 1], [10, 1], [12, 1], [14, 1]]
x_data = [xy[0] for xy in data]
y_data = [xy[1] for xy in data]

#X = tf.placeholder(dtype=tf.float32, shape=[None, 3], name='X')
#Y = tf.placeholder(dtype=tf.float32, shape=[None, 1], name='Y')

tf.set_random_seed(777)
weight = tf.Variable(tf.random_normal([1], seed=0, dtype=tf.float64), name='Weight')
bias = tf.Variable(tf.random_normal([1], seed=0, dtype=tf.float64), name='Bias')
init = tf.global_variables_initializer()

#hypothesis = slope * x
#y = slope * x_data + offset
with tf.name_scope('Hypothesis'):
    hypothesis = 1/(1 + np.e**(weight * x_data + bias))
#cost = tf.reduce_mean(tf.square(y - slope * x), name='Mean_square')
with tf.name_scope('Loss'):
    loss = -tf.reduce_mean(np.array(y_data) * tf.log(hypothesis)
                           + (1-np.array(y_data)) * tf.log(1-hypothesis))

learn_rate = 0.5
optimizer = tf.train.GradientDescentOptimizer(learning_rate=learn_rate, name='GradientDescentOptimizer')
train = optimizer.minimize(loss)
#gradient = tf.reduce_mean(((weight*x - y) * x), name='Gradient')
#descent = weight - learn_rate * gradient
#gradient_descent = weight.assign(descent, name='GradientDescent')

with tf.Session() as sess:
    tf.summary.FileWriter('./graph_logs', sess.graph)
    sess.run(init)
    for step in range(60001):
        [_loss, _weight, _bias, _] = sess.run([loss, weight, bias, train])
        if step % 6000 == 0:
            print("Epoch:{} Cost={:.04f} Weight={:.4f} Bias={:.4f}"\
                  .format(step, _loss, _weight[0], _bias[0]))

