# -*- coding: utf-8 -*-
import tensorflow as tf
import numpy as np

np.random.seed(1234)

x_data = np.random.randn(5, 10)
w_data = np.random.randn(10, 1)

print("\nx_data:", x_data)
print("\nw_data:", w_data)

x = tf.placeholder(dtype=tf.float32, shape=(5, 10))
w = tf.placeholder(dtype=tf.float32, shape=(10, 1))
b = tf.fill((5, 1), -1.)

xw = tf.matmul(x, w)
xwb = xw + b
y = tf.reduce_max(xwb)
with tf.Session() as sess:
    print("\nb:", sess.run(b))
    print("\nxw:", sess.run(xw, feed_dict={x:x_data, w:w_data}))
    print("\nxwb:", sess.run(xwb, feed_dict={x:x_data, w:w_data}))
    print("\ny:", sess.run(y, feed_dict={x:x_data, w:w_data}))
