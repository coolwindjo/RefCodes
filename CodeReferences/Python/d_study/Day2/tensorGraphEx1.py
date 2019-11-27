# -*- coding: utf-8 -*-
import tensorflow as tf
import os

os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'

print("\ndefault_graph:\n", tf.get_default_graph())

g = tf.Graph()
print("\ncreate graph...:\n", g)
print("\ndefault_graph:\n", tf.get_default_graph())

with g.as_default() as graph:
    print("\ndefault_graph:\n", tf.get_default_graph())
    print("\ngraph:\n", graph)
    a = tf.multiply(2, 4)
    b = tf.add(a, 5)
    c = tf.subtract(b, 7)

    with tf.Session() as sess:
        result = sess.run(c)
        print(result)
        tf.summary.FileWriter('./graph_logs',sess.graph)

#a = tf.constant(5)
#print("\n", a.graph is g)
#sprint(a.graph is tf.get_default_graph())
