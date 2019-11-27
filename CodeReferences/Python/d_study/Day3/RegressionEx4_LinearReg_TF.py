# -*- coding: utf-8 -*-
import tensorflow as tf

data = [[2, 81], [4, 93], [6, 91], [8, 97]]
x_data = [xy[0] for xy in data]
y_data = [xy[1] for xy in data]

tf.set_random_seed(777)
slope = tf.Variable(tf.random_uniform([1], 0, 10, seed=0, dtype=tf.float64), name='A')
offset = tf.Variable(tf.random_uniform([1], 0, 100, seed=0, dtype=tf.float64), name='B')

init = tf.global_variables_initializer()

y = slope * x_data + offset
rmse = tf.sqrt(tf.reduce_mean(tf.square(y - y_data)))

learn_rate = 0.1
grad_descent = tf.train.GradientDescentOptimizer(learn_rate).minimize(rmse)
#hypothesis = slope * x
#cost = tf.reduce_mean(tf.square(y - slope * x), name='Mean_square')
#grad = tf.reduce_mean(((slope*x - y) * x), name='Gradient')
#descent = slope - learn_rate * grad
#update = slope.assign(descent, name='Update')

with tf.Session() as sess:
    tf.summary.FileWriter('./graph_logs', sess.graph)
    sess.run(init)
    for step in range(2001):
        sess.run(grad_descent)
        if step % 100 == 0:
            print("Epoch:{} RMSE={:.04f} Slope:{:.4f} Offset:{:.4f}".format(step, sess.run(rmse), sess.run(slope)[0], sess.run(offset)[0]))
