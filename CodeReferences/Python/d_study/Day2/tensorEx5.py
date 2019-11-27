# -*- coding: utf-8 -*-
import numpy as np
import tensorflow as tf

input_data = [1, 2, 3, 4, 5]
x = tf.placeholder(dtype=tf.float32)
y = x * 2

sess = tf.Session()
print("\ny:", sess.run(y, feed_dict={x:input_data}))

p=print
p("# ----------------------------------------")

a = tf.placeholder(dtype=tf.int32, shape=[2, 2], name='p_input')
b = tf.reduce_prod(a, name='prod_b')
c = tf.reduce_sum(a, name='sum_c')
d = tf.add(b, c, name='add_d')

input_dict = {a: np.array([[5, 3],
                           [4, 7]], 
                           dtype=np.int32)}
print("\n[b, c, d]:", sess.run([b, c, d], feed_dict=input_dict))

tf.summary.FileWriter('./graph_logs',sess.graph)
sess.close()