#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-08-27 17:03
# Last modified: 2017-08-27 19:04
# Filename: main.py
# Description:
import sys

import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import scipy.optimize as opt

from numpy.linalg import norm


M = 1000
CENTER_X1 = np.array([[0, 0]])
CENTER_X2 = np.array([[3, 5]])

X1 = np.random.normal(size=(M//2, 2)) + CENTER_X1
X2 = np.random.normal(size=(M//2, 2)) + CENTER_X2


def close(p1, p2, dist=4):
    return norm(p1-p2) <= dist


X = np.append(X1, X2, axis=0)
X = np.append(np.ones(len(X)).reshape((-1, 1)), X, axis=1)
y = np.append(np.ones(len(X1)), np.zeros(len(X2)), axis=0).reshape((-1, 1))

fig, ax = plt.subplots()
ax.scatter(X1[:, 0], X1[:, 1], marker='+', c='blue')
ax.scatter(X2[:, 0], X2[:, 1], marker='o', c='red')
#plt.show()

def sigmoid(x):
    return 1 / (1 + np.exp(-x))


def cost_func(theta, X, y):
    theta = theta.reshape((-1, 1))
    m = len(y)
    h = sigmoid(X.dot(theta))
    errors = - (np.log(h).T.dot(y) + np.log(1-h).T.dot(1-y)) / m

    return errors


def gradient(theta, X, y):
    theta = theta.reshape((-1, 1))
    m = len(y)
    h = sigmoid(X.dot(theta))
    errors = h - y
    grad = X.T.dot(errors) / m
    return grad.flatten()


def optimize(theta, X, y, iters=1000, alpha=1e-4, with_history=False,
             init_patience=20):
    m = len(y)
    history = []
    last_errors = 1e9
    patience = init_patience
    for _ in range(iters):
        errors = float(sum(cost_func(theta, X, y)))
        if abs(last_errors - errors) < 1e-3:
            patience -= 1
            if patience == 0:
                break
        else:
            patience = init_patience
            last_errors = errors
        grad = gradient(theta, X, y)
        theta_delta = alpha * grad.reshape(theta.shape)
        theta -= theta_delta
        history.append((theta.copy(), errors))
    if with_history:
        return theta, history
    else:
        return theta


def predict(theta, X, thres=0.5):
    h = sigmoid(X.dot(theta))
    h[h >= thres] = 1
    h[h < thres] = 0
    return h


theta = np.zeros((3, 1))
iters = 10000
lr = 1e-1
options = {'full_output': True, 'maxiter': iters}

theta, history = optimize(theta, X, y, alpha=lr, iters=iters, with_history=True)

#theta, cost, *rest = opt.fmin_bfgs(cost_func, x0=theta,
#                                   fprime=gradient, args=(X, y), **options)

theta = theta.reshape((-1, 1))

h = predict(theta, X)
print(np.sum(h==y) / len(y) * 100)

theta = history[0][0]
plot_x = np.array([min(X[:, 1]) - 2, max(X[:, 1]) + 2])


def cal_y(theta):
    plot_y = -1 / theta[2] * (theta[1]*plot_x + theta[0])
    return plot_y


line, = ax.plot(plot_x, cal_y(theta))

def animate(history):
    def _wrapper(i):
        theta, error = history[i]
        h = predict(theta, X)
        acc = np.sum(h==y) / len(y)
        line.set_ydata(cal_y(theta))
        sys.stdout.flush()
        sys.stdout.write('{:5d} / {:5d}, {:5.2%} | {:6.3f}, {:6.2%}\r'.format(
            i, len(history), i / len(history), error, acc))
        return line
    return _wrapper

anim = animation.FuncAnimation(fig, animate(history), np.arange(len(history)),
                               interval=10)
plt.show()
