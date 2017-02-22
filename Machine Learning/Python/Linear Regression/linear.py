#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-02-22 09:33
# Last modified: 2017-02-22 11:05
# Filename: linear.py
# Description:
import numpy as np
import matplotlib.pyplot as plt


def gradient_descent(X, y, theta, alpha, iterations):
    m = y.shape[0]
    J_history = []
    for it in range(iterations):
        h = np.dot(X, theta)
        errors = h - y
        theta_change = alpha / m * np.dot(X.T, errors)
        theta = theta - theta_change
        J_history.append(sum(errors))

    return theta, J_history


plt.figure(dpi=80)

X, y = np.loadtxt('ex1data1.txt', delimiter=',', unpack=True)
X = X.reshape((-1, 1))
y = y.reshape((-1, 1))
m = y.shape

plt.scatter(X, y, c='red')

X = np.append(np.ones(m), X, axis=1)
theta = np.random.random_sample((2, 1))

iterations = 5000
alpha = 0.01

theta, J_history = gradient_descent(X, y, theta, alpha, iterations)

plt.plot(X[:, 1], np.dot(X, theta), c='blue')
plt.title('Linear Regression with Gradient Descent')
plt.xlabel('x')
plt.ylabel('y')
plt.show()
