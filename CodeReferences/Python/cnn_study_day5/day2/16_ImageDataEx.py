import tensorflow as tf
import random
import matplotlib.pyplot as plt
from tensorflow.examples.tutorials.mnist import input_data

## MNIST 데이터를 Fully connected layer로 구분

tf.set_random_seed(777)

mnist = input_data.read_data_sets('MNIST_data/', one_hot=True)

learning_rate = 0.001
training_epoches = 15
batch_size = 100

# 28 x 28 크기의 이미지가 1차원으로 펴면 784개
x = tf.placeholder(dtype=tf.float32, shape=[None, 784])
# 숫자는 0~9까지 총 10개이므로 output노드는 10개
y = tf.placeholder(dtype=tf.float32, shape=[None, 10])

w = tf.Variable(tf.random_normal([784,10]))
b = tf.Variable(tf.random_normal([10]))

logit = tf.matmul(x, w) + b
hypothesis = tf.nn.softmax(logit)

cost = tf.reduce_mean(tf.nn.softmax_cross_entropy_with_logits_v2(logits=logit, labels=y))
train = tf.train.AdamOptimizer(learning_rate=learning_rate).minimize(cost)

sess = tf.Session()
sess.run(tf.global_variables_initializer())

#epoch는 전체 트레이닝샘플을 학습한 것을 의미
for epoch in range(training_epoches):
    avg_cost = 0
    #training sample 개수가 60,000개. batch_size가 100개이므로 한 번에 600장씩 학습
    #일반적으로는 batch size가 클수록 좋음
    #batch size가 작으면 학습속도도 느리며, 학습결과가 자꾸 튀게 됨
    #batch size가 클수록 여러개의 데이터를 한번에 학습하기 때문에 안정적, 그러나 컴퓨터의 메모리가(또는 컴퓨팅파워) 부족함
    total_batch = int(mnist.train.num_examples / batch_size)

    for i in range(total_batch):
        batch_x, batch_y = mnist.train.next_batch(batch_size)
        fdata = {x:batch_x, y:batch_y}
        _c, _ = sess.run([cost, train], feed_dict=fdata)
        avg_cost += _c / total_batch

    print('epoch:{}, cost:{}'.format(epoch+1, avg_cost))

#test 데이터에 대한 성능을 표시, 테스트데이터는 10,000개
#일반적으로 7:3, 8:2 정도의 비율을 가짐
accuracy = tf.reduce_mean(tf.cast(tf.equal(tf.argmax(hypothesis, axis=1), tf.argmax(y, axis=1)), dtype=tf.float32))
print('accuracy:', sess.run(accuracy, feed_dict={x:mnist.test.images, y:mnist.test.labels}))