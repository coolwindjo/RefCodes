# -*- coding: utf-8 -*-

import tensorflow as tf
import os

os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'
sess = tf.InteractiveSession()

#spikes = tf.Variable([False]*len(raw_data), name='spike')
s1 = tf.Variable([False]*7, name='spike')

saver = tf.train.Saver()
try:
        saver.restore(sess, './Day2/my_ckpt/spikes.ckpt')
        print(s1.eval())
except:
        print("file not found")
sess.close()
