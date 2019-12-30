import tensorflow as tf
tf.set_random_seed(777)

#7번 문제보다 좀 더 generic한 형태
#변수가 여러개, 즉 x의 종류가 많아서 w의 개수가 많아지더라도
#행렬형태로 hypothesis를 구하므로 굉장히 일반적인 형태

#일반적인 형태로 만들기 위해 y_data의 형태도 행렬로 바뀌었다. 
x_data = [[1,2],[2,3],[3,1],[4,3],[5,3],[6,2]]
y_data = [[0],[0],[0],[1],[1],[1]]

# n개의 변수를 입력받기 위한 일반적인 형태
x = tf.placeholder(tf.float32, shape=[None, 2])
y = tf.placeholder(tf.float32, shape=[None, 1])

W = tf.Variable(tf.random_normal([2, 1]), name='weight')
b = tf.Variable(tf.random_normal([1]), name='bias')

# W*x가 아니라 x*w인 이유 -> x가 [None, 2]의 형태. 행렬로 따지면 (N x 2)
# 우리가 필요한 W는 x의 개수는 N과 일치 -> W = (N x 1)의 형태가 필요함
# (N x 2) * M = (N x 1)이 되려면
# M=(2 x 1)이 되어야 함 그래서 16번째줄에 W를 선언한 tensor가 (2, 1)인 이유
# 더욱 더 generic한 형태로 만들기 위해서는 16번째줄을 아래와 같이 바꿀 필요가 있다.
# x = tf.placeholder(tf.float32, shape=[len(x_data[0]), 2])
hypothesis = tf.sigmoid(tf.matmul(x, W) + b)
cost = -tf.reduce_mean(y * tf.log(hypothesis) + (1 - y) *
                       tf.log(1 - hypothesis))

train = tf.train.GradientDescentOptimizer(learning_rate=0.01).minimize(cost)

predicted = tf.cast(hypothesis > 0.5, dtype=tf.float32)
accuracy = tf.reduce_mean(tf.cast(tf.equal(predicted, y), dtype=tf.float32))

with tf.Session() as sess:
    sess.run(tf.global_variables_initializer())
    for step in range(10001):
        _cost, _ = sess.run([cost, train], feed_dict={x: x_data, y: y_data})
        if step % 200 == 0:
            print('step:{} cost:{}'.format(step, _cost))

    h, c, a = sess.run([hypothesis, predicted, accuracy],
                       feed_dict={x: x_data, y: y_data})
    print("\nHypothesis: ", h, "\nCorrect (Y): ", c, "\nAccuracy: ", a)