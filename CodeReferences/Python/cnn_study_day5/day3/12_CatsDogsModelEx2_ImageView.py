from tensorflow.python.keras.preprocessing.image import ImageDataGenerator
import matplotlib.pyplot as plt
import os

# 이전예제와 달리 ImageDataGenerator를 적극적으로 활용한다.
# 돌리고 뒤집고, 밀고 난리났다.
# 이렇게 지지고 볶은 이미지를 plt로 그려보는 예제
# 영상 영역이 없는 부분이 근처의 값을 그대로 재생하도록 하는 nearest를 사용하여 기괴하다..

base_dir = './data/cats_and_dogs_small'
train_dir = os.path.join(base_dir, 'train')

datagen = ImageDataGenerator(
    rotation_range=40,
    width_shift_range=0.2,
    height_shift_range=0.2,
    shear_range=0.2,
    horizontal_flip=True,
    fill_mode='nearest',
)

from tensorflow.python.keras.preprocessing import image
train_cats_dir = os.path.join(train_dir, 'cats')
fnames = sorted([os.path.join(train_cats_dir, fname) for fname in os.listdir(train_cats_dir)])
img_path = fnames[3] #임의로 이미지 선택

img = image.load_img(img_path, target_size=(150, 150))
x = image.img_to_array(img)
x = x.reshape((1,) + x.shape) #차원 확장?

i = 0
for batch in datagen.flow(x, batch_size=1):
    plt.figure(i)
    plt.imshow(image.array_to_img(batch[0]))
    i += 1
    if i % 20 == 0:
        break
plt.show()
