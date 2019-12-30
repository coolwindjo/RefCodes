from tensorflow.python.keras.models import Sequential
from tensorflow.python.keras.layers import Dense
import pandas as pd
import numpy as np
import os
import tensorflow as tf

# 07파일의 강사버전
# 결과의 클래스가 두가지이므로 binary_crossentropy를 사용하였다.
# 가르쳐주지 않다가 강사 혼자 슬쩍 validation_split를 멋지게? 선보였다.
# training 샘플 중 일부분을 자동으로 validation으로 빼서 학습한다고 한다.
# 그럼 evaluate할 때 입력하는 x, y는 validation일까?


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

model.fit(x, y,
          validation_split=0.2,
          epochs=300,
          batch_size=500,
          )
result = model.evaluate(x,y)
print(result)