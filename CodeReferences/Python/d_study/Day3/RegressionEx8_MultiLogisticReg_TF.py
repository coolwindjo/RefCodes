# -*- coding: utf-8 -*-
import tensorflow as tf
import numpy as np
import os

os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'

data = [[2, 3, 0], [4, 3, 0], [6, 4, 0], [8, 6, 1], [10, 7, 1], [12, 8, 1], [14, 9, 1]]
x_data = np.array([xxy[:-1] for xxy in data])
y_data = np.array([xxy[-1] for xxy in data]).reshape(7, 1)

X = tf.placeholder(dtype=tf.float64, shape=[None, 2], name='X')
Y = tf.placeholder(dtype=tf.float64, shape=[None, 1], name='Y')

# Weight, bias initialization
tf.set_random_seed(777)
weight = tf.Variable(tf.random_uniform([2, 1], seed=0, dtype=tf.float64), name='Weight')
bias = tf.Variable(tf.random_uniform([1], seed=0, dtype=tf.float64), name='Bias')
init = tf.global_variables_initializer()

with tf.name_scope('SigmoidHypothesis'):
    #hypothesis = 1/(1 + np.e**(weight * x_data + bias))
    hypothesis = tf.sigmoid(tf.add(tf.matmul(X, weight), bias))

with tf.name_scope('Loss'):
#    loss = -tf.reduce_mean(np.array(y_data) * tf.log(hypothesis)
#                           + (1-np.array(y_data)) * tf.log(1-hypothesis))
    loss = -tf.reduce_mean(Y * tf.log(hypothesis)
                           + (1 - Y) * tf.log(1-hypothesis))

learn_rate = 0.1
with tf.name_scope('GradientDescentOptimizer'):
    optimizer = tf.train.GradientDescentOptimizer(learning_rate=learn_rate)
    train = optimizer.minimize(loss)
    #gradient = tf.reduce_mean(((weight*x - y) * x), name='Gradient')
    #descent = weight - learn_rate * gradient
    #gradient_descent = weight.assign(descent, name='GradientDescent')

with tf.Session() as sess:
    tf.summary.FileWriter('./graph_logs', sess.graph)
    sess.run(init)
    # Train weights with X, Y
    for step in range(3001):
        [_loss, _weight, _bias, _] = sess.run([loss, weight, bias, train], feed_dict={X:x_data, Y:y_data})
        if step % 300 == 0:
            print("Epoch:{} Cost={:.04f} Weight1={:.4f} Weight2={:.4f} Bias={:.4f}"\
                  .format(step, _loss, _weight[0, 0], _weight[1, 0], _bias[0]))

    # Now classfy a test set
    new_x = np.array([7, 6]).reshape(1, 2)
    new_y = sess.run(hypothesis, feed_dict={X:new_x})
    print("Study time:{} Private tutor:{}".format(new_x[:,0], new_x[:,1]))
    print("Pass probabiliy:{:6.2f}".format(new_y[0,0]*100))