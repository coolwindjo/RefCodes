from tensorflow.python.keras.models import load_model
from tensorflow.python.keras import models
import matplotlib.pyplot as plt

model = load_model('data/cats_and_dogs_small_2.h5')
print(model.summary())

img_path = 'data/cats_and_dogs_small/test/cats/cat.1700.jpg'

from tensorflow.python.keras.preprocessing import image
import numpy as np

img = image.load_img(img_path, target_size=(150, 150))
img_tensor = image.img_to_array(img)
print(img_tensor.shape) # (150,150,3) = (width, height, channel)
img_tensor = np.expand_dims(img_tensor, axis=0)
print(img_tensor.shape) # (1, 150,150,3) = (batch, width, height, channel) 형태로 만듦

#정규화
img_tensor /= 255.
plt.imshow(img_tensor[0])
# plt.show()

# 8번째(0~7) 레이어까지가 convolution layer(conv+pool)
layer_outputs = [layer.output for layer in model.layers[:8]]

activation_model = models.Model(inputs=model.input, outputs=layer_outputs)
print(activation_model.summary())

# activations = output
activations = activation_model.predict(img_tensor)
# first_layer_activation = activations[0]
# plt.matshow(first_layer_activation[0, :, :, 19], cmap='viridis')
# plt.matshow(first_layer_activation[0, :, :, 15], cmap='viridis')
# plt.matshow(first_layer_activation[0, :, :, 16], cmap='viridis')
# plt.show()

# 변수 이름이 n_cols라 엄청나게 헷갈렸음
layer_names = [layer.name for layer in model.layers[:8]]
images_per_row = 16
for layer_name, layer_activation in zip(layer_names, activations):
    n_features = layer_activation.shape[-1] # kernel(feature)의 개수
    size = layer_activation.shape[1] #index2도 가능 정사각형 형태의 kernel이기 때문
    n_cols = n_features // images_per_row # 32/16, 64/16, 128/64, ...
    display_grid = np.zeros((n_cols * size, images_per_row * size)) # (row, column)
    print(display_grid.shape)

    for col in range(n_cols):
        for row in range(images_per_row):
            channel_image = layer_activation[0, :,  :, col * images_per_row + row]

            # 이미지를 보다 부드럽게 표현
            channel_image -= channel_image.mean()
            channel_image /= channel_image.std()
            channel_image *= 64
            channel_image += 128
            channel_image = np.clip(channel_image, 0, 255).astype('uint8')

            display_grid[col * size : (col + 1) * size,
                         row * size : (row + 1) * size] = channel_image

    scale = 1. / size
    plt.figure(figsize=(scale * display_grid.shape[1],
                        scale * display_grid.shape[0])) #(row, col)
    plt.title(layer_name)
    plt.imshow(display_grid, aspect='auto', cmap='viridis')
plt.show()