import tensorflow as tf

a = tf.constant(5, dtype=tf.float32)
b = tf.constant(10, dtype=tf.float32)
c = tf.constant(2, dtype=tf.float32)

d = a * b + c
print("a:\n", a)
print("\nd:\n", d)

sess = tf.Session()
result = sess.run(d)
print("\nresult:", result)

m = tf.multiply(a, b)
f = tf.add(m, c)
print("\nf:", sess.run(f))
print("\na:", sess.run(a))

p = print

p("# ----------------------------------------")

fetches = [a, b, c, d]
print("\n", sess.run([a, b, c]))
print("\n", sess.run(fetches=fetches))

