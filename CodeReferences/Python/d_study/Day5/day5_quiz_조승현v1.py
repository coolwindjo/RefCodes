# -*- coding: utf-8 -*-
import os
import tensorflow as tf
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
#import random
#from tensorflow.examples.tutorials.mnist import input_data
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'

#mnist = input_data.read_data_sets('MNIST/', one_hot=True)
#patch_size = 28
data_file = "./data/Iris2.csv"
ckpt_path = './model'
graph_path = './graph_logs'

def read_data(filename):
    """Read data from the file
    """
    #data_set = np.loadtxt(filename, delimiter=",", dtype=np.float32)
    data_set = pd.read_csv(filename)
    print("Iris data{}:\n{}".format(data_set.shape, data_set.head()))
    return parse_data(data_set)

def parse_data(data_with_str):
    """Parse data from the list of item
    """
    data_one_hot = pd.get_dummies(data_with_str)
    print("\nIris one-hot encoded data{}:\n{}".format(data_one_hot.shape, data_one_hot.head()))
    print("\nIris one-hot encoded data loc[0]:\n{}".format(data_one_hot.loc[0]))

    [input_data_train, label_data_train,
     input_data_test, lable_data_test] = parse_iris_data(data_one_hot)
    return [np.array(input_data_train), np.array(label_data_train),
            np.array(input_data_test), np.array(lable_data_test)]

def parse_iris_data(iris_data):
    """Parse iris data from the list of item
    """
    iris_train_data = iris_data.sample(frac=0.8, random_state=200)
    iris_test_data = iris_data.drop(iris_train_data.index)

    input_attributes = ['SepalLengthCm', 'SepalWidthCm', 'PetalLengthCm', 'PetalWidthCm']
    output_classes = ['Species_Iris-setosa', 'Species_Iris-versicolor', 'Species_Iris-virginica']

    iris_train_input_data = iris_train_data.filter(input_attributes)
    iris_train_label_data = iris_train_data.filter(output_classes)

    iris_test_input_data = iris_test_data.filter(input_attributes)
    iris_test_label_data = iris_test_data.filter(output_classes)
    return iris_train_input_data, iris_train_label_data, iris_test_input_data, iris_test_label_data

class GraphManager():
    """Graph manager class
    """
    def __init__(self, learn_rate, num_inputs, num_outputs, num_hidden_nodes=512):
        self.build_graph(learn_rate, num_inputs, num_outputs, num_hidden_nodes)

    def __enter__(self):
        return self

    def __exit__(self, exc_type, exc_val, exc_tb):
        self.draw_graph()

    def build_graph(self, learn_rate, num_inputs, num_outputs, num_hidden_nodes=512):
        """Build graph
        """
        self.graph = tf.Graph()
        with self.graph.as_default():
            self.x_node = tf.placeholder(dtype=tf.float32, shape=[None, num_inputs], name='X')
            self.y_node = tf.placeholder(dtype=tf.int32, shape=[None, num_outputs], name='Y')
            self.keep_prob = tf.placeholder(dtype=tf.float32)

            # Weight, bias initialization
            tf.set_random_seed(777)
            with tf.name_scope('hidden_layers'):
                weight1 = tf.get_variable(shape=[num_inputs, num_hidden_nodes], initializer=tf.contrib.layers.xavier_initializer(),
                                          name='weight1')
                bias1 = tf.Variable(tf.random_normal([num_hidden_nodes]), name='bias1')
                with tf.name_scope('layer1_activation'):
                    hypothesis1 = tf.add(tf.matmul(self.x_node, weight1), bias1)
                    y_h1 = tf.nn.relu(hypothesis1)
                    #y_h1 = tf.nn.dropout(y_h1, keep_prob=self.keep_prob)

                tf.summary.histogram("X", self.x_node)
                tf.summary.histogram("Weights", weight1)

                weight2 = tf.get_variable(shape=[num_hidden_nodes, num_hidden_nodes], initializer=tf.contrib.layers.xavier_initializer(),
                                          name='weight2')
                bias2 = tf.Variable(tf.random_normal([num_hidden_nodes]), name='bias2')
                with tf.name_scope('layer2_activation'):
                    hypothesis2 = tf.add(tf.matmul(y_h1, weight2), bias2)
                    y_h2 = tf.nn.relu(hypothesis2)
                    #y_h2 = tf.nn.dropout(y_h2, keep_prob=self.keep_prob)

                tf.summary.histogram("Weights", weight2)

                weight3 = tf.get_variable(shape=[num_hidden_nodes, num_hidden_nodes], initializer=tf.contrib.layers.xavier_initializer(),
                                          name='weight3')
                bias3 = tf.Variable(tf.random_normal([num_hidden_nodes]), name='bias3')
                with tf.name_scope('layer3_activation'):
                    hypothesis3 = tf.add(tf.matmul(y_h2, weight3), bias3)
                    y_h3 = tf.nn.relu(hypothesis3)
                    #y_h3 = tf.nn.dropout(y_h3, keep_prob=self.keep_prob)

                tf.summary.histogram("Weights", weight3)

                weight4 = tf.get_variable(shape=[num_hidden_nodes, num_hidden_nodes], initializer=tf.contrib.layers.xavier_initializer(),
                                          name='weight4')
                bias4 = tf.Variable(tf.random_normal([num_hidden_nodes]), name='bias4')
                with tf.name_scope('layer4_activation'):
                    hypothesis4 = tf.add(tf.matmul(y_h3, weight4), bias4)
                    y_h4 = tf.nn.relu(hypothesis4)
                    #y_h4 = tf.nn.dropout(y_h4, keep_prob=self.keep_prob)

                tf.summary.histogram("Weights", weight4)
            # -------------------------------------------------------------------------

            self.global_step = tf.Variable(0, trainable=False, name='global_step')
            self.weight = tf.get_variable(shape=[num_hidden_nodes, num_outputs], initializer=tf.contrib.layers.xavier_initializer(),
                                          name='weight')
            self.bias = tf.Variable(tf.random.normal([num_outputs]), name='bias')

            with tf.name_scope('output_layer_activation'):
                model = tf.add(tf.matmul(y_h4, self.weight), self.bias)

                tf.summary.histogram("Weights", self.weight)
                tf.summary.histogram("Model", model)

            with tf.name_scope('output_layer_activation_and_loss_calculation'):
                #cross_entropy = -tf.reduce_sum(self.y_node * tf.log(self.hypothesis), axis=1)
                cross_entropy = tf.nn.softmax_cross_entropy_with_logits_v2(labels=self.y_node,
                                                                           logits=model)
                self.loss = tf.reduce_mean(cross_entropy)

            with tf.name_scope('train'):
                #optimizer = tf.train.GradientDescentOptimizer(learning_rate=learn_rate)
                optimizer = tf.train.AdamOptimizer(learning_rate=learn_rate)
                self.train = optimizer.minimize(self.loss)

                tf.summary.scalar('Cost', self.loss)

            with tf.name_scope('evaluate'):
                self.hypothesis = tf.nn.softmax(model)
                #self.predicted = tf.cast(self.hypothesis > 0.5, dtype=tf.float32)
                self.predicted = tf.math.argmax(self.hypothesis, axis=1)
                correct = tf.equal(self.predicted, tf.math.argmax(self.y_node, axis=1))
                self.accuracy = tf.reduce_mean(tf.cast(correct, dtype=tf.float32))

            self.init = tf.global_variables_initializer()
            self.sess = tf.Session()
            self.saver = tf.train.Saver(tf.global_variables())
            self.writer = tf.summary.FileWriter(graph_path, graph=self.graph)
            self.ckpt = tf.train.get_checkpoint_state(ckpt_path)
            self.merged = tf.summary.merge_all()

    def train_data(self, num_epochs, batch_size, x_data, y_data, keep_prob=0.7):
        """Train model with given data
        """
        with self.graph.as_default():
            if self.ckpt and tf.train.checkpoint_exists(self.ckpt.model_checkpoint_path):
                self.saver.restore(self.sess, self.ckpt.model_checkpoint_path)
            else:
                self.sess.run(self.init)

            for epoch in range(num_epochs):
                avg_cost = 0
                num_batches = int(len(x_data) / batch_size)

                for _ in range(num_batches):
                    #[batch_xs, batch_ys] = mnist.train.next_batch(batch_size)
                    feed_dict = {self.x_node:x_data, self.y_node:y_data, self.keep_prob:keep_prob}
                    [_loss, _weight, _bias, _]\
                    = self.sess.run([self.loss, self.weight, self.bias, self.train],
                                    feed_dict=feed_dict)

                avg_cost += _loss / num_batches
                if epoch % 200 == 0:
                    print("Epoch:{} Cost={:.04f} Weight{}[0, 0]={:.4f} Bias{}[0]={:.4f}"\
                          .format(epoch+1, _loss, _weight.shape, _weight[0, 0], _bias.shape, _bias[0]))
                summary = self.sess.run(self.merged, feed_dict=feed_dict)
                global_step = self.sess.run(self.global_step)
                self.writer.add_summary(summary, global_step=global_step)
            self.saver.save(self.sess, ckpt_path+'/dnn.ckpt', global_step=self.global_step)

    def evalute_data(self, x_data, y_data, keep_prob=1):
        """Evaluate the model with given data
        """
        with self.graph.as_default():
            #[test_x_data, test_y_data] = [mnist.test.images, mnist.test.labels]
            feed_dict = {self.x_node:x_data, self.y_node:y_data, self.keep_prob:keep_prob}
            [hypothesis, predicted, accuracy]\
            = self.sess.run([self.hypothesis, self.predicted, self.accuracy],
                            feed_dict=feed_dict)
            print("Hypothesis{}[:20]:\n{}\nPrediction{}[:20]:\n{}, \nAccuracy: {:.2f}%".format(
                hypothesis.shape, hypothesis[:20], predicted.shape, predicted[:20], accuracy*100.0))

    def test_with_model(self, test_x, gt_y="", keep_prob=1):
        """Test with trained model
        """

        print("\n############ Test start! ###########")
        with self.graph.as_default():
            #rnd = random.randint(0, mnist.test.num_examples - 1)
            #[test_x_data, test_y_data] = [mnist.test.images[rnd:rnd+1], mnist.test.labels[rnd:rnd+1]]
            feed_dict = {self.x_node:test_x, self.keep_prob:keep_prob}

            hypothesis = self.sess.run(self.hypothesis, feed_dict=feed_dict)
            predicted = self.sess.run(self.predicted, feed_dict=feed_dict)

            print("TestSet{}:\n{} \nHypothesis{}:\n{} \nPredicted: {}"\
                  .format(test_x.shape, test_x, hypothesis.shape, hypothesis, predicted))
            #plt.imshow(test_x_data.reshape(patch_size, patch_size), cmap='Greys')
            #plt.show()

    def draw_graph(self):
        """Draw graph
        """
        self.sess.close()


def main():
    """Main function
    """
    [input_data_train, label_data_train,
     input_data_test, lable_data_test] = read_data(data_file)

    learn_rate = 0.05
    num_epochs = 1000
    batch_size = 100
    num_hidden_nodes = 512
    keep_prob = 0.7
    with GraphManager(learn_rate, len(input_data_train[0]), len(label_data_train[0]), num_hidden_nodes) as grp_man:
        grp_man.train_data(num_epochs, batch_size, input_data_train, label_data_train, keep_prob)
        grp_man.evalute_data(input_data_train, label_data_train)
        grp_man.test_with_model(input_data_test, lable_data_test)

if __name__ == '__main__':
    main()
