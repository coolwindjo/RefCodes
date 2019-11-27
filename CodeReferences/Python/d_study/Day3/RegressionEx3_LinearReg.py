# -*- coding: utf-8 -*-
import tensorflow as tf

x_data = [1, 2, 3]
y_data = [1, 2, 3]

tf.set_random_seed(777)
slope = tf.Variable(tf.random_normal([1]), dtype=tf.float32, name='Weight')
init = tf.global_variables_initializer()

x = tf.placeholder(dtype=tf.float32)
y = tf.placeholder(dtype=tf.float32)

hypothesis = slope * x
cost = tf.reduce_mean(tf.square(y - hypothesis), name='Mean_square')

learn_rate = 0.1
grad = tf.reduce_mean(((slope*x - y) * x), name='Gradient')
descent = slope - learn_rate * grad
update = slope.assign(descent, name='Update')

with tf.Session() as sess:
    sess.run(init)
    for step in range(21):
        sess.run(update, feed_dict={x:x_data, y:y_data})
        print("step: ", step, sess.run(cost, feed_dict={x:x_data, y:y_data}), sess.run(slope))
