import tensorflow as tf

# tf에서 스케치북처럼 사용하는 기본 그래프
# 기본으로 존재한다. 노드를 생성하면 여기에 포함되게 된다.
print(tf.get_default_graph())

g = tf.Graph()
print('g:', g)

# 노드는 기본적으로 default 그래프에 들어감
a = tf.constant(5, dtype=tf.float32)
print(a.graph is g)
print(a.graph is tf.get_default_graph())

with g.as_default():
    b = tf.multiply(2, 4)
    c = tf.add(b, 5)
    d = tf.subtract(c, 7)

print("b is G" if b.graph is g else 'b is default')

sess = tf.Session(graph=tf.get_default_graph()) #이것이 Session의 기본값
sess2 = tf.Session(graph=g)

print('G graph ', sess2.run(d))

tf.summary.FileWriter('./my_graph', graph=g)