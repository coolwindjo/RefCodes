#tensorflow 1.12부터 내부에 keras가 들어있음
from tensorflow.python.keras.models import Sequential
from tensorflow.python.keras.layers import Dense
import numpy as np
import tensorflow as tf

# Keras로 Fully connected layer를 만들어보는 예제
# 매우 간단하게 구현할 수 있다.
# 간단한만큼 원리를 제대로 알지 못하는 경우가 허다할 것으로 보임...
# 결과가 잘 나오면 장땡이긴 함.

seed = 777
tf.set_random_seed(seed)
np.random.seed(seed)

data = np.loadtxt('data/ThoraricSurgery.csv', delimiter=',')

x = data[:, 0:17]
y = data[:, 17]

model = Sequential()
model.add(Dense(30, input_dim=17, activation='relu'))
model.add(Dense(1, activation='sigmoid'))
model.compile(loss='mean_squared_error', optimizer='adam', metrics=['accuracy'])
model.fit(x, y, epochs=30, batch_size=10) #tensorflow의 sess.run과 같은 개념

#test로 사용할 데이터. 이번엔 없으므로 트레이닝 데이터 입력
#result = (loss, accuracy)
result = model.evaluate(x, y)
print('result:', result)