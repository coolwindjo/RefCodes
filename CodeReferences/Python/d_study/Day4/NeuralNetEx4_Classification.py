# -*- coding: utf-8 -*-
import os
import tensorflow as tf
import numpy as np

os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'

def read_data(filename):
    """Read data from the file
    """
    data_set = np.loadtxt(filename, delimiter=",")
    return parse_data(data_set)

def parse_data(multi_x_mono_y_data):
    """Parse data from the list of item shaped as '[x1, x2, x3, y]'
    """
    x_data = np.array([x3y[:-1] for x3y in multi_x_mono_y_data])
    y_data = np.array([x3y[-1] for x3y in multi_x_mono_y_data]).reshape(len(x_data), 1)
    return x_data, y_data

class GraphManager():
    """Graph manager class
    """
    def __init__(self, learn_rate, num_inputs, num_outputs):
        self.build_graph(learn_rate, num_inputs, num_outputs)

    def __enter__(self):
        return self

    def __exit__(self, exc_type, exc_val, exc_tb):
        self.draw_graph()

    def build_graph(self, learn_rate, num_inputs, num_outputs):
        """Build graph
        """
        self.graph = tf.Graph()
        with self.graph.as_default():
            self.x_node = tf.placeholder(dtype=tf.float32, shape=[None, num_inputs], name='X')
            self.y_node = tf.placeholder(dtype=tf.float32, shape=[None, num_outputs], name='Y')

            # Weight, bias initialization
            tf.set_random_seed(777)
            """
            with tf.name_scope('hidden_layers'):
                weight1 = tf.Variable(tf.random_normal([num_inputs, 30],
                                                        seed=0, dtype=tf.float32), name='weight1')
                #bias1 = tf.Variable(tf.random_normal([30], seed=0, dtype=tf.float32), name='b1')
                bias1 = tf.Variable(tf.zeros([30]), name='bias1')
                with tf.name_scope('layer1_activation'):
                    #hypothesis1 = tf.sigmoid(tf.add(tf.matmul(self.x_node, weight1), bias1))
                    hypothesis1 = tf.add(tf.matmul(self.x_node, weight1), bias1)
                    y_h = tf.nn.relu(hypothesis1)

                weight2 = tf.Variable(tf.random_normal([30, 10], seed=0, dtype=tf.float32), name='W2')
                bias2 = tf.Variable(tf.random_normal([10], seed=0, dtype=tf.float32), name='b2')
                with tf.name_scope('layer2_activation'):
                    hypothesis2 = tf.sigmoid(tf.add(tf.matmul(hypothesis1, weight2), bias2))
            """
            self.weight = tf.Variable(tf.random_normal([num_inputs, num_outputs],
                                                       seed=0, dtype=tf.float32), name='weight')
            #self.bias = tf.Variable(tf.random_normal([1], seed=0, dtype=tf.float32), name='b')
            self.bias = tf.Variable(tf.random_normal([num_outputs]), name='bias')
            with tf.name_scope('output_layer_activation'):
                model = tf.add(tf.matmul(self.x_node, self.weight), self.bias)
                self.hypothesis = tf.nn.softmax(model)

            with tf.name_scope('loss_calculation'):
                #cross_entropy = tf.nn.sigmoid_cross_entropy_with_logits(labels=self.y_node,
                 #                                                       logits=model)
                cross_entropy = -tf.reduce_sum(self.y_node * tf.log(self.hypothesis), axis=1)
                self.loss = tf.reduce_mean(cross_entropy)

            with tf.name_scope('train'):
                optimizer = tf.train.GradientDescentOptimizer(learning_rate=learn_rate)
                #optimizer = tf.train.AdamOptimizer(learn_rate)
                self.train = optimizer.minimize(self.loss)

            with tf.name_scope('evaluate'):
                self.predicted = tf.cast(self.hypothesis > 0.5, dtype=tf.float32)
                self.accuracy = tf.reduce_mean(tf.cast(tf.equal(self.predicted, self.y_node),
                                                        dtype=tf.float32))

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
                if step % 200 == 0:
                    print("Epoch:{} Cost={:.04f}\nWeight=\n{}\nBias={:.4f}"\
                          .format(step, _loss, _weight, _bias[0]))
            cost, accuracy = self.sess.run([self.predicted, self.accuracy],
                                           feed_dict={self.x_node:x_data, self.y_node:y_data})
            print("\n Correct:{}\n{}, \nAccuracy: {}".format(cost.shape, cost[:10], accuracy))

    def test_with_model(self, test_x, gt_y = 0):
        """Test with trained model
        """
        print("\n############ Test start! ###########")
        with self.graph.as_default():
            test_y = self.sess.run(self.hypothesis, feed_dict={self.x_node:test_x})
            if gt_y == 0:
                max_test_y = self.sess.run(tf.argmax(test_y, axis=1))
                print("TestSet: {} \nResult:\n{} \nMax value index: {}"\
                      .format(test_x, test_y, max_test_y))
            else:
                print("TestSet: {} \nResult:\n{} \nGround truth: {}"\
                      .format(test_x, test_y, gt_y))

    def draw_graph(self):
        """Draw graph
        """
        tf.summary.FileWriter('./graph_logs',graph=self.graph)
        self.sess.close()


def main():
    """Main function
    """
    x_data = [[1, 2, 1, 1],
              [2, 1, 3, 2],
              [3, 1, 3, 4],
              [4, 1, 5, 5],
              [1, 7, 5, 5],
              [1, 2, 5, 6],
              [1, 6, 6, 6],
              [1, 7, 7, 7]]
    y_data = [[0, 0, 1],
              [0, 0, 1],
              [0, 0, 1],
              [0, 1, 0],
              [0, 1, 0],
              [0, 1, 0],
              [1, 0, 0],
              [1, 0, 0]]

    # Test preparation
    """gt_w = np.array([[0.3], [0.5], [0.1]])
    gt_b = -0.2
    test_x = np.array([0.1, 0.2, 0.3]).reshape(1, 3)
    gt_y = np.matmul(test_x, gt_w) + gt_b
    """
    test_x = [[1, 11, 7, 9]]
    test_x2 = [[1, 11, 7, 9], [1, 3, 4, 3], [1, 1, 0, 1]]
    # Training data preparation
    """np.random.seed(1234)
    x3_data = np.random.randn(2000, 3)
    x3y_data = np.array([[x_datum[0], x_datum[1], x_datum[2], (np.matmul(x_datum, gt_w) + gt_b)[0]]\
                         for x_datum in x3_data])
    """
    learn_rate = 0.1
    num_epochs = 2001
    with GraphManager(learn_rate, len(x_data[0]), len(y_data[0])) as grp_man:
        grp_man.train_data(num_epochs, x_data, y_data)
        grp_man.test_with_model(test_x)
        grp_man.test_with_model(test_x2)

if __name__ == '__main__':
    main()
