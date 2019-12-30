import tensorflow as tf
import numpy as np
tf.set_random_seed(777)
#두 개의 계층으로 XOR을 분류하는 상황을 재현
#seed와 step에 따라서 간혹 0.75가 나오는 상황이 발생한다

learning_rate = 0.1
x_raw_data = [[0,0],[0,1],[1,0],[1,1]]
y_raw_data = [[0], [1], [1], [0]]

x_data = np.array(x_raw_data, dtype=np.float32)
y_data = np.array(y_raw_data, dtype=np.float32)

x = tf.placeholder(dtype=tf.float32, shape=[None, 2])
y = tf.placeholder(dtype=tf.float32, shape=[None, 1])

w1 = tf.Variable(tf.random_normal([2, 2]), name='weight1')
b1 = tf.Variable(tf.random_normal([2]), name='bias1')
layer1 = tf.sigmoid(tf.matmul(x, w1) + b1)

w2 = tf.Variable(tf.random_normal([2, 1]), name='weight2')
b2 = tf.Variable(tf.random_normal([1]), name='bias2')

hypothesis = tf.sigmoid(tf.matmul(layer1, w2) + b2)
cost = -tf.reduce_mean(y * tf.log(hypothesis) + (1 - y) * tf.log(1 - hypothesis))

train = tf.train.GradientDescentOptimizer(learning_rate=0.01).minimize(cost)

predicted = tf.cast(hypothesis > 0.5, dtype=tf.float32)
accuracy = tf.reduce_mean(tf.cast(tf.equal(predicted, y), dtype=tf.float32))

with tf.Session() as sess:
    sess.run(tf.global_variables_initializer())
    for step in range(50001):
        _cost, _ = sess.run([cost, train], feed_dict={x: x_data, y: y_data})
        if step % 200 == 0:
            print('step:{} cost:{}'.format(step, _cost))

    h, c, a = sess.run([hypothesis, predicted, accuracy],
                       feed_dict={x: x_data, y: y_data})
    print("\nHypothesis: ", h, "\nCorrect (Y): ", c, "\nAccuracy: ", a)
