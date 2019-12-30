import tensorflow as tf

sess = tf.InteractiveSession()

s1 = tf.Variable([False]*8, name='s_data') #파일로부터 읽어올때 사이즈와 name이 같아야 함
saver = tf.train.Saver()

try:
    saver.restore(sess, './spikes.ckpt')
    print(s1.eval())
except:
    print('file not founded')
