# -*- coding: utf-8 -*-
import tensorflow as tf
import matplotlib.pyplot as plt

x = [1, 2, 3]
y = [1, 2, 3]

slope = tf.placeholder(dtype=tf.float32, name='Slope')

hypothesis = slope * x
cost = tf.reduce_mean(tf.square(y - hypothesis), name='Mean_square')

slope_history = []
cost_history = []
with tf.Session() as sess:
    for i in range(-30, 50):
        curr_slope = i * 0.1
        curr_cost = sess.run(cost, feed_dict={slope:curr_slope})
        slope_history.append(curr_slope)
        cost_history.append(curr_cost)

plt.plot(slope_history, cost_history)
plt.show()