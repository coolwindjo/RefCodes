from tensorflow.python.keras.datasets import cifar10
from tensorflow.python.keras import models
from tensorflow.python.keras import layers
from tensorflow.python.keras.utils import np_utils
import matplotlib.pyplot as plt
import tensorflow as tf

#colab를 위한 코드

with tf.device('/gpu:0'):
    num_classes = 10
    im_rows = 32
    im_cols = 32
    im_size = im_rows * im_cols * 3

    (x_train, y_train), (x_test, y_test) = cifar10.load_data()
    x_train = x_train.astype('float32') / 255
    y_train = np_utils.to_categorical(y_train)
    x_test = x_test.astype('float32') / 255
    y_test = np_utils.to_categorical(y_test)

    # for only dense
    x_train = x_train.reshape(x_train.shape[0], 32 * 32 * 3)
    x_test = x_test.reshape(x_test.shape[0], 32 * 32 * 3)

    labels = ["airplane", "automobile", "bird", "cat", "deer",
              "dog", "frog", "horse", "ship", "truck"]

    model = models.Sequential()
    model.add(layers.Dense(8192, input_dim=32 * 32 * 3, activation='relu'))
    model.add(layers.Dropout(0.5))
    model.add(layers.Dense(4096, activation='relu'))
    model.add(layers.Dropout(0.5))
    model.add(layers.Dense(2048, activation='relu'))
    model.add(layers.Dropout(0.5))
    model.add(layers.Dense(1024, activation='relu'))
    model.add(layers.Dropout(0.5))
    model.add(layers.Dense(1024, activation='relu'))
    model.add(layers.Dropout(0.5))
    model.add(layers.Dense(512, activation='relu'))
    model.add(layers.Dropout(0.5))
    model.add(layers.Dense(10, activation='softmax'))

    print(model.summary())
    model.compile(loss='categorical_crossentropy', optimizer='adam', metrics=['acc'])

    history = model.fit(x_train,
                        y_train,
                        validation_data=(x_test, y_test),
                        epochs=300,
                        batch_size=5000,
                        )

    model.save('/content/drive/My Drive/cnn_data/cifar10_dense.h5')

    acc = history.history['acc']
    val_acc = history.history['val_acc']
    loss = history.history['loss']
    val_loss = history.history['val_loss']

    epochs = range(len(acc))

    plt.plot(epochs, acc, 'bo', label='Training acc')
    plt.plot(epochs, val_acc, 'b', label='Validation acc')
    plt.title('Training and validation accuracy')
    plt.legend()

    plt.figure()

    plt.plot(epochs, loss, 'bo', label='Training loss')
    plt.plot(epochs, val_loss, 'b', label='Validation loss')
    plt.title('Training and validation loss')
    plt.legend()

    plt.show()