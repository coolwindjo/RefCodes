import tensorflow as tf

class Ex1:
    def __init__(self):
        # self.step_counter = 1
        self.g = tf.Graph()
        self.sess = tf.InteractiveSession(graph=self.g)
        with self.g.as_default():
            with tf.name_scope('exercise_transformation'):
                with tf.name_scope('input'):
                    self.input_node = tf.placeholder(dtype=tf.float32, shape=[None], name='input_node')

                with tf.name_scope('imtermediate_layer'):
                    self.input_sum = tf.reduce_sum(self.input_node, name='input_sum')
                    self.input_mul = tf.reduce_prod(self.input_node, name='input_mul')

                with tf.name_scope('output'):
                    self.sum = tf.add(self.input_sum, self.input_mul)

            with tf.name_scope('variables'):
                self.global_step = tf.Variable(0.0, dtype=tf.float32)
                # self.global_step_assign = tf.assign(self.global_step, self.global_step + self.previous_value_assign)
                self.global_step_assign = tf.assign(self.global_step, self.sum)

                self.previous_value = tf.Variable(0.0, dtype=tf.float32)
                self.previous_value_assign = tf.assign(self.previous_value, self.global_step_assign + self.previous_value)

                self.step_counter = tf.Variable(0, dtype=tf.int32)
                self.step_counter_plus = tf.assign(self.step_counter, self.step_counter + 1)

            with tf.name_scope('global_ops'):
                self.init = tf.global_variables_initializer()

        self.sess.run(self.init)

    def test(self, input_data):
        self.sess.run(self.previous_value_assign, feed_dict={self.input_node: input_data})
        self.sess.run(self.step_counter_plus)
        print('step:{}, result:{}, total_result:{}'.format(self.step_counter.eval(), self.global_step.eval(), self.previous_value.eval()))
        # self.step_counter += 1
        tf.summary.FileWriter('./m_graph', graph=self.g)

if __name__ == "__main__":
    ex = Ex1()
    ex.test([2, 8])
    ex.test([3, 1, 3, 3])
    ex.test([8])
    ex.test([2, 3, 7])

## global_variables_initializer이 가장 마지막에 있어야 
## node들을 초기화 할 수 있음