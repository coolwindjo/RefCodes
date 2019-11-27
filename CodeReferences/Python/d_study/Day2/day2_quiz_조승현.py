# -*- coding: utf-8 -*-
import tensorflow as tf
import os

os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'

class GraphManager():
    def __init__(self):
        self.build_graph()

    def __enter__(self):
        self.init_vars()
        return self

    def __exit__(self, exc_type, exc_val, exc_tb):
        self.draw_graph()

    def build_graph(self):
        self.graph = tf.Graph()
        with self.graph.as_default():
            with tf.name_scope('variables'):
                with tf.name_scope('input'):
                    self.input_out = tf.placeholder(dtype=tf.float32, name='input_node')

                with tf.name_scope('imtermediate_layer'):
                    add_out = tf.reduce_sum(self.input_out, name='sum_inputs')
                    mul_out = tf.reduce_prod(self.input_out, name='prod_inputs')

                with tf.name_scope('output'):
                    self.out = tf.add(add_out, mul_out)

    def init_vars(self):
        self.var_graph = tf.Graph()
        with self.var_graph.as_default():
            self.g_steps = tf.Variable(0, dtype=tf.int32, name='g_steps')
            self.sum_outs = tf.Variable(0.0, name='sum_outs')
            with tf.name_scope('global_ops'):
                init = tf.global_variables_initializer()
            with tf.name_scope('update'):
                self.incr_g_steps = tf.assign_add(self.g_steps, 1, name='increment_steps')
                self.average = tf.div_no_nan(self.sum_outs, tf.cast(self.g_steps, tf.float32), name='average')
            self.sess = tf.Session()
            self.sess.run(init)

    def run_graph(self, input_data):
        with self.graph.as_default():
            with tf.Session() as sess:
                _result = sess.run(self.out, feed_dict={self.input_out:input_data})
        with self.var_graph.as_default():
            self.sess.run(tf.assign_add(self.sum_outs, _result, name='update_sum'))
            _g_steps = self.sess.run(self.incr_g_steps)
            _avg = self.sess.run(self.average)
            print("step:{}, result:{}, average:{}".format(_g_steps, _result, _avg))

    def draw_graph(self):
        tf.summary.FileWriter('./graph_logs',graph=self.graph)
        self.sess.close()


def main():
    with GraphManager() as grp_man:
        grp_man.run_graph([2, 8])
        grp_man.run_graph([3, 1,3, 3])
        grp_man.run_graph([8])
        grp_man.run_graph([1, 2, 3])
        grp_man.run_graph([11, 4])
        grp_man.run_graph([4, 1])
        grp_man.run_graph([7, 3, 1])
        grp_man.run_graph([6, 3])

if __name__ == '__main__':
    main()