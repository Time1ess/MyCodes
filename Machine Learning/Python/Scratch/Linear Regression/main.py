#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-08-27 15:43
# Last modified: 2017-08-31 15:22
# Filename: main.py
# Description:
import sys

import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation


m = 100
n = 3  # >= 2

gt_theta = np.random.random_sample((n, 1))
x = np.arange(-m/2, m/2).reshape((-1, 1))
bias = np.ones((m, 1))
X = np.append(bias, x, axis=1)

for exp in range(2, n):
    X = np.append(X, x**exp, axis=1)
y = np.dot(X, gt_theta)

theta = np.random.random_sample((n, 1))
lr = 1e-7
iters = 100

fig, ax = plt.subplots()
ax.scatter(x, y)
line, = ax.plot(x, X.dot(theta), c='red')


def optimize(x, y, theta, alpha=1e-4, iters=100, with_history=False):
    history = []
    m = y.shape[0]
    for _ in range(iters):
        h = x.dot(theta)
        errors = h - y
        theta_delta = alpha / m * np.dot(x.T, errors)
        theta -= theta_delta
        history.append((theta.copy(), np.sum(errors)))
    if with_history:
        return theta, history
    else:
        return theta


def animate(history):
    def _wrapper(i):
        theta, error = history[i]
        h = X.dot(theta)
        line.set_ydata(h)
        sys.stdout.flush()
        sys.stdout.write('{:6.3f}\r'.format(error))
        return line
    return _wrapper


theta, history = optimize(X, y, theta, alpha=lr, iters=iters,
                          with_history=True)

anim = animation.FuncAnimation(fig, animate(history), np.arange(len(history)),
                               interval=50, repeat=True)
plt.show()
