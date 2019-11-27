# -*- coding: utf-8 -*-

import tensorflow as tf
import os

os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'
sess = tf.InteractiveSession()

raw_data = [1., 2., 8., -1., 0., 5.5, 6.]
spike = tf.Variable(False)
spike.initializer.run()

for i in range(1, len(raw_data)):
    if raw_data[i] - raw_data[i-1] > 5:
        updater = tf.assign(spike, True)
        print(updater.eval())
    else:
        updater = tf.assign(spike, False)
        print(updater.eval())
sess.close()
