# -*- coding: utf-8 -*-
import os
import tensorflow as tf
import random
import matplotlib.pyplot as plt
from tensorflow.examples.tutorials.mnist import input_data
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'

mnist = input_data.read_data_sets('MNIST/', one_hot=True)
patch_size = 28

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
        num_hidden_nodes = 512

        self.graph = tf.Graph()
        with self.graph.as_default():
            self.x_node = tf.placeholder(dtype=tf.float32, shape=[None, num_inputs], name='X')
            self.x_img = tf.reshape(self.x_node, [-1, patch_size, patch_size, 1]) # img 28x28x1 (b/w)
            self.y_node = tf.placeholder(dtype=tf.int32, shape=[None, num_outputs], name='Y')
            self.keep_prob = tf.placeholder(dtype=tf.float32)

            # Weight, bias initialization
            tf.set_random_seed(777)
            with tf.name_scope('hidden_layers'):
                # L1 ImgIn shape=(?, 28, 28, 1)
                #weight1 = tf.Variable(shape=[3, 3, num_inputs, num_hidden_nodes], stddev=0.01,
                weight1 = tf.Variable(tf.random_normal([3, 3, 1, 32], stddev=0.01),
                                      name='weight1')
                #bias1 = tf.Variable(tf.random_normal([num_hidden_nodes]), name='bias1')
                #    Conv     -> (?, 28, 28, 32)
                #    Pool     -> (?, 14, 14, 32)
                with tf.name_scope('layer1_activation'):
                    #hypothesis1 = tf.add(tf.matmul(self.x_node, weight1), bias1)
                    hypothesis1 = tf.nn.conv2d(self.x_img, weight1, strides=[1, 1, 1, 1], padding='SAME')
                    y_h1 = tf.nn.relu(hypothesis1)
                    y_h1 = tf.nn.max_pool(y_h1, ksize=[1, 2, 2, 1],
                                          strides=[1, 2, 2, 1], padding='SAME')
                    #y_h1 = tf.nn.dropout(y_h1, keep_prob=self.keep_prob)
                    '''
                    Tensor("Conv2D:0", shape=(?, 28, 28, 32), dtype=float32)
                    Tensor("Relu:0", shape=(?, 28, 28, 32), dtype=float32)
                    Tensor("MaxPool:0", shape=(?, 14, 14, 32), dtype=float32)
                    Tensor("dropout/mul:0", shape=(?, 14, 14, 32), dtype=float32)
                    '''

                # L2 ImgIn shape=(?, 14, 14, 32)
                weight2 = tf.Variable(tf.random_normal([3, 3, 32, 64], stddev=0.01),
                                      name='weight2')
                #    Conv      ->(?, 14, 14, 64)
                #    Pool      ->(?, 7, 7, 64)
                with tf.name_scope('layer2_activation'):
                    hypothesis2 = tf.nn.conv2d(y_h1, weight2, strides=[1, 1, 1, 1], padding='SAME')
                    y_h2 = tf.nn.relu(hypothesis2)
                    y_h2 = tf.nn.max_pool(y_h2, ksize=[1, 2, 2, 1],
                                          strides=[1, 2, 2, 1], padding='SAME')
                    #y_h2 = tf.nn.dropout(y_h2, keep_prob=self.keep_prob)
                    y_h2_flat = tf.reshape(y_h2, [-1, 7 * 7 * 64])

            # -------------------------------------------------------------------------

            self.weight = tf.get_variable(shape=[7 * 7 * 64, num_outputs], initializer=tf.contrib.layers.xavier_initializer(),
                                          name='weight')
            self.bias = tf.Variable(tf.random.normal([num_outputs]), name='bias')

            with tf.name_scope('output_layer_activation'):
                self.model = tf.add(tf.matmul(y_h2_flat, self.weight), self.bias)

                # For evaluation
                self.hypothesis = tf.nn.softmax(self.model)

            with tf.name_scope('output_layer_activation_and_loss_calculation'):
                #cross_entropy = -tf.reduce_sum(self.y_node * tf.log(self.hypothesis), axis=1)
                cross_entropy = tf.nn.softmax_cross_entropy_with_logits_v2(labels=self.y_node,
                                                                           logits=self.model)
                self.loss = tf.reduce_mean(cross_entropy)

            with tf.name_scope('train'):
                #optimizer = tf.train.GradientDescentOptimizer(learning_rate=learn_rate)
                optimizer = tf.train.AdamOptimizer(learning_rate=learn_rate)
                self.train = optimizer.minimize(self.loss)

            with tf.name_scope('evaluate'):
                #self.predicted = tf.cast(self.hypothesis > 0.5, dtype=tf.float32)
                self.predicted = tf.math.argmax(self.model, axis=1)
                correct = tf.equal(self.predicted, tf.math.argmax(self.y_node, axis=1))
                self.accuracy = tf.reduce_mean(tf.cast(correct, dtype=tf.float32))

            self.init = tf.global_variables_initializer()
            self.sess = tf.Session()


    def train_data(self, num_epochs, batch_size):
        """Train model with given data
        """
        keep_prob = 0.7
        with self.graph.as_default():
            self.sess.run(self.init)
            for epoch in range(num_epochs):
                avg_cost = 0
                num_batches = int(mnist.train.num_examples / batch_size)

                for _ in range(num_batches):
                    [batch_xs, batch_ys] = mnist.train.next_batch(batch_size)
                    feed_dict = {self.x_node:batch_xs, self.y_node:batch_ys, self.keep_prob:keep_prob}
                    [_loss, _weight, _bias, _]\
                    = self.sess.run([self.loss, self.weight, self.bias, self.train],
                                    feed_dict=feed_dict)

                avg_cost += _loss / num_batches
                print("Epoch:{} Cost={:.04f} Weight{}[0, 0]={:.4f} Bias{}[0]={:.4f}"\
                      .format(epoch+1, _loss, _weight.shape, _weight[0, 0], _bias.shape, _bias[0]))

    def evalute_data(self):
        """Evaluate the model with given data
        """
        with self.graph.as_default():
            [test_x_data, test_y_data] = [mnist.test.images, mnist.test.labels]
            #feed_dict = {self.x_node:test_x_data, self.y_node:test_y_data, self.keep_prob:keep_prob}
            feed_dict = {self.x_node:test_x_data, self.y_node:test_y_data}
            [hypothesis, predicted, accuracy]\
            = self.sess.run([self.hypothesis, self.predicted, self.accuracy],
                            feed_dict=feed_dict)
            print("Hypothesis{}[:20]:\n{}\nPrediction{}[:20]:\n{}, \nAccuracy: {:.2f}%"\
                  .format(hypothesis.shape, hypothesis[:20], predicted.shape, predicted[:20], accuracy*100.0))

    def test_with_model(self):
        """Test with trained model
        """
        print("\n############ Test start! ###########")
        with self.graph.as_default():
            rnd = random.randint(0, mnist.test.num_examples - 1)
            [test_x_data, test_y_data] = [mnist.test.images[rnd:rnd+1], mnist.test.labels[rnd:rnd+1]]
            #feed_dict = {self.x_node:test_x_data, self.keep_prob:keep_prob}
            feed_dict = {self.x_node:test_x_data}

            test_y = tf.math.argmax(test_y_data, axis=1)
            [predicted, gt_y] = self.sess.run([self.predicted, test_y], feed_dict=feed_dict)

            print("Result: {} \nGround truth: {}".format(predicted, gt_y))
            plt.imshow(test_x_data.reshape(patch_size, patch_size), cmap='Greys')
            plt.show()

    def draw_graph(self):
        """Draw graph
        """
        tf.summary.FileWriter('./graph_logs',graph=self.graph)
        self.sess.close()


def main():
    """Main function
    """
    learn_rate = 0.001
    num_epochs = 15
    num_inputs = patch_size*patch_size
    num_outputs = 10
    batch_size = 100
    with GraphManager(learn_rate, num_inputs, num_outputs) as grp_man:
        grp_man.train_data(num_epochs, batch_size)
        grp_man.evalute_data()
        grp_man.test_with_model()

if __name__ == '__main__':
    main()
