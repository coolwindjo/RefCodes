import tensorflow as tf

a = tf.placeholder(dtype=tf.int32, shape=[2, 2], name='p_input')
b = tf.reduce_prod(a, name='prod_b')
c = tf.reduce_sum(a, name='sum_c')
d = tf.add(b, c, name='add_d')
print(tf.Session().run([b, c, d], feed_dict={a:[[5,3],[4,7]]}))