from tensorflow.python.keras.models import load_model
from tensorflow.python.keras import models
import matplotlib.pyplot as plt
from tensorflow.python.keras.datasets import cifar10
from tensorflow.python.keras.utils import np_utils
import numpy as np

from tensorflow.python.keras.preprocessing import image


dnn_model = load_model('data/cifar10_dense.h5')
# cnn_model = load_model('data/cifar10_cnn.h5')

labels = ["airplane", "automobile", "bird", "cat", "deer",
          "dog", "frog", "horse", "ship", "truck"]


(x_train, y_train), (x_test, y_test) = cifar10.load_data()
x_train = x_train.astype('float32') / 255
y_train = np_utils.to_categorical(y_train)
x_test = x_test.astype('float32') / 255
y_test = np_utils.to_categorical(y_test)

# for only dense
x_test_dnn = x_test.reshape(x_test.shape[0], 32*32*3)


test_sample = image.load_img('images/test-car.jpg', target_size=(32, 32))
test_sample = image.img_to_array(test_sample)
# print(img_tensor.shape) # (150,150,3) = (width, height, channel)
test_sample = np.expand_dims(test_sample, axis=0)
print(test_sample.shape) # (1, 150,150,3) = (batch

test_sample_dnn = test_sample.reshape(test_sample.shape[0], 32*32*3)

# activation_model = models.Model(inputs=dnn_model.input, outputs=layer_outputs)

print(x_test_dnn[0].shape)
print(x_test_dnn[0:1].shape)
# result = dnn_model.predict_classes(x_test_dnn[0:1])
result = dnn_model.predict_classes(test_sample_dnn)
# result_cnn = cnn_model.predict_classes(x_test[0:1])
# print("DNN answer:{}, correct_answer:{}".format(labels[result[0]], labels[np.argmax(y_test[0])]))
# print("CNN answer:{}, correct_answer:{}".format(labels[result_cnn[0]], labels[np.argmax(y_test[0])]))
print("DNN answer:{}, correct_answer:{}".format(labels_dict[result[0]], labels_dict[np.argmax(y_test[0])]))