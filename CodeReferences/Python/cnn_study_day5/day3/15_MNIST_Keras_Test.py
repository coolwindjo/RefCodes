from tensorflow.python.keras.datasets import mnist
from tensorflow.python.keras.preprocessing.image import ImageDataGenerator

from tensorflow.python.keras import layers
from tensorflow.python.keras import models
from tensorflow.python.keras import optimizers

from tensorflow.python.keras.utils import to_categorical
import numpy as np

# 과제... 이 코드는 실행하지 말것!
# 실행하면 컴퓨터가 죽는다
# 왜 문제가 되는지 아직도 알 수 없다
# 내일 강사에게 답을 받으면 알 수 있을 것으로 보임.

(X_train, Y_train), (X_test, Y_test) = mnist.load_data()
X_train = X_train / 255
X_test = X_test / 255
Y_train = to_categorical(Y_train)
Y_test = to_categorical(Y_test)

X_train = X_train.reshape(X_train.shape[0], 28, 28, 1)
X_test = X_test.reshape(X_test.shape[0], 28, 28, 1)


model = models.Sequential()
model.add(layers.Conv2D(32, (3, 3), activation='relu', input_shape=(28, 28, 1)))
model.add(layers.MaxPool2D(eva2, 2))
model.add(layers.Conv2D(64, (3, 3), activation='relu'))
model.add(layers.MaxPool2D(2, 2))

model.add(layers.Flatten())
model.add(layers.Dense(512, activation='relu'))
model.add(layers.Dense(10, activation='sigmoid'))

print(model.summary())
model.compile(loss='categorical_crossentropy', optimizer='adam', metrics=['acc'])

history = model.fit(X_train,
                    Y_train,
                    steps_per_epoch=10, #하나의 epoch당 100개의 출력
                    epochs=10,
                    batch_size=32,
                    validation_data=(X_test, Y_test),
                    validation_steps=10)


import matplotlib.pyplot as plt
acc = history.history['acc']
val_acc = history.history['val_acc']
loss = history.history['loss']
val_loss = history.history['val_loss']

epoches = range(len(acc))
plt.plot(epoches, acc, 'bo', label='Train acc')
plt.plot(epoches, val_acc, 'b', label='Validation acc')
plt.title('Training and Validation accuracy')
plt.legend()
plt.figure()

plt.plot(epoches, loss, 'bo', label='Train loss')
plt.plot(epoches, val_loss, 'b', label='Validation loss')
plt.title('Training and Validation loss')
plt.legend()
plt.show()

