import numpy as np
import matplotlib.pyplot as plt
from tensorflow.python.keras.models import Sequential
from tensorflow.python.keras.preprocessing.image import array_to_img
from tensorflow.python.keras.layers import Conv2D, MaxPooling2D, UpSampling2D
from tensorflow.python.keras.datasets import mnist

(x_train, _), (x_test, _) = mnist.load_data()
x_train = x_train.reshape(-1, 28, 28, 1)
x_test = x_test.reshape(-1, 28, 28, 1)

x_train = x_train / 255.
x_test = x_test / 255.

plt.imshow(array_to_img(x_train[0]))
# plt.show()

def inserting_noise_to_data(data_x, percent=0.1):
    size = data_x.shape
    masking = np.random.binomial(n=1, p=percent, size=size) #이항분포 사용
    return data_x * masking

x_train_masked = inserting_noise_to_data(x_train)
x_test_masked = inserting_noise_to_data(x_test)

def make_gaussian_noise(data_x, scale=0.8):
    gaussian_data_x = data_x + np.random.normal(loc=0, scale=scale, size=data_x.shape)
    gaussian_data_x = np.clip(gaussian_data_x, a_min=0, a_max=1)
    return gaussian_data_x

x_train_gaussian = make_gaussian_noise(x_train)
x_test_gaussian = make_gaussian_noise(x_test)

plt.imshow(array_to_img(x_train_gaussian[0]))
# plt.show()
plt.imshow(array_to_img(x_train_masked[0]))
# plt.show()

autoencoder = Sequential()

#encoder
#stride = 1
autoencoder.add(Conv2D(16, (3, 3), 1, activation='relu', padding='same', input_shape=(28, 28, 1)))
autoencoder.add(MaxPooling2D((2, 2), padding='same'))
autoencoder.add(Conv2D(8, (3, 3), 1, activation='relu', padding='same'))
autoencoder.add(MaxPooling2D((2,2), padding='same'))

#decoder
autoencoder.add(Conv2D(8, (3, 3), 1, activation='relu', padding='same'))
autoencoder.add(UpSampling2D((2, 2)))
autoencoder.add(Conv2D(16, (3, 3), 1, activation='relu', padding='same'))
autoencoder.add(UpSampling2D((2, 2)))
autoencoder.add(Conv2D(1, (3, 3), 1, activation='sigmoid', padding='same')) #영상이미지 하나로 만들기 위함

# softmax가 아니라 binary_crossentropy사용
autoencoder.compile(loss='binary_crossentropy', optimizer='adam')

print(autoencoder.summary())

autoencoder.fit(x_train_gaussian,
                x_train,
                epochs=20,
                batch_size=20,
                shuffle=True)

gauss_pred = autoencoder.predict(x_test_gaussian)
sample_size = 10
fig, ax = plt.subplots(3, sample_size, figsize=(sample_size, 2))
for i in range(sample_size):
    ax[0][i].set_axis_off()
    ax[1][i].set_axis_off()
    ax[2][i].set_axis_off()
    ax[0][i].imshow(np.reshape(x_test[i], (28, 28)))
    ax[1][i].imshow(np.reshape(x_test_gaussian[i], (28, 28)))
    ax[2][i].imshow(np.reshape(gauss_pred[i], (28, 28)))
plt.show()