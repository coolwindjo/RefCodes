import tensorflow as tf

sess = tf.InteractiveSession()

raw_data = [1,2,8,-1,0,5,6,13]
spikes = tf.Variable([False]*8, name='s_data')

spikes.initializer.run()

# Node안의 데이터를 하나만 찝어서 변경할 수 없다
# 통째로 바꾸어야 함.
for i in range(1, 8):
    if raw_data[i] - raw_data[i - 1] > 5:
        spikes_val = spikes.eval()
        spikes_val[i] = True
        update = tf.assign(spikes, spikes_val)
        update.eval()

saver = tf.train.Saver()
save_path = saver.save(sess, './spikes.ckpt')
print(save_path)