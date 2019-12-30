import tensorflow as tf
import numpy as np

# logstic regression의 가장 간단한 예제
# cost 함수가 어떻게 생성되는지 적기 어려우니 링크를 참조 또는 교육 때 받은 교재 참조
# 두 링크 모두 cousera의 andrew ag 교수의 강의를 참조한 것으로 보임
# http://gnujoow.github.io/ml/2016/01/29/ML3-Logistic-Regression/
# https://daeson.tistory.com/180

x_data = [2,4,6,8,10,12,14]
y_data = [0,0,0,1,1,1,1]

w = tf.Variable(tf.random_normal([1], dtype=tf.float64, seed=0))
b = tf.Variable(tf.random_normal([1], dtype=tf.float64, seed=0))

hypothesis = 1 / (1 + np.e**(w*x_data+b)) #sigmoid 함수
#binary costentrpy라고 부름
cost_vector = -(np.array(y_data) * tf.log(hypothesis) + (1-np.array(y_data)) * tf.log(1-hypothesis))
cost = tf.reduce_mean(cost_vector)

learning_rate = 0.5
train = tf.train.GradientDescentOptimizer(learning_rate).minimize(cost)

with tf.Session() as sess:
    sess.run(tf.global_variables_initializer())
    for step in range(60001):
        _cost, _w, _b, _ = sess.run([cost, w, b, train])
        if step % 6000 == 0:
            print('step:{} cost:{} w:{} b:{}'.format(step, _cost, _w, _b))
