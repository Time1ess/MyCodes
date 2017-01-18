#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-01-18 08:59
# Last modified: 2017-01-18 09:05
# Filename: basic.py
# Description:
import tensorflow as tf


with tf.Session() as sess:
    m1 = tf.constant([[3., 3.]])
    m2 = tf.constant([[3.], [3.]])
    product = tf.matmul(m1, m2)
    result = sess.run(product)
    print(result)
