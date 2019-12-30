import tensorflow as tf

## test for TensorBoard
a = tf.constant(10, dtype=tf.float32, name='input_a')
b = tf.constant(50, dtype=tf.float32, name='input_b')
c = tf.constant(2, dtype=tf.float32, name='input_c')

sess = tf.Session()
d = tf.multiply(a, c, name='multi_d')
e = tf.add(d, c, name='add_e')
result2 = sess.run(e)
print(result2)
print("################")

tf.summary.FileWriter('./my_graph', sess.graph)

f = tf.constant([[1, 2], [5, 7]], dtype=tf.int32)
print('shape:', f.get_shape())
print('dtype:', f.dtype)
f = tf.cast(f, dtype=tf.float32)
print('dtype:', f.dtype)