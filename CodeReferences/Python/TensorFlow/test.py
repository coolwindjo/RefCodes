import tensorflow as tf
import numpy as np

x = tf.constant(np.arange(1,5).reshape((1,2,2,1)), dtype=tf.float32)
f = tf.constant(np.ones(9).reshape((3,3,1,1)),dtype=tf.float32)

'''
Same = in_w * in_h
Valid = (in_w -1) x stride + f_w
'''

conv = tf.nn.conv2d_transpose(x,f, output_shape=(1,4,4,1), strides=[1,2,2,1], padding='SAME')
print("conv size : ", conv.shape)
print(tf.squeeze(conv).numpy())