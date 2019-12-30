import tensorflow as tf

# tf에서는 variable 노드를 바꾸기 위해서는 바꿔주는 별도의 노드(assign)가 필요하다
# 어째서 이렇게 복잡한 구조를 취하게 되었을까?
# 모든 것을 노드형태로 만들어 graph를 만드려고 하면 이렇게 되는 듯?

m_var = tf.Variable(1, dtype=tf.int32)
m_var_times_two = tf.assign(m_var, m_var * 2)
init = tf.global_variables_initializer()

sess = tf.Session()

sess.run(init)
print(sess.run(m_var))

sess.run(m_var_times_two)
print(sess.run(m_var))

sess.run(m_var_times_two)
print(sess.run(m_var))

sess.run(init)
print(sess.run(m_var))