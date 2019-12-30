import tensorflow as tf

g = tf.Graph()
with g.as_default():
    # shape에 None이 들거마
    # 1x2, 2x2, 3x2 모두 크기에 관계없이 가능하다는 의미에서 None -> Batch 개념
    in1 = tf.placeholder(dtype=tf.float32, shape=[None, 2], name='input1')
    in2 = tf.placeholder(dtype=tf.float32, shape=[None, 2], name='intput2')
    const = tf.constant(2, dtype=tf.float32, name='static_value')

    with tf.name_scope('Transformation'):
        with tf.name_scope('A'):
            a_mul = tf.multiply(in1, const)
            a_out = tf.subtract(a_mul, in1)

        with tf.name_scope('B'):
            b_mul = tf.multiply(in2, const)
            b_out = tf.subtract(b_mul, in2)

        with tf.name_scope('B'):
            c_div = tf.div(a_out, b_out)
            c_out = tf.add(c_div, const)

        with tf.name_scope('B'):
            d_div = tf.div(b_out, a_out)
            d_out = tf.add(d_div, const)

    out = tf.maximum(c_out, d_out)
    sess = tf.Session(graph=g)
    _result, _c_out, _d_out = sess.run([out, c_out, d_out],
                                       feed_dict={in1:[[5, 3],
                                                       [4, 1]],
                                                  in2:[[5, 6],
                                                       [7, 8]]})

print('out{}\nc_out:{}\nd_out{}'.format(_result, _c_out, _d_out))
tf.summary.FileWriter('./my_graph', graph=g)