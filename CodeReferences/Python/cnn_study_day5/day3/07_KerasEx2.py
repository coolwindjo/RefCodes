#tensorflow 1.12부터 내부에 keras가 들어있음
from tensorflow.python.keras.models import Sequential
from tensorflow.python.keras.layers import Dense
import numpy as np
import tensorflow as tf

#조금 더 복잡한 keras 예제

seed = 777
tf.set_random_seed(seed)
np.random.seed(seed)

data = np.loadtxt('data/wine.csv', delimiter=',')

x = data[:, 0:12]
y = data[:, 12]

model = Sequential()
model.add(Dense(30, input_dim=12, activation='relu'))
model.add(Dense(12, input_dim=30, activation='relu'))
model.add(Dense(8, input_dim=12, activation='relu'))
model.add(Dense(1, activation='sigmoid'))
model.compile(loss='mean_squared_error', optimizer='adam', metrics=['accuracy'])
model.fit(x, y, epochs=30, batch_size=100) #tensorflow의 sess.run과 같은 개념

#test로 사용할 데이터. 이번엔 없으므로 트레이닝 데이터 입력
#result = (loss, accuracy)
result = model.evaluate(x, y)
print('result:', result)