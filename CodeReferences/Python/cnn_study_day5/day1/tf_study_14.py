import tensorflow as tf

with tf.name_scope('scope_A'):
    a = tf.add(1, 3, name='a_add')
    b = tf.multiply(a, 3, name='a_mul')


with tf.name_scope('scope_B'):
    c = tf.add(4, 5 , name='b_add')
    d = tf.multiply(c, 6, name='b_mul')

e = b+d
sess = tf.Session()
print(sess.run(e))
tf.summary.FileWriter('./my_graph', graph=tf.get_default_graph())
