# -*- coding: utf-8 -*-

import tensorflow as tf

my_var = tf.Variable(1)
my_var_times_two = my_var.assign(my_var * 2)

init = tf.global_variables_initializer()

sess = tf.Session()
sess.run(init)

print("\nmy_var_times_two:", sess.run(my_var_times_two))
print("\nmy_var_times_two:", sess.run(my_var_times_two))
print("\nmy_var_times_two:", sess.run(my_var_times_two))