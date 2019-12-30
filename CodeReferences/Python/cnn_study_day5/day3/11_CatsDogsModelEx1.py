from tensorflow.python.keras import layers
from tensorflow.python.keras import models
from tensorflow.python.keras import optimizers

# 아래 링크에서 여기서 하려는 짓과 비슷한 것을 함.
# https://keraskorea.github.io/posts/2018-10-24-little_data_powerful_model/

# ImageDataGenerator의 갑작스런 등장
# Image를 트레이닝하기 좋게 알아서 정규화하고 돌리고 지지고 볶고 해주는 클래스
# 이게 들어오면서 굉장히 헷가리게 되었다.
# 기존의 keras는 아래와 같은 구조
# 1. model 설계               layer 설계
# 2. model.compile            cost function 및 optimizer 선택
# 3. model.fit                데이터 입력 및, epoch, batch size 결정
# 4. model.evaluate           학습을 평가
# 와 같은 구조로 이루어져 있음

# 이 코드에서는 model.fit -> model.fit_generator 로 대체되었다.
# model.fit_generator에 ImageDataGenerator가 사용된다.

model = models.Sequential()
# 커널 크기는 3x3이며 필터 수는 32개, 입력이미지는 150x150x3=(width,height,channel)
model.add(layers.Conv2D(32, (3, 3), activation='relu', input_shape=(150, 150, 3)))
model.add(layers.MaxPool2D(2, 2))
# 커널 크기는 3x3 필터 수는 64개
model.add(layers.Conv2D(64, (3, 3), activation='relu'))
model.add(layers.MaxPool2D(2, 2))

model.add(layers.Conv2D(128, (3, 3), activation='relu'))
model.add(layers.MaxPool2D(2, 2))

model.add(layers.Conv2D(128, (3, 3), activation='relu'))
model.add(layers.MaxPool2D(2, 2))

model.add(layers.Flatten())

model.add(layers.Dense(512, activation='relu'))
model.add(layers.Dense(1, activation='sigmoid'))

print(model.summary())

model.compile(loss='binary_crossentropy',
              optimizer=optimizers.RMSprop(lr=1e-4),
              metrics=['acc'])

# 이미지 전처리 - 크기 맞춰주는 등등의 작업
# Anaconda prompt에서  pillow 라이브러리 설치 필요
# ImageDataGenerator를 사용하기 위함
from tensorflow.python.keras.preprocessing.image import ImageDataGenerator
import os

base_dir = './data/cats_and_dogs_small'
train_dir = os.path.join(base_dir, 'train')
validation_dir = os.path.join(base_dir, 'validation')

train_datagen = ImageDataGenerator(rescale=1./255)
validation_datagen = ImageDataGenerator(rescale=1./255)

train_generator = train_datagen.flow_from_directory(
    train_dir,
    target_size=(150, 150),
    batch_size=20,
    class_mode='binary'
)

validation_generator = validation_datagen.flow_from_directory(
    validation_dir,
    target_size=(150, 150),
    batch_size=20,
    class_mode='binary'
)

history = model.fit_generator(
    train_generator,
    steps_per_epoch=100, #하나의 epoch당 100개의 출력
    epochs=20,
    validation_data=validation_generator,
    validation_steps=50
)

model.save('cats_and_dogs_small_1.h5')

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
