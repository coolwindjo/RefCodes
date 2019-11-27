import tensorflow as tf

graph = tf.Graph()

with graph.as_default():
    with tf.name_scope("variables"):
        global_step = tf.Variable(0, dtype=tf.int32, name="global_step")
        increment_step = global_step.assign_add(1)
        total_output = tf.Variable(0, dtype=tf.float32, name="total_output")
        with tf.name_scope("input"):
            a = tf.placeholder(tf.float32, shape=[None], name="input_placeholder_a")

        with tf.name_scope("intermediate_layer"):
            b = tf.reduce_prod(a, name="product_b")
            c = tf.reduce_sum(a, name="sum_c")

        with tf.name_scope("output"):
            d = tf.add(b, c, name="add_d")

        with tf.name_scope("global_ops"):
            init = tf.global_variables_initializer()

        with tf.name_scope("updates"):
            update_total = total_output.assign_add(d)

        with tf.name_scope("summaries"):
            avg = tf.div(update_total, tf.cast(increment_step,tf.float32), name='average')

sess = tf.Session(graph=graph)
sess.run(init)
writer = tf.summary.FileWriter('./my_graph', graph)

def run_graph(input_tensor):
    feed_dict = {a: input_tensor}
    _output, _step, _avg = sess.run([d,increment_step, avg], feed_dict=feed_dict)
    print('step:{}, result:{}, average:{}'.format(_step,_output, _avg))

# Run the graph with various inputs
run_graph([2, 8])
run_graph([3, 1, 3, 3])
run_graph([8])
run_graph([1, 2, 3])
run_graph([11, 4])
run_graph([4, 1])
run_graph([7, 3, 1])
run_graph([6, 3])
run_graph([0, 2]),
run_graph([4, 5, 6])

sess.close()

