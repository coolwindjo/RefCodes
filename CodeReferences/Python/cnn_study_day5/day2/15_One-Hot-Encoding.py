import tensorflow as tf

#one-hot api가 이해되지 않아 작성한 코드
# tf.one_hot으로 형태를 완전히 바꾼뒤에 reshape으로 차원을 줄여야 함

x_data = [[0],[1],[2]]


sess = tf.Session()
x1 = tf.one_hot(x_data, 7).eval(session=sess)
print(x1)
print(x1.shape)

# tf reshape에서 -1은 None을 뜻함
y_one_hot = tf.reshape(x1, [-1, 7]).eval(session=sess)
print(y_one_hot)
print(y_one_hot.shape) # -> (?, 7)

x2 = tf.reshape(x_data, shape=[-1, 7]).eval(session=sess)
print(x2)
print(x2.shape)