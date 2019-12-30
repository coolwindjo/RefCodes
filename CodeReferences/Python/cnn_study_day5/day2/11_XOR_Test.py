import tensorflow as tf
import numpy as np
tf.set_random_seed(777)
#히든 레이어는 3개
#각 레이어의 노드는 10개씩
#tf.matmul함수에 tf.matmul(x * w1)처럼 단항을 넣어 문제가 발생함
#tf.matmul(x, w1) 로 수정하여 괜찮아졌음.

learning_rate = 0.1
x_raw_data = [[0,0],[0,1],[1,0],[1,1]]
y_raw_data = [[0], [1], [1], [0]]

x_data = np.array(x_raw_data, dtype=np.float32)
y_data = np.array(y_raw_data, dtype=np.float32)

x = tf.placeholder(dtype=tf.float32, shape=[None, 2])
y = tf.placeholder(dtype=tf.float32, shape=[None, 1])

w1 = tf.Variable(tf.random_normal([2, 10]))
b1 = tf.Variable(tf.random_normal([10]))
layer1 = tf.sigmoid(tf.matmul(x, w1) + b1)

w2 = tf.Variable(tf.random_normal([10, 10], dtype=tf.float32))
b2 = tf.Variable(tf.random_normal([10], dtype=tf.float32))
layer2 = tf.sigmoid(tf.matmul(layer1, w2) + b2)

w3 = tf.Variable(tf.random_normal([10, 10], dtype=tf.float32))
b3 = tf.Variable(tf.random_normal([10], dtype=tf.float32))
layer3 = tf.sigmoid(tf.matmul(layer2, w3) + b3)

w4 = tf.Variable(tf.random_normal([10, 1], dtype=tf.float32))
b4 = tf.Variable(tf.random_normal([1], dtype=tf.float32))

hypothesis = tf.sigmoid(tf.matmul(layer3, w4) + b4)
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


