#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-08-27 15:43
# Last modified: 2017-08-27 16:19
# Filename: main.py
# Description:
import numpy as np
import matplotlib.pyplot as plt


m = 100
n = 4  # >= 2
gt_theta = np.random.random_sample((n, 1))

x = np.arange(-m/2, m/2).reshape((-1, 1))
bias = np.ones((m ,1))
X = np.append(bias, x, axis=1)

for exp in range(2, n):
    X = np.append(X, x**exp, axis=1)

y = np.dot(X, gt_theta)


theta = np.random.random_sample((n, 1))
lr = 1e-10


def optimize(x, y, theta, alpha=1e-4, iters=100, with_history=False):
    history = []
    m = y.shape[0]
    for _ in range(iters):
        h = x.dot(theta)
        errors = h - y
        theta_delta = alpha / m * np.dot(x.T, errors)
        theta -= theta_delta
        history.append((theta.copy(), sum(errors)))
    if with_history:
        return theta, history
    else:
        return theta


theta, history = optimize(X, y, theta, alpha=lr, with_history=True)
plt.figure()
plt.scatter(x, y)
plt.plot(x, X.dot(theta), c='red')
plt.figure()
plt.plot([abs(his[1]) for his in history])
plt.show()
