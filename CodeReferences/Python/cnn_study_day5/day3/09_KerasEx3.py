from tensorflow.python.keras.models import Sequential
from tensorflow.python.keras.layers import Dense
import pandas as pd
import numpy as np
import os
import tensorflow as tf

# 8번 예제에 epoch만 10배로 늘렸고, model.fit의 리턴값을 history 변수에 담았다
# history변수를 사용해 학습과정을 기록하였다.
#그래프를 그려보면 loss가 튀는 부분이 발생
#그 부분이 overfitting이 발생하는 지점

np.random.seed(777)
tf.set_random_seed(777)

df = pd.read_csv('data/wine.csv', header=None)
data = df.values
x = data[:,0:12]
y = data[:, 12]

model = Sequential()
model.add(Dense(30, input_dim=12, activation='relu'))
model.add(Dense(12, activation='relu'))
model.add(Dense(8, activation='relu'))
model.add(Dense(1, activation='sigmoid'))

model.compile(loss='binary_crossentropy',
              optimizer='adam',
              metrics=['accuracy'])

history = model.fit(x, y,
          validation_split=0.33,
          epochs=3500,
          batch_size=500,
          )
result = model.evaluate(x,y)
print(result)

y_vloss = history.history['val_loss']
y_acc = history.history['acc']

import matplotlib.pyplot as plt
x_len = np.arange(len(y_acc))
plt.plot(x_len, y_vloss, 'o', c='red', markersize=3)
plt.plot(x_len, y_acc, 'o', c='blue', markersize=3)
plt.show()

