from tensorflow.python.keras.models import Sequential
from tensorflow.python.keras import layers
import tensorflow as tf
from tensorflow.examples.tutorials.mnist import input_data
import matplotlib.pyplot as plt
import numpy as np
from tensorflow.python.keras.preprocessing import image
from tensorflow.python.keras.datasets import mnist
from tensorflow.python.keras.utils import to_categorical
tf.set_random_seed(777)

class AE:
    def __init__(self):
        n_hidden = 256
        n_input = 784

        self.autoencoder = Sequential()
        self.autoencoder.add(layers.Dense(n_hidden, input_dim=n_input, activation='sigmoid'))
        self.autoencoder.add(layers.Dense(n_input, activation='sigmoid'))
        self.autoencoder.compile(loss='mean_squared_error', optimizer='adam')

        print(self.autoencoder.summary())

    def do_train(self):
        (X_train, _), (_, _) = mnist.load_data()
        X_train = X_train / 255
        X_train = X_train.reshape(X_train.shape[0], 28*28)

        self.autoencoder.fit(X_train, X_train, epochs=20, batch_size=100, verbose=False)

    def show_ae(self):
        (_, _), (X_test, _) = mnist.load_data()
        X_test = X_test / 255
        X_test = X_test.reshape(X_test.shape[0], 28 * 28)

        sample_size = 10
        samples = self.autoencoder.predict(X_test[:sample_size])

        fig, ax = plt.subplots(2, sample_size, figsize=(sample_size, 2))
        for i in range(sample_size):
            ax[0][i].set_axis_off()
            ax[1][i].set_axis_off()
            ax[0][i].imshow(np.reshape(X_test[i], (28, 28)))
            ax[1][i].imshow(np.reshape(samples[i], (28, 28)))
        plt.show()

    def show_ae_mydata(self, input_image):
        print(input_image)
        img = image.load_img(input_image, target_size=(28, 28))
        img_array = image.img_to_array(img)[:, :, 0:1]
        img_array = img_array.flatten()
        img_array = np.expand_dims(img_array, axis=0)

        samples = self.autoencoder.predict(img_array)
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