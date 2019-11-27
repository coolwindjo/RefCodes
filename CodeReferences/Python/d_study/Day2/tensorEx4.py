import tensorflow as tf

a = tf.constant([[1, 2, 3],
                [4, 5, 6]])
print("\na.shape:", a.get_shape())

b = tf.constant([[1],
                 [0],
                 [1]])
print("\nb.shape:", b.get_shape())

c = tf.matmul(a, b)
sess = tf.Session()
print("\nc:\n", sess.run(c))

d = tf.constant([1, 2, 3])
e = tf.expand_dims(d, 1)
print("\nd.shape:", d.get_shape())
print("\ne.shape:", e.get_shape())

f = tf.matmul(a, e)
print("\nf:\n", sess.run(f))

p=print
p("# -----------------------------------------")

x = tf.constant([1, 2, 3], dtype=tf.float32)
print(x.dtype)

x = tf.cast(x, tf.int64)
print(x.dtype)
