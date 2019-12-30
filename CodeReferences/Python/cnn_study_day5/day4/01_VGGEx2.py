from scipy.optimize.zeros import results_c
from tensorflow.python.keras.applications import VGG16
from tensorflow.python.keras.preprocessing.image import ImageDataGenerator
from tensorflow.python.keras import models
from tensorflow.python.keras import layers
from tensorflow.python.keras import optimizers
import matplotlib.pyplot as plt
import os
import numpy as np

base_dir = './data/cats_and_dogs_small'
train_dir = os.path.join(base_dir, 'train')
validation_dir = os.path.join(base_dir, 'validation')
test_dir = os.path.join(base_dir, 'test')

batch_size = 20

#include_top=False의 이미는 VGG16에 붙어있는 Fuuly connectyed layer를 사용하지 않겠다
conv_base = VGG16(weights='imagenet',
                  include_top=False,
                  input_shape=(150, 150, 3))
print(conv_base.summary())


def extract_features(directory, sample_count):
    # VGG16 conv 계층의 마지막 아웃풋이 4 x 4x 512
    features = np.zeros(shape=(sample_count, 4, 4, 512))
    labels = np.zeros(shape=(sample_count))

    datagen = ImageDataGenerator(rescale=1. / 255)
    generator = datagen.flow_from_directory(
        directory,
        target_size=(150,150),
        batch_size=batch_size,
        class_mode='binary'
    )

    i = 0
    # generator를 for 루프에 넣으면 batch 사이즈만큼 잘라서
    # 데이터를 넘겨주게 됨
    for input_batch, labels_batch in generator:
        # 결과값들만 출력함
        features_batch = conv_base.predict(input_batch)

        # ex)
        # 0*batch:1*batch=0:20
        # 1*batch:2*batch=20:40
        features[i * batch_size : (i + 1) * batch_size] = features_batch
        labels[i * batch_size : (i + 1) * batch_size] = labels_batch
        i += 1
        if i * batch_size >= sample_count:
            break
    return features, labels
# 여기에서 return 문장을 for문 안에 두어 샘플수가 적어서 100이 나올 수 밖에 없는 예제

# extract_features 함수를 호출하면
# sameple_count 수 만큼 conv 레이어를 통과시킨 결과를 하나의 벡터에 저장한다
# 매번 batch size만큼 conv를 통과시키고 model을 학습시키는 과정을 거치는 거 보다
# 고정되어 있는 conv 계층의 결과를 미리 다 만들어두고 시작하는 것이 빠르기 때문이다
# 특히, ImageDataGenerator에서 이미지 회전이나 다른 조작작업을 하게 될 때 속도는 더욱 두드러질 것
train_features, train_labels = extract_features(train_dir, 2000)
validation_features, validation_labels = extract_features(validation_dir, 1000)
test_features, test_labels = extract_features(test_dir, 1000)

train_features = np.reshape(train_features, (2000, 4*4*512))
validation_features = np.reshape(validation_features, (1000, 4*4*512))
test_features = np.reshape(test_features, (1000, 4*4*512))

model = models.Sequential()
model.add(layers.Dense(256, input_dim=4*4*512, activation='relu'))
model.add(layers.Dropout(0.5))
model.add(layers.Dense(1, activation='sigmoid'))

model.compile(optimizer=optimizers.RMSprop(lr=2e-5),
              loss='binary_crossentropy',
              metrics=['acc'])

history = model.fit(train_features, train_labels,
                    epochs = 30,
                    batch_size = batch_size,
                    validation_data=(validation_features, validation_labels))

result = model.evaluate(test_features, test_labels)
print('result:', result)

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

