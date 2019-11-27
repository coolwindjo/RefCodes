
import tensorflow as tf
import numpy as np
Data_set = np.loadtxt("../dataset/ThoraricSurgery.csv", delimiter=",")

# 환자의 기록과 수술 결과를 X와 Y로 구분하여 저장합니다.
x_data = Data_set[:, 0:17]
y_data = Data_set[:, 17]

X = tf.placeholder(tf.float32)
Y = tf.placeholder(tf.float32)

# 첫번째 가중치의 차원은 [특성, 히든 레이어의 뉴런갯수] -> [17, 30] 으로 정합니다.
W1 = tf.Variable(tf.random_uniform([17, 30], -1., 1.))
# 두번째 가중치의 차원을 [첫번째 히든 레이어의 뉴런 갯수, 분류 갯수] -> [30, 1] 으로 정합니다.
W2 = tf.Variable(tf.random_uniform([30, 1], -1., 1.))

# 편향을 각각 각 레이어의 아웃풋 갯수로 설정합니다.
# b1 은 히든 레이어의 뉴런 갯수로, b2 는 최종 결과값 즉, 아웃풋 갯수인 3으로 설정합니다.
b1 = tf.Variable(tf.zeros([30]))
b2 = tf.Variable(tf.zeros([1]))

# 신경망의 히든 레이어에 가중치 W1과 편향 b1을 적용합니다
L1 = tf.add(tf.matmul(X, W1), b1)
L1 = tf.nn.relu(L1)

# 최종적인 아웃풋을 계산합니다.
# 히든레이어에 두번째 가중치 W2와 편향 b2를 적용하여 3개의 출력값을 만들어냅니다.
model = tf.add(tf.matmul(L1, W2),b2)

# 텐서플로우에서 기본적으로 제공되는 크로스 엔트로피 함수를 이용해
# 복잡한 수식을 사용하지 않고도 최적화를 위한 비용 함수를 다음처럼 간단하게 적용할 수 있습니다.

cross_entropy = tf.nn.sigmoid_cross_entropy_with_logits(labels=Y, logits=model)
cost = tf.reduce_mean(cross_entropy)
optimizer = tf.train.AdamOptimizer(learning_rate=0.01)
train_op = optimizer.minimize(cost)


#########
# 신경망 모델 학습
######
init = tf.global_variables_initializer()
sess = tf.Session()
sess.run(init)

predicted = tf.cast(model > 0.5, dtype=tf.float32)
accuracy = tf.reduce_mean(tf.cast(tf.equal(predicted,y_data), dtype=tf.float32))
for step in range(500):
    accuracyv,costv, _ = sess.run([accuracy,cost,train_op], feed_dict={X: x_data, Y: y_data})

    if (step + 1) % 100 == 0:
        print('cost:{0}  accuracy:{1}'.format(costv, accuracyv) )
print('accuracy:',accuracyv)


