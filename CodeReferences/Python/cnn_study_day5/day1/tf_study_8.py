import tensorflow as tf

# 개별적으로 초기화를 할 수 있도록 별도의 session을 제공
tf.InteractiveSession()

raw_data = [1,2,8,-1,0,5,6,13]
spike = tf.Variable(False, dtype=tf.bool)
spike.initializer.run()

for i in range(1, 8):
    if raw_data[i] - raw_data[i-1] > 5:
        update = tf.assign(spike, True)
        update.eval()
    else:
        tf.assign(spike, False).eval()
    print(raw_data[i], raw_data[i-1], raw_data[i] - raw_data[i-1], ', ', end='')
    print('spike : ', spike.eval())