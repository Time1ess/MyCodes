#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-01-18 09:10
# Last modified: 2017-01-18 09:11
# Filename: basic_fetch.py
# Description:
import tensorflow as tf

input1 = tf.constant(3.)
input2 = tf.constant(2.)
input3 = tf.constant(5.)
intermed = tf.add(input2, input3)
mul = tf.mul(input1, intermed)

with tf.Session() as sess:
    result = sess.run([mul, intermed])
    print(result)
