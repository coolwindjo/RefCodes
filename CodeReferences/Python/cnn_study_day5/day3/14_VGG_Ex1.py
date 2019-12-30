from tensorflow.python.keras.applications import VGG16

# imagenet데이터를 학습한 VGG16 데이터를 다운로드 하는 코드.
# 다운로드 후 VGG16의 네트워크 구조를 출력한다.
# 다운로드 한 네트워크 모델파일을 어딨는지 모르겠따.
# 찾았다
# "C:\Users\user\.keras\models\vgg16_weights_tf_dim_ordering_tf_kernels_notop.h5"

conv_base = VGG16(weights='imagenet',
                  include_top=False,
                  input_shape=(150, 150, 3))

print(conv_base.summary())