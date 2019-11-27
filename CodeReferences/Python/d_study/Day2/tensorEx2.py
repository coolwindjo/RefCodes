t_0 = 50 #scalar

t_1 = ['apple', 'peach', 'graph'] #vector

t_2 = [[True, False, False],
       [True, False, False],
       [True, False, False]]    #matrix

t_3 = [[[0, 0], [1, 1], [2, 2]],
       [[4, 4], [5, 5], [6, 6]]]    #3-D tensor

import numpy as np
import tensorflow as tf

a = np.array([2, 3], dtype=np.int32)
b = np.array([4, 5], dtype=np.int32)
c = tf.add(a, b, name='add_op')
sess = tf.Session()
print("\nc:", sess.run(c))