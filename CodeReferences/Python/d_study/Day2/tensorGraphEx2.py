# -*- coding: utf-8 -*-
import tensorflow as tf
import os

os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'

graph = tf.Graph()
with graph.as_default():
    in_1 = tf.placeholder(dtype=tf.float32, shape=[None, 2], name='input_1')
    in_2 = tf.placeholder(dtype=tf.float32, shape=[None, 2], name='input_2')
    const = tf.constant(2, dtype=tf.float32, name='static_value')
    
    with tf.name_scope('Transformation'):
        with tf.name_scope('A'):
            a_mul = tf.multiply(in_1, const)
            a_out = tf.subtract(a_mul, in_1)

        with tf.name_scope('B'):
            b_mul = tf.multiply(in_2, const)
            b_out = tf.subtract(b_mul, in_2)

        with tf.name_scope('C'):
            c_div = tf.div(a_out, b_out)
            c_out = tf.add(c_div, const)

        with tf.name_scope('D'):
            d_div = tf.div(b_out, a_out)
            d_out = tf.add(d_div, const)

    out = tf.maximum(c_out, d_out)

    with tf.Session() as sess:
        in_1_data = [[1, 2], [3, 4]]
        in_2_data = [[5, 6], [7, 8]]
        _result, _c_out, _d_out = sess.run([out, c_out, d_out], feed_dict={in_1:in_1_data, in_2:in_2_data})
        print("\nout:\n{}:\nc_out:\n{}\nd_out:\n{}".format(_result, _c_out, _d_out))
        tf.summary.FileWriter('./graph_logs',sess.graph)