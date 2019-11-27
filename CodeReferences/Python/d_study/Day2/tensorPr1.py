import tensorflow as tf
import os

os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'
a = tf.constant(5, dtype=tf.int32, name='a_input')
b = tf.constant(2, dtype=tf.int32, name='b_input')
c = tf.constant(3, dtype=tf.int32, name='c_input')

d = tf.multiply(a, b)
e = tf.add(d, c)
f = tf.subtract(d, e)

sess = tf.Session()
print("\nf:", sess.run(f))

tf.summary.FileWriter('./graph_logs',sess.graph)
sess.close()