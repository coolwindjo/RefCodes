from tensorflow.python.keras.models import load_model
from tensorflow.python.keras import models
import matplotlib.pyplot as plt

model = load_model('data/cats_and_dogs_small_2.h5')
print(model.summary())

img_path = 'data/cats_and_dogs_small/test/cats/cat.1700.jpg'

from tensorflow.python.keras.preprocessing import image
import numpy as np

img = image.load_img(img_path, target_size=(150,150))
img_tensor = image.img_to_array(img)
print(img_tensor.shape)
img_tensor = np.expand_dims(img_tensor, axis=0)
print(img_tensor.shape)

img_tensor /= 255.
plt.imshow(img_tensor[0])
plt.show()

layer_outputs = [layer.output for layer in model.layers[:8]]

activation_model = models.Model(inputs=model.input, outputs=layer_outputs)
print(activation_model.summary())

activations = activation_model.predict(img_tensor)
first_layer_activation = activations[0]
plt.matshow(first_layer_activation[0, :, :, 19], cmap='viridis')
plt.show()

plt.matshow(first_layer_activation[0, :, :, 15], cmap='viridis')
plt.show()

layer_names = []
for layer in model.layers[:8]:
    layer_names.append(layer.name)

images_per_row = 16

for layer_name, layer_activation in zip(layer_names, activations):
    n_features = layer_activation.shape[-1]
    size = layer_activation.shape[1]
    n_cols = n_features // images_per_row
    displa_grid = np.zeros((n_cols * size , images_per_row * size))

    for col in range(n_cols):
        for row in range(images_per_row):
            channel_image = layer_activation[0, :,  :, col * images_per_row + row]
            channel_image -= channel_image.mean()
            channel_image /= channel_image.std()
            channel_image *=64
            channel_image +=128
            channel_image = np.clip(channel_image, 0, 255).astype('uint8')
            displa_grid[col * size : (col + 1) * size,
                        row * size : (row + 1) * size] = channel_image

    scale = 1. / size
    plt.figure(figsize=(scale * displa_grid.shape[1],
                        scale * displa_grid.shape[0]))
    plt.title(layer_name)
    plt.imshow(displa_grid, aspect='auto', cmap='viridis')

plt.show()