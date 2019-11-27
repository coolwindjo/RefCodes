import tensorflow as tf
import pandas as pd

iris_data = pd.read_csv("Day4/data/Iris2.csv")
print(iris_data.head())
iris_data_one_hot_encoded = pd.get_dummies(iris_data)
print('\n',iris_data_one_hot_encoded.loc[0])

iris_train_data = iris_data_one_hot_encoded.sample(frac=0.8, random_state=200)
iris_test_data = iris_data_one_hot_encoded.drop(iris_train_data.index)

iris_train_input_data = iris_train_data.filter(
    ['SepalLengthCm', 'SepalWidthCm', 'PetalLengthCm', 'PetalWidthCm'])
iris_train_label_data = iris_train_data.filter(
    ['Species_Iris-setosa', 'Species_Iris-versicolor', 'Species_Iris-virginica'])
iris_test_input_data = iris_test_data.filter(
    ['SepalLengthCm', 'SepalWidthCm', 'PetalLengthCm', 'PetalWidthCm'])
iris_test_label_data = iris_test_data.filter(
    ['Species_Iris-setosa', 'Species_Iris-versicolor', 'Species_Iris-virginica'])

