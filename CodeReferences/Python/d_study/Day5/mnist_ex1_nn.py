# -*- coding: utf-8 -*-
import os
import tensorflow as tf
import random
import matplotlib.pyplot as plt
from tensorflow.examples.tutorials.mnist import input_data
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'

mnist = input_data.read_data_sets('MNIST/', one_hot=True)

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
            self.y_node = tf.placeholder(dtype=tf.int32, shape=[None, num_outputs], name='Y')

            # Weight, bias initialization
            tf.set_random_seed(777)
            with tf.name_scope('hidden_layers'):
                weight1 = tf.Variable(tf.random_normal([num_inputs, 256]),
                                      name='weight1')
                bias1 = tf.Variable(tf.random_normal([256]), name='bias1')
                with tf.name_scope('layer1_activation'):
                    hypothesis1 = tf.add(tf.matmul(self.x_node, weight1), bias1)
                    y_h1 = tf.nn.relu(hypothesis1)

                weight2 = tf.Variable(tf.random_normal([256, 256]),
                                      name='weight2')
                bias2 = tf.Variable(tf.random_normal([256]), name='bias2')
                with tf.name_scope('layer2_activation'):
                    hypothesis2 = tf.add(tf.matmul(y_h1, weight2), bias2)
                    y_h2 = tf.nn.relu(hypothesis2)

            # -------------------------------------------------------------------------

            self.weight = tf.Variable(tf.random_normal([256, num_outputs]),
                                      name='weight')
            self.bias = tf.Variable(tf.random.normal([num_outputs]), name='bias')

            with tf.name_scope('output_layer_activation'):
                model = tf.add(tf.matmul(y_h2, self.weight), self.bias)

                # For evaluation
                self.hypothesis = tf.nn.softmax(model)

            with tf.name_scope('output_layer_activation_and_loss_calculation'):
                #cross_entropy = -tf.reduce_sum(self.y_node * tf.log(self.hypothesis), axis=1)
                cross_entropy = tf.nn.softmax_cross_entropy_with_logits_v2(labels=self.y_node,
                                                                           logits=model)
                self.loss = tf.reduce_mean(cross_entropy)

            with tf.name_scope('train'):
                #optimizer = tf.train.GradientDescentOptimizer(learning_rate=learn_rate)
                optimizer = tf.train.AdamOptimizer(learning_rate=learn_rate)
                self.train = optimizer.minimize(self.loss)

            with tf.name_scope('evaluate'):
                #self.predicted = tf.cast(self.hypothesis > 0.5, dtype=tf.float32)
                self.predicted = tf.math.argmax(self.hypothesis, axis=1)
                correct = tf.equal(self.predicted, tf.math.argmax(self.y_node, axis=1))
                self.accuracy = tf.reduce_mean(tf.cast(correct, dtype=tf.float32))

            self.init = tf.global_variables_initializer()
            self.sess = tf.Session()


    def train_data(self, num_epochs, batch_size):
        """Train model with given data
        """
        with self.graph.as_default():
            self.sess.run(self.init)
            for epoch in range(num_epochs):
                avg_cost = 0
                num_batches = int(mnist.train.num_examples / batch_size)

                for _ in range(num_batches):
                    [batch_xs, batch_ys] = mnist.train.next_batch(batch_size)
                    feed_dict = {self.x_node:batch_xs, self.y_node:batch_ys}
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
            feed_dict = {self.x_node:test_x_data, self.y_node:test_y_data}
            [hypothesis, predicted, accuracy]\
            = self.sess.run([self.hypothesis, self.predicted, self.accuracy],
                            feed_dict=feed_dict)
            print("Hypothesis{}[:20]:\n{}\nPrediction{}[:20]:\n{}, \nAccuracy: {:.2f}%".format(
                hypothesis.shape, hypothesis[:20], predicted.shape, predicted[:20], accuracy*100.0))

    def test_with_model(self):
        """Test with trained model
        """
        print("\n############ Test start! ###########")
        with self.graph.as_default():
            rnd = random.randint(0, mnist.test.num_examples - 1)
            [test_x_data, test_y_data] = [mnist.test.images[rnd:rnd+1], mnist.test.labels[rnd:rnd+1]]
            feed_dict = {self.x_node:test_x_data}

            test_y = tf.math.argmax(test_y_data, axis=1)
            [predicted, gt_y] = self.sess.run([self.predicted, test_y], feed_dict=feed_dict)

            print("Result: {} \nGround truth: {}".format(predicted, gt_y))
            plt.imshow(test_x_data.reshape(28, 28), cmap='Greys')
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
    num_inputs = 784
    num_outputs = 10
    batch_size = 100
    with GraphManager(learn_rate, num_inputs, num_outputs) as grp_man:
        grp_man.train_data(num_epochs, batch_size)
        grp_man.evalute_data()
        grp_man.test_with_model()

if __name__ == '__main__':
    main()
