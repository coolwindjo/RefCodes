from tensorflow.python.keras.models import Sequential
from tensorflow.python.keras.layers import Dense
import tensorflow as tf
from tensorflow.examples.tutorials.mnist import input_data
import matplotlib.pyplot as plt
import numpy as np
from tensorflow.python.keras.preprocessing import image
tf.set_random_seed(777)

class AE:
    def __init__(self):
        learning_rate = 0.1
        n_hidden = 256
        n_input = 784

        self.x = tf.placeholder(dtype=tf.float32, shape=[None, n_input])

        # encoder 레이어
        self.w_encode = tf.Variable(tf.random_normal([n_input, n_hidden]))
        self.b_encode = tf.Variable(tf.random_normal([n_hidden]))
        self.encoder = tf.nn.sigmoid(tf.matmul(self.x, self.w_encode) + self.b_encode)

        # decoder 레이어
        self.w_decode = tf.Variable(tf.random_normal([n_hidden, n_input]))
        self.b_decode = tf.Variable(tf.random_normal([n_input]))
        self.decoder = tf.nn.sigmoid(tf.matmul(self.encoder, self.w_decode) + self.b_decode)

        self.cost = tf.reduce_mean(tf.square(self.x - self.decoder))
        self.train = tf.train.RMSPropOptimizer(learning_rate=learning_rate).minimize(self.cost)

    def do_train(self):
        training_epoch = 20
        batch_size = 100

        self.mnist = input_data.read_data_sets('MNIst_data', one_hot=True)

        self.sess = tf.Session()
        self.sess.run(tf.global_variables_initializer())
        total_batch = int(self.mnist.train.num_examples / batch_size)

        for epoch in range(training_epoch):
            total_cost = 0
            for i in range(total_batch):
                batch_x, batch_y = self.mnist.train.next_batch(batch_size)
                _c, _ = self.sess.run([self.cost, self.train], feed_dict={self.x: batch_x})
                total_cost += _c
            print("epoch:{} avg_cost:{}".format(epoch + 1, total_cost / total_batch))

    def show_ae(self):
        sample_size = 10
        samples = self.sess.run(self.decoder, feed_dict={self.x: self.mnist.test.images[:sample_size]})

        fig, ax = plt.subplots(2, sample_size, figsize=(sample_size, 2))
        for i in range(sample_size):
            ax[0][i].set_axis_off()
            ax[1][i].set_axis_off()
            ax[0][i].imshow(np.reshape(self.mnist.test.images[i], (28, 28)))
            ax[1][i].imshow(np.reshape(samples[i], (28, 28)))
        plt.show()

    def show_ae_mydata(self, input_image):
        print(input_image)
        img = image.load_img(input_image, target_size=(28, 28))
        img_array = image.img_to_array(img)[:, :, 0:1]
        img_array = img_array.flatten()
        img_array = np.expand_dims(img_array, axis=0)

        samples = self.sess.run(self.decoder, feed_dict={self.x: img_array})
        plt.subplot(1, 2, 1)
        plt.imshow(np.reshape(img_array, (28, 28)))

        plt.subplot(1, 2, 2)
        plt.imshow(np.reshape(samples[0], (28, 28)))
        plt.show()



if __name__ == "__main__":
    ae = AE()
    ae.do_train()
    ae.show_ae()
    ae.show_ae_mydata('data/Number5.png')