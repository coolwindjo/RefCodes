# -*- coding: utf-8 -*-
""" Classification with zoo data using softmax
"""
import os
import tensorflow as tf
import pandas as pd
import numpy as np

os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'

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
            self.weight = tf.Variable(tf.random.normal([num_inputs, num_outputs],
                                                       seed=0, dtype=tf.dtypes.float32),
                                      name='weight')
            self.bias = tf.Variable(tf.random.normal([num_outputs]), name='bias')

            with tf.name_scope('output_layer_activation'):
                model = tf.add(tf.matmul(self.x_node, self.weight), self.bias)

                # For evaluation
                self.hypothesis = tf.nn.softmax(model)

            with tf.name_scope('output_layer_activation_and_loss_calculation'):
                #cross_entropy = -tf.reduce_sum(self.y_node * tf.log(self.hypothesis), axis=1)
                cross_entropy = tf.nn.softmax_cross_entropy_with_logits_v2(labels=self.y_node,
                                                                           logits=model)
                self.loss = tf.reduce_mean(cross_entropy)

            with tf.name_scope('train'):
                optimizer = tf.train.GradientDescentOptimizer(learning_rate=learn_rate)
                #optimizer = tf.train.AdamOptimizer(learn_rate)
                self.train = optimizer.minimize(self.loss)

            with tf.name_scope('evaluate'):
                #self.predicted = tf.cast(self.hypothesis > 0.5, dtype=tf.float32)
                self.predicted = tf.math.argmax(self.hypothesis, 1)
                correct = tf.equal(self.predicted, tf.math.argmax(self.y_node, axis=1))
                self.accuracy = tf.reduce_mean(tf.cast(correct, dtype=tf.float32))

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
                    print("Epoch:{} Cost={:.04f} Weight{}[0, 0]={:.4f} Bias{}[0]={:.4f}"\
                          .format(step, _loss, _weight.shape, _weight[0, 0], _bias.shape, _bias[0]))

    def evalute_data(self, x_data, y_data):
        """Evaluate the model with given data
        """
        with self.graph.as_default():
            [hypothesis, cost, accuracy]\
            = self.sess.run([self.hypothesis, self.predicted, self.accuracy],
                            feed_dict={self.x_node:x_data, self.y_node:y_data})
            print("Hypothesis{}[:20]:\n{}\nCorrect{}[:20]:\n{}, \nAccuracy: {:.2f}%".format(
                hypothesis.shape, hypothesis[:20], cost.shape, cost[:20], accuracy*100.0))

    def test_with_model(self, test_x, gt_y=""):
        """Test with trained model
        """
        print("\n############ Test start! ###########")
        with self.graph.as_default():
            test_y = self.sess.run(self.hypothesis, feed_dict={self.x_node:test_x})
            if gt_y == "":
                max_test_y = self.sess.run(tf.math.argmax(test_y, axis=1))
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
    [input_data_train, label_data_train,
     input_data_test, lable_data_test] = read_data("Day4/data/Iris2.csv")
    learn_rate = 0.05
    num_epochs = 1000
    with GraphManager(learn_rate, len(input_data_train[0]), len(label_data_train[0])) as grp_man:
        grp_man.train_data(num_epochs, input_data_train, label_data_train)
        grp_man.evalute_data(input_data_train, label_data_train)
        grp_man.test_with_model(input_data_test, lable_data_test)

if __name__ == '__main__':
    main()
