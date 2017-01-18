#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-01-18 13:24
# Last modified: 2017-01-18 13:58
# Filename: linear.py
# Description:
import tensorflow as tf
import numpy as np
import matplotlib.pyplot as plt

POINTS_NUM = 1000
ITER_TIMES = 500
x_data = []
y_data = []
for i in range(POINTS_NUM):
    x1 = np.random.normal(0., 0.55)
    y1 = x1 * 0.3 + 0.2 + np.random.normal(0., 0.1)
    x_data.append([x1])
    y_data.append([y1])

x = tf.placeholder(tf.float32, [None, 1])
y_ = tf.placeholder(tf.float32, [None, 1])
W = tf.Variable(tf.random_uniform([1], -1.0, 1.0))
b = tf.Variable(tf.zeros([1]))
y = W * x + b
cost = tf.reduce_mean(tf.square(y-y_))

train_step = tf.train.GradientDescentOptimizer(0.1).minimize(cost)

with tf.Session() as sess:
    sess.run(tf.global_variables_initializer())
    for step in range(ITER_TIMES):
        if step % 100 == 0:
            print(step, sess.run(W), sess.run(b))
        sess.run(train_step, feed_dict={x: x_data, y_: y_data})
    a1 = sess.run(W)[0]
    a0 = sess.run(b)[0]
    line_x = np.array([-2, 2])
    line_y = line_x * a1 + a0
    plt.plot(line_x, line_y, 'r')
    plt.plot(x_data, y_data, 'go', label='Original data')
    plt.legend()
    plt.show()
