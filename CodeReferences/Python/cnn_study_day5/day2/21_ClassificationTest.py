import tensorflow as tf
import numpy as np

import pandas as pd

# 입력되는 데이터에 header row가 존재. 또한 마지막 column이 숫자가 아니라 문자열.
# 첫번째 column이 Id column으로 학습에 아무런 상관이 없음
# 데이터를 전처리하는 과정이 필요함.
# np.loadtxt에 lambda 함수를 사용하여 해결하였음.
# lambda 함수를 사용해 5번째 column을 조건에 따라 숫자로 입력받음
# skiprow를 통해 header row를 제거하였음
# 생성된 데이터를 numpy의 slice기능을 통해 필요한 부분만 잘라서 사용함.

tf.set_random_seed(777)

#기존 13번 파일과 입력데이터만 변경
#전처리 방식 변경 : np.loadtxt로 읽히지 않음
#입력 노드 개수와 output class의 개수가 변경됨

#아래는 다른 사람의 모범 답안
'''
data=np.loadtxt('data/Iris2.csv',delimiter=',',skiprows=1, usecols = (1,2,3,4),dtype=np.float32)
x_data = data[:]
data2=np.loadtxt('data/Iris2.csv',delimiter=',',skiprows=1, usecols = (5),dtype=np.str)
y_data = data2[:]
new_y=[]
for y_tmp in y_data:
    if(y_tmp=='Iris-setosa'):
        new_y.append([0])
    elif(y_tmp=='Iris-versicolor'):
        new_y.append([1])
    elif(y_tmp=='Iris-virginica'):
        new_y.append([2])
'''
####################################
# 가장 처음에 시도한 방법. 가장 기초적인 문법을 사용하여 해결하였음.
# raw_data_lines = []
# with open('data/Iris2.csv', 'r') as f:
#     while True:
#         line = f.readline()
#         if not line: break
#
#         splited_line = line.split(',')
#         if splited_line[-1].rstrip() == 'Iris-setosa':
#             splited_line[-1] = '0'
#         elif splited_line[-1].rstrip() == 'Iris-versicolor':
#             splited_line[-1] = '1'
#         elif splited_line[-1].rstrip() == 'Iris-virginica':
#             splited_line[-1] = '2'
#
#         raw_data_lines.append(splited_line)
# data = np.array(raw_data_lines)
####################################

# 강사 버전
# from sklearn.preprocessing import LabelEncoder
# iris_data = pd.read_csv('data/Iris2.csv')
# data_set = iris_data.values
# x_data = data_set[:, 1:5]
# y_data = data_set[:, 5]
#
# e = LabelEncoder()
# e.fit(y_data) #sklearn에서 제공하는 api. 특수한 문자열을 추출하여 숫자로 encoding
# y_data = e.transform(y_data)
# print(y_data)
# y_data = np.expand_dims(y_data, axis=1)
# print(y_data)
####################################

# 응용 버전
def SpeciesToNum(str):
    str = str.decode('ascii')
    if str == 'Iris-setosa':
        return 0
    elif str == 'Iris-versicolor':
        return 1
    elif str == 'Iris-virginica':
        return 2

data=np.loadtxt('data/Iris2.csv', delimiter=',',skiprows=1, converters={5: lambda x :SpeciesToNum(x)})
##################################

x_data = data[1:, 1:-1] #모든 행에서 추출, 첫컬럽부터 마지막컬럽전까지
y_data = data[1:, [-1]]

x = tf.placeholder(dtype=tf.float32, shape=[None, 4]) # -> (?, 4)
y = tf.placeholder(dtype=tf.int32, shape=[None, 1])  # -> (?, 1)

# tensorflow의 one_hot api를 이용하는 방법
y_one_hot = tf.one_hot(y, 3)
print(y_one_hot.get_shape()) # -> (?, 1, 7)
# :RNN에서 one-hot을 주로 사용, RNN에서 batch x seq x input
# tensorflow가 RNN에서 하던것처럼 해서 (?, 1, 7)이 됨... '변형 필요

# tf reshape에서 -1은 None을 뜻함
y_one_hot = tf.reshape(y_one_hot, [-1, 3])
print(y_one_hot.get_shape()) # -> (?, 7)


w = tf.Variable(tf.random_normal([4, 3]), name='weight')
b = tf.Variable(tf.random_normal([3]), name='bias')

# weighted sum
logit = tf.matmul(x, w) + b
hypothesis = tf.nn.softmax(logit)

# 기존의 수식 : 32, 33줄을 대체하는 코드, tensorflow에서 제공하는 것이 더 효율적인 코드
#cost = tf.reduce_mean(-tf.reduce_sum(y * tf.log(hypothesis), axis=1))

cost_i = tf.nn.softmax_cross_entropy_with_logits_v2(logits=logit, labels=y_one_hot)
cost = tf.reduce_mean(cost_i)
train = tf.train.GradientDescentOptimizer(learning_rate=0.1).minimize(cost)

prediction = tf.argmax(hypothesis, axis=1)
accuracy = tf.reduce_mean(tf.cast(tf.equal(prediction, tf.argmax(y_one_hot, axis=1)), tf.float32))

with tf.Session() as sess:
    sess.run(tf.global_variables_initializer())
    for step in range(3001):
        _cost,_acc, _ = sess.run([cost, accuracy, train], feed_dict={x: x_data, y: y_data})
        if step % 200 == 0:
            print('step:{} accuracy:{}, cost:{}'.format(step, _acc, _cost))

    a = sess.run(hypothesis, feed_dict={x:[[1,11,7,9]]})
    print('a:{}',format(a))
    print(sess.run(tf.argmax(a, axis=1)))

    pred = sess.run(prediction, feed_dict={x:x_data})
    for p, y in zip(pred, y_data):
        print('prediction:{}, correct:{}'.format(p, y))

