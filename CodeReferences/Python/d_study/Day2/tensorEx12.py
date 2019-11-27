# -*- coding: utf-8 -*-
import tensorflow as tf
import os

os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'

with tf.name_scope('Scope_A'):
    a = tf.add(1, 3, name='sa_add')
    b = tf.multiply(a, 3, name='sa_mul')

with tf.name_scope('Scope_B'):
    c = tf.add(4, 5, name='sb_add')
    d = tf.multiply(c, 6, name='sb_mul')

with tf.Session() as sess:
    result = sess.run(b+d)
    print(result)
    tf.summary.FileWriter('./graph_logs',sess.graph)