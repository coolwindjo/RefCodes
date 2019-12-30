import tensorflow as tf

## test for constant and concept of tensor
a = tf.constant(5, dtype=tf.float32)
b = tf.constant(10, dtype=tf.float32)
c = tf.constant(2, dtype=tf.float32)
d = a * b + c

print(d) # It is NOT 52. 'd' is just a node similar with graph
print("################")

sess = tf.Session()
result = sess.run(d)
print(result) # It is '52'.
print("################")

# It is each number
_a, _b, _c, _d = sess.run([a, b, c, d])
print(_a)
print(_b)
print(_c)
print(_d)
print("################")

#e는 계산되어 있지 않지만 f를 실행하면 f에 붙어있는 e가 먼저 계산되어 값이 전달됨
e = tf.multiply(a, b)
f = tf.add(e, c)
result2 = sess.run(f)
print(result2)
print("################")