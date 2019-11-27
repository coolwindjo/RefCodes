import tensorflow as tf

a = tf.constant([5, 3], name='input_a')
b = tf.reduce_sum(a, name='sum_b')
c = tf.reduce_prod(a, name='prod_c')
d = tf.add(b, c, name='add_d')
sess = tf.Session()
print("\nd:", sess.run(d))

tf.summary.FileWriter('./graph_logs',sess.graph)
sess.close()