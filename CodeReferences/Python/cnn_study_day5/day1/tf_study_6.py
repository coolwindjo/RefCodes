import tensorflow as tf

input_data = [1,2,3,4,5]
x = tf.placeholder(dtype=tf.float32)
w = tf.Variable([2], dtype=tf.float32)
y = tf.add(x, w)

sess = tf.Session()

## 초기화도 하나의 노드일 뿐. 초기화를 하기 위해 노드를 session상에서 실행시켜야 함
init = tf.global_variables_initializer()
sess.run(init)

result = sess.run(y, feed_dict={x:input_data})
print(result)
