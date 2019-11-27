# -*- coding: utf-8 -*-

import tensorflow as tf
import os

os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'
sess = tf.InteractiveSession()

raw_data = [1., 2., 8., -1., 0., 5.5, 6.]
spikes = tf.Variable([False]*len(raw_data), name='spike')
spikes.initializer.run()

saver = tf.train.Saver()
spike_val = spikes.eval()
for i in range(1, len(raw_data)):
    if raw_data[i] - raw_data[i-1] > 5:
        spike_val[i] = True
        
updater = tf.assign(spikes, spike_val)
print(updater.eval())

save_path = saver.save(sess, './Day2/my_ckpt/spikes.ckpt')
print("spikes data saved in file:", save_path)
sess.close()
