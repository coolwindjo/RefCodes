import tensorflow as tf

# 04 파일의 강사버전
# tf.random_uniform을 사용하였고, weight의 최대 최소값이 명시되어 있다
# 또한 float32가 아니라 float64를 사용
# float32를 사용하면 오류가 난다. 간단해보이는 숫자지만 학습하기 어려워서 그런듯

data = [[2, 81], [4, 93], [6, 91], [8, 97]]
x_data = [x_row[0] for x_row in data]
y_data = [y_row[1] for y_row in data]

w = tf.Variable(tf.random_uniform([1], 0, 10, dtype = tf.float64, seed = 0))
b = tf.Variable(tf.random_uniform([1], 0, 100, dtype = tf.float64, seed = 0))

x = tf.placeholder(dtype=tf.float64)
y = tf.placeholder(dtype=tf.float64)

hypothesis = w * x + b
cost = tf.reduce_mean(tf.square( hypothesis - y ))

learning_rate = 0.01
gradient_decent = tf.train.GradientDescentOptimizer(learning_rate).minimize(cost)

with tf.Session() as sess:
    tf.summary.FileWriter('../logs', sess.graph)
    sess.run(tf.global_variables_initializer())

    for step in range(2001):
        _cost, _w, _b, _ = sess.run([cost, w, b, gradient_decent], feed_dict={x:x_data, y:y_data})
        if step % 100 == 0:
            print("step: %.f, cost = %.04f, 기울기 a = %.4f, y 절편 b = %.4f" %(step, _cost, _w, _b))

