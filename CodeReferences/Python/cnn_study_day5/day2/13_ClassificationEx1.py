import tensorflow as tf
import numpy as np

tf.set_random_seed(777)

#입력 데이터가 16개, 답이 하나인 데이터. 답의 종류가 7가지

data = np.loadtxt('data/data-04-zoo.csv', delimiter=',', dtype=np.float32)
x_data = data[:, 0:-1] #모든 행에서 추출, 첫컬럽부터 마지막컬럽전까지
y_data = data[:, [-1]] #모든 행에서 추출, 가장 마지막 칼럼만 추출

x = tf.placeholder(dtype=tf.float32, shape=[None, 16]) # -> (?, 16)
y = tf.placeholder(dtype=tf.int32, shape=[None, 1])  # -> (?, 1)

# 바로 one_hot_encoding 방법
# y_one_hot = tf.reshape(y, [-1, 7])
# print(y_one_hot.get_shape()) # -> (?, 1, 7)


# tensorflow의 one_hot api를 이용하는 방법
y_one_hot = tf.one_hot(y, 7)
print(y_one_hot.get_shape()) # -> (?, 1, 7)
# :RNN에서 one-hot을 주로 사용, RNN에서 batch x seq x input
# tensorflow가 RNN에서 하던것처럼 해서 (?, 1, 7)이 됨... 변형 필요

# tf reshape에서 -1은 None을 뜻함
y_one_hot = tf.reshape(y_one_hot, [-1, 7])
print(y_one_hot.get_shape()) # -> (?, 7)


w = tf.Variable(tf.random_normal([16, 7]), name='weight')
b = tf.Variable(tf.random_normal([7]), name='bias')

# weighted sum
logit = tf.matmul(x, w) + b
# softmax 첫 등장. 결과를 모두 더해서 1이 되도록 만든다. 그냥 더한것이 아니라 각 값에 지수를 취해 값을 뻥튀기 함. 왜?
hypothesis = tf.nn.softmax(logit)

# 기존의 수식 : 31, 32줄을 대체하는 코드, tensorflow에서 제공하는 것이 더 효율적인 코드
# 이전예제에서 계속 사용하던 코드
#cost = tf.reduce_mean(-tf.reduce_sum(y * tf.log(hypothesis), axis=1))

cost_i = tf.nn.softmax_cross_entropy_with_logits_v2(logits=logit, labels=y_one_hot)
cost = tf.reduce_mean(cost_i)
train = tf.train.GradientDescentOptimizer(learning_rate=0.1).minimize(cost)

prediction = tf.argmax(hypothesis, axis=1)
accuracy = tf.reduce_mean(tf.cast(tf.equal(prediction, tf.argmax(y_one_hot, axis=1)), tf.float32))

with tf.Session() as sess:
    sess.run(tf.global_variables_initializer())
    for step in range(2001):
        _cost,_acc, _ = sess.run([cost, accuracy, train], feed_dict={x: x_data, y: y_data})
        if step % 200 == 0:
            print('step:{} accuracy:{}, cost:{}'.format(step, _acc, _cost))

    a = sess.run(hypothesis, feed_dict={x:[[1,11,7,9,6,7,8,5,4,3,2,1,5,4,8,7]]})
    print('a:{}',format(a))
    print(sess.run(tf.argmax(a, axis=1)))

    pred = sess.run(prediction, feed_dict={x:x_data})
    for p, y in zip(pred, y_data):
        print('prediction:{}, correct:{}'.format(p, y))

