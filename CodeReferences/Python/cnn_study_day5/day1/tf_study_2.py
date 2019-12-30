import tensorflow as tf

a = tf.constant([5, 3], dtype=tf.float32)
b = tf.reduce_prod(a)   #들어오는 값이 무엇이든 곱해서 하나의 scalar값으로 변환 #차원 하나만 줄이고 numpy 연산
c = tf.reduce_sum(a)    #들어오는 값이 무엇이든 더해서 하나의 scalar값으로 변환
d = tf.add(b, c)

sess = tf.Session()
result = sess.run(d)
print(result)           # result is 23

e = tf.constant([2, 3], dtype=tf.float32)
f = tf.constant([4, 5], dtype=tf.float32)
c = tf.add(e, f)
result2 = sess.run(c)
print(result2)
# 입력상태가 벡터이기 때문에 출력도 벡터 
