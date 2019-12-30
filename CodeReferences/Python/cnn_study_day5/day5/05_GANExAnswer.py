import tensorflow as tf
import matplotlib.pyplot as plt
import numpy as np

from tensorflow.examples.tutorials.mnist import input_data
mnist = input_data.read_data_sets('./mnist/data/', one_hot=True)

total_epoch = 100
batch_size = 100
learning_rate = 0.0002
n_hidden = 256
n_input = 784
n_noise = 128

x = tf.placeholder(dtype=tf.float32, shape=[None, n_input])
z = tf.placeholder(dtype=tf.float32, shape=[None, n_noise])

#생성자
G_w1 = tf.Variable(tf.random_normal([n_noise, n_hidden], stddev=0.01))
G_b1 = tf.Variable(tf.random_normal([n_hidden]))
G_w2 = tf.Variable(tf.random_normal([n_hidden, n_input], stddev=0.01))
G_b2 = tf.Variable(tf.random_normal([n_input]))

#판별자
D_w1 = tf.Variable(tf.random_normal([n_input, n_hidden], stddev=0.01))
D_b1 = tf.Variable(tf.random_normal([n_hidden]))
D_w2 = tf.Variable(tf.random_normal([n_hidden, 1], stddev=0.01))
D_b2 = tf.Variable(tf.zeros([1]))

def generator(noise_z):
    hidden = tf.nn.relu(tf.matmul(noise_z, G_w1) + G_b1)
    output = tf.nn.sigmoid(tf.matmul(hidden, G_w2) + G_b2)
    return output



def discriminator(inputs):
    hidden = tf.nn.relu(tf.matmul(inputs, D_w1) + D_b1)
    output = tf.nn.sigmoid(tf.matmul(hidden, D_w2) + D_b2)
    return output

G = generator(z)

D_real = discriminator(x)
D_gene = discriminator(G)

#discriminator loss func
loss_D = tf.reduce_mean(tf.log(D_real) + tf.log(1 - D_gene))

#generatorloss func
loss_G = tf.reduce_mean(tf.log(D_gene))

D_var_list = [D_w1, D_b1, D_w2, D_b2]
G_var_list = [G_w1, G_b1, G_w2, G_b2]

train_D = tf.train.AdamOptimizer(learning_rate=learning_rate).minimize(-loss_D, var_list=D_var_list)
train_G = tf.train.AdamOptimizer(learning_rate=learning_rate).minimize(-loss_G, var_list=G_var_list)

def get_noise(batch_size, n_noise):
    return np.random.normal(size=(batch_size, n_noise))

sess = tf.Session()
sess.run(tf.global_variables_initializer())

total_batch = int(mnist.train.num_examples/batch_size)
loss_val_D, loss_val_G = 0, 0

for epoch in range(total_epoch):
    for i in range(total_batch):
        batch_xs, batch_ys = mnist.train.next_batch(batch_size)
        noise = get_noise(batch_size, n_noise)
        _, loss_val_D = sess.run([train_D, loss_D], feed_dict={x:batch_xs, z:noise})
        _, loss_val_G = sess.run([train_G, loss_G], feed_dict={z:noise})

    print('Epoch:', '%04d' % epoch,'D loss: {:.4}'.format(loss_val_D), 'G loss: {:.4}'.format(loss_val_G))

    if epoch == 0 or (epoch + 1) % 10 == 0:
        sample_size = 10
        noise = get_noise(sample_size, n_noise)
        samples = sess.run(G, feed_dict={z: noise})
        fig, ax = plt.subplots(1, sample_size, figsize=(sample_size, 1))

        for i in range(sample_size):
            ax[i].set_axis_off()
            ax[i].imshow(np.reshape(samples[i], (28, 28)))
        plt.savefig('samples/{}.png'.format(str(epoch).zfill(3)), bbox_inches='tight')
        plt.close(fig)


