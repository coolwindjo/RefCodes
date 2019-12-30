import tensorflow as tf
import numpy as np
import matplotlib.pyplot as plt

from tensorflow.examples.tutorials.mnist import input_data
mnist = input_data.read_data_sets('MNIst_data', one_hot=True)

tf.set_random_seed(777)

learning_rate = 0.1
training_epoch = 20
batch_size = 100

n_hidden = 256
n_input = 784

x = tf.placeholder(dtype=tf.float32, shape=[None, n_input])

# encoder 레이어
w_encode = tf.Variable(tf.random_normal([n_input, n_hidden]))
b_encode = tf.Variable(tf.random_normal([n_hidden]))
encoder = tf.nn.sigmoid(tf.matmul(x, w_encode) + b_encode)

# decoder 레이어
w_decode = tf.Variable(tf.random_normal([n_hidden, n_input]))
b_decode = tf.Variable(tf.random_normal([n_input]))
decoder = tf.nn.sigmoid(tf.matmul(encoder, w_decode) + b_decode)

cost = tf.reduce_mean(tf.square(x-decoder))
train = tf.train.RMSPropOptimizer(learning_rate=learning_rate).minimize(cost)

sess = tf.Session()
sess.run(tf.global_variables_initializer())
total_batch = int(mnist.train.num_examples/batch_size)

for epoch in range(training_epoch):
    total_cost = 0
    for i in range(total_batch):
        batch_x, batch_y = mnist.train.next_batch(batch_size)
        _c, _ = sess.run([cost, train], feed_dict={x:batch_x})
        total_cost += _c
    print("epoch:{} avg_cost:{}".format(epoch+1, total_cost/total_batch))

####################################################
sample_size = 10
samples = sess.run(decoder, feed_dict={x: mnist.test.images[:sample_size]})

fig, ax = plt.subplots(2, sample_size, figsize=(sample_size, 2))
for i in range(sample_size):
    ax[0][i].set_axis_off()
    ax[1][i].set_axis_off()
    ax[0][i].imshow(np.reshape(mnist.test.images[i], (28, 28)))
    ax[1][i].imshow(np.reshape(samples[i], (28, 28)))
plt.show()