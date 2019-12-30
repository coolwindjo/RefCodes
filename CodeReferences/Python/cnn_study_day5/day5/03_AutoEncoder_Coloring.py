import os
import glob
import math
import numpy as np
import cv2
from tensorflow.python.keras.models import Sequential
from tensorflow.python.keras.layers import Conv2D, Conv2DTranspose
from tensorflow.python.keras.preprocessing.image import load_img, img_to_array, array_to_img

data_path = 'data/img/colorize'
data_lists = glob.glob(os.path.join(data_path, '*.jpg'))
print(len(data_lists))

val_n_sample = math.floor(len(data_lists) * 0.1) # 10%만큼
test_n_sample = math.floor(len(data_lists) * 0.1) # 10%만큼
train_n_sample = len(data_lists) - val_n_sample - test_n_sample

val_lists = data_lists[:val_n_sample]
test_lists = data_lists[val_n_sample:(val_n_sample + test_n_sample)]
train_lists = data_lists[(val_n_sample + test_n_sample):]

print(len(val_lists))
print(len(test_lists))
print(len(train_lists))

img_size = 224
def rgb2lab(rgb):
    assert rgb.dtype == 'uint8'
    return cv2.cvtColor(rgb, cv2.COLOR_RGB2LAB)

def lab2rgb(lab):
    assert lab.dtype == 'uint8'
    return cv2.cvtColor(lab, cv2.COLOR_LAB2RGB)

def get_lab_from_data_list(data_list):
    x_lab = []
    for f in data_list:
        rgb = img_to_array(load_img(f, target_size=(img_size, img_size))).astype(np.uint8)
        lab = rgb2lab(rgb)
        x_lab.append(lab)
    return np.stack(x_lab)

autoencoder = Sequential()

#encoder
# LAB 중 L만 넣기 때문에 입력 채널이 하나
autoencoder.add(Conv2D(32, (3, 3), 1, activation='relu', padding='same', input_shape=(224, 224, 1)))
autoencoder.add(Conv2D(64, (3, 3), (2, 2), activation='relu', padding='same'))
autoencoder.add(Conv2D(128, (3, 3), (2, 2), activation='relu', padding='same'))
autoencoder.add(Conv2D(256, (3, 3), (2, 2), activation='relu', padding='same'))

#decoder
autoencoder.add(Conv2DTranspose(128, (3,3), (2,2), activation='relu', padding='same'))
autoencoder.add(Conv2DTranspose(64, (3,3), (2,2), activation='relu', padding='same'))
autoencoder.add(Conv2DTranspose(32, (3,3), (2,2), activation='relu', padding='same'))
autoencoder.add(Conv2DTranspose(2, (1,1), (1,1), activation='relu', padding='same'))
# 하나를 넣어 두개가 나오기 때문에 마지막 레이어의 activation 변경없이 relu를 쓴다고 함... 왜?
# sigmoid도 가능하다고 함

autoencoder.compile(loss='mse',
                    optimizer='adam')

print(autoencoder.summary())

def generator_with_preprocessing(data_list, batch_size, shuffle=False):
    while True:
        if shuffle:
            np.random.shuffle(data_list)
        for i in range(0, len(data_list), batch_size):
            batch_list = data_list[i:(i+batch_size)]
            batch_lab = get_lab_from_data_list(batch_list)
            batch_l = batch_lab[:, :, :, 0:1]
            batch_ab = batch_lab[:, :, :, 1:]
            yield (batch_l, batch_ab)

batch_size = 30

train_gen = generator_with_preprocessing(train_lists, batch_size, shuffle=True)
val_gen = generator_with_preprocessing(val_lists, batch_size)
test_gen = generator_with_preprocessing(test_lists, batch_size)

train_steps = math.ceil(len(train_lists)/batch_size)
val_steps = math.ceil(len(val_lists)/batch_size)
test_steps = math.ceil(len(test_lists)/batch_size)

# 1000은 돌려야 성능이 나온다고 함...
epoch = 150
autoencoder.fit_generator(
    generator=train_gen,
    steps_per_epoch=train_steps,
    epochs=epoch,
    validation_data=val_gen,
    validation_steps=val_steps
)

preds = autoencoder.predict_generator()

x_test = []
y_test = []
for i, (l, ab) in enumerate(generator_with_preprocessing(test_lists, batch_size)):
    x_test.append(l)
    y_test.append(ab)

x_test = np.vstack(x_test)
y_test = np.vstack(y_test)

test_preds_lab = np.concatenate((x_test, preds), axis=3).astype(np.uint8)

test_preds_rgb = []
for i in range(test_preds_lab.shape[0]):
    preds_rgb = lab2rgb(test_preds_lab[i,:,:,:])
    test_preds_rgb.append(preds_rgb)
test_preds_rgb = np.stack(test_preds_rgb) # 왜 vstack이 아님?

model.save추가하여 학습 후 다시 확인할 수 있도록 할 것
ImageOps가 아니라 opencv나 다른 방법으로 깔끔한 이미지를 출력해보자

from PIL import ImageOps
import matplotlib.pyplot as plt
for i in range(test_preds_rgb.shape[0]):
    gray_image = ImageOps.grayscale(array_to_img(test_preds_rgb[i]))
    plt.imshow(gray_image)
    plt.show()
    plt.imshow(array_to_img(test_preds_rgb[i]))
    plt.show()
    if i == 20:
        break