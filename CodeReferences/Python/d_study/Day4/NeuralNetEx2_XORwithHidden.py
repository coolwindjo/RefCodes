# -*- coding: utf-8 -*-
import os
import tensorflow as tf
import numpy as np

os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'

def parse_data(x3y_data):
    """Parse data from the list of item shaped as '[x1, x2, x3, y]'
    """
    x_data = np.array([x3y[:-1] for x3y in x3y_data])
    y_data = np.array([x3y[-1] for x3y in x3y_data]).reshape(len(x_data), 1)
    return x_data, y_data

class GraphManager():
    """Graph manager class
    """
    def __init__(self, learn_rate):
        self.build_graph(learn_rate)

    def __enter__(self):
        return self

    def __exit__(self, exc_type, exc_val, exc_tb):
        self.draw_graph()

    def build_graph(self, learn_rate):
        """Build graph
        """
        self.graph = tf.Graph()
        with self.graph.as_default():
            self.x_node = tf.placeholder(dtype=tf.float32, shape=[None, 2], name='X')
            self.y_node = tf.placeholder(dtype=tf.float32, shape=[None, 1], name='Y')

            # Weight, bias initialization
            tf.set_random_seed(777)
            with tf.name_scope('hidden_layers'):
                weight1 = tf.Variable(tf.random_normal([2, 10], seed=0, dtype=tf.float32), name='W1')
                bias1 = tf.Variable(tf.random_normal([10], seed=0, dtype=tf.float32), name='b1')
                with tf.name_scope('layer1_activation'):
                    hypothesis1 = tf.sigmoid(tf.add(tf.matmul(self.x_node, weight1), bias1))

                weight2 = tf.Variable(tf.random_normal([10, 10], seed=0, dtype=tf.float32), name='W2')
                bias2 = tf.Variable(tf.random_normal([10], seed=0, dtype=tf.float32), name='b2')
                with tf.name_scope('layer2_activation'):
                    hypothesis2 = tf.sigmoid(tf.add(tf.matmul(hypothesis1, weight2), bias2))

            self.weight = tf.Variable(tf.random_normal([10, 1], seed=0, dtype=tf.float32), name='W')
            self.bias = tf.Variable(tf.random_normal([1], seed=0, dtype=tf.float32), name='b')
            with tf.name_scope('output_layer_activation'):
                self.y_o = tf.sigmoid(tf.add(tf.matmul(hypothesis2, self.weight), self.bias))

            with tf.name_scope('error_calculation'):
                #self.loss = -tf.reduce_mean(tf.square(self.y_o - self.y_node))
                self.loss = -tf.reduce_mean(self.y_node * tf.log(self.y_o)
                                            + (1 - self.y_node) * tf.log(1-self.y_o))

            with tf.name_scope('train'):
                optimizer = tf.train.GradientDescentOptimizer(learning_rate=learn_rate)
                self.train = optimizer.minimize(self.loss)

            with tf.name_scope('evaluate'):
                self.predicted = tf.cast(self.y_o > 0.5, dtype=tf.float32)
                self.accuracy = tf.reduce_mean(tf.cast(tf.equal(self.predicted, self.y_node), dtype=tf.float32))

            self.init = tf.global_variables_initializer()
            self.sess = tf.Session()


    def train_data(self, num_epochs, x_data, y_data):
        """Train model with given data
        """
        with self.graph.as_default():
            self.sess.run(self.init)
            for step in range(num_epochs):
                [_loss, _weight, _bias, _]\
                 = self.sess.run([self.loss, self.weight, self.bias, self.train],
                                 feed_dict={self.x_node:x_data, self.y_node:y_data})
                if step % 100 == 0:
                    print("Epoch:{} Cost={:.04f} Weight=[{:.4f}, {:.4f}] Bias={:.4f}"\
                          .format(step, _loss,
                                  _weight[0, 0], _weight[1, 0], _bias[0]))
            h, c, a = self.sess.run([self.y_o, self.predicted, self.accuracy], feed_dict={self.x_node:x_data, self.y_node:y_data})
            print("\n Hypothesis: {}, \nCorrect: {}, \nAccuracy: {}".format(h, c, a))

    def test_with_model(self, test_x, gt_y):
        """Test with trained model
        """
        with self.graph.as_default():
            test_y =self.sess.run(self.y_o, feed_dict={self.x_node:test_x})
            print("TestSet: {} \nResult: {} \nGround truth: {}"\
                  .format(test_x, test_y, gt_y))

    def draw_graph(self):
        """Draw graph
        """
        tf.summary.FileWriter('./graph_logs',graph=self.graph)
        self.sess.close()


def main():
    """Main function
    """
    x_raw_data = [[0, 0], [1, 0], [0, 1], [1, 1]]
    y_raw_data = [[0],
                  [1],
                  [1],
                  [0]]

    # Test preparation
    """gt_w = np.array([[0.3], [0.5], [0.1]])
    gt_b = -0.2
    test_x = np.array([0.1, 0.2, 0.3]).reshape(1, 3)
    gt_y = np.matmul(test_x, gt_w) + gt_b
    """
    test_x = np.array(x_raw_data, dtype=np.float32)
    gt_y = np.array(y_raw_data, dtype=np.float32)
    # Training data preparation
    """np.random.seed(1234)
    x3_data = np.random.randn(2000, 3)
    x3y_data = np.array([[x_datum[0], x_datum[1], x_datum[2], (np.matmul(x_datum, gt_w) + gt_b)[0]]\
                         for x_datum in x3_data])
    x_data, y_data = parse_data(x3y_data)
    """
    x_data = np.array(x_raw_data, dtype=np.float32)
    y_data = np.array(y_raw_data, dtype=np.float32)

    learn_rate = 0.1
    num_epochs = 10001
    with GraphManager(learn_rate) as grp_man:
        grp_man.train_data(num_epochs, x_data, y_data)
        grp_man.test_with_model(test_x, gt_y)

if __name__ == '__main__':
    main()
