# -*- coding: utf-8 -*-

import tensorflow as tf

input_data = [1, 2, 3, 4, 5]
x = tf.placeholder(dtype=tf.float32)
W = tf.Variable([2], dtype=tf.float32)
y = W*x

sess = tf.Session()
init = tf.global_variables_initializer()
print("\ninit:\n", sess.run(init))
print("\ny:\n", sess.run(y, feed_dict={x:input_data}))
