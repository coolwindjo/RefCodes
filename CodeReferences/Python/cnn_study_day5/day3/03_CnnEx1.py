import tensorflow as tf
import random
from tensorflow.examples.tutorials.mnist import input_data
tf.set_random_seed(777)

# tensorflow로 CNN을 구성하여 mnist 데이터셋을 학습하는 예제
# 여기서 부터는 training이 오래걸리기 시작한다.
# GPU를 사용하여 풀거나, colab을 사용하는 것을 추천.

mnist = input_data.read_data_sets('MNIst_data/', one_hot=True)

learning_rate = 0.01
training_epoch = 15
batch_size = 100

# 기존에 사용했던 데이터 형태는 (batch, 784)와 같았음.
# CNN에서는 (batch, width, height, channel)

x = tf.placeholder(dtype=tf.float32, shape=[None, 784])
x_img = tf.reshape(x, [-1, 28, 28, 1]) #-1은 batch를 의미

y = tf.placeholder(dtype=tf.float32, shape=[None, 10])

# 첫번째 convolution layer의 weight
# width, height, 입력개수(input), 커널의 개수
# weight 초기화는 표준오차가 0.01로
w1 = tf.Variable(tf.random_normal([3,3,1,32], stddev=0.01))

# convolution 연산 layer:  [batch, width, height, channel]
# 공식 설명에 batch와 channel을 고정시켜서 사용하라고 되어 있음. 사실 건너뛸 필요가 적음
# padding은 상, 하, 좌, 우에 0값의 padding을 삽입 -' SAME'으로 줬으므로 stride를 적용하더라도
# input 영상과 같은 출력 영상이 나타나도록 결정
L1 = tf.nn.conv2d(x_img, w1, strides=[1,1,1,1], padding='SAME')

#여기까지 진행하면 (batch, width, height, kernel)
# (?, 28, 28, 32)의 사이즈 : ?는 batch_size를 의미

# activation function을 ReLU로 설정
L1 = tf.nn.relu(L1)

# max pooling
# [batch, width, height, channel] -> 2 x 2의 max pooling
# stride와 padding은 conv2d와 같음
L1 = tf.nn.max_pool(L1, ksize=[1,2,2,1], strides=[1,2,2,1], padding='SAME')

# 여기까지 진행하면 (?, 14, 14, 32)
# pooling에 stride가 2가 포함되어 있으므로 사이즈가 절반으로 줄어든다.

# 두번째 convlution weight
w2 = tf.Variable(tf.random_normal([3, 3, 32, 64]))
L2 = tf.nn.conv2d(L1, w2, strides=[1,1,1,1], padding='SAME')
# (?, 14, 14, 64)
L2 = tf.nn.relu(L2)
L2 = tf.nn.max_pool(L2, ksize=[1,2,2,1], strides=[1,2,2,1], padding='SAME')
# (?, 7, 7, 64)

# 직렬화 과정. -1은 batch를 의미
L2_flat = tf.reshape(L2, [-1, 7*7*64])

# Fully connected layer
# 입력값이 L2 레이어를 직렬화한 것, 히든 레이어 없이 바로 숫자 10개 구분하는 출력으로
w3 = tf.get_variable('w3', shape=[7*7*64, 10],
                     initializer=tf.contrib.layers.xavier_initializer())
b = tf.Variable(tf.random_normal([10]))
logit = tf.matmul(L2_flat, w3) + b
hypothesis = tf.nn.softmax(logit)

cost = tf.reduce_mean(tf.nn.softmax_cross_entropy_with_logits_v2(logits=logit, labels=y))
train = tf.train.AdamOptimizer(learning_rate=learning_rate).minimize(cost)

sess = tf.Session()
sess.run(tf.global_variables_initializer())

for epoch in range(training_epoch):
    avg_cost = 0
    total_batch = int(mnist.train.num_examples / batch_size)

    for i in range(total_batch):
        batch_x, batch_y = mnist.train.next_batch(batch_size)
        _c, _ = sess.run([cost, train], feed_dict={x:batch_x, y:batch_y})
        avg_cost += _c / total_batch
    print("epoch:{}, cost:{}".format(epoch+1, avg_cost))

correct_prediction = tf.equal(tf.argmax(hypothesis, axis=1), tf.argmax(y, axis=1))
accuracy = tf.reduce_mean(tf.cast(correct_prediction, tf.float32))
print("acuuracy ", sess.run(accuracy, feed_dict={x:mnist.test.images, y:mnist.test.labels}))
