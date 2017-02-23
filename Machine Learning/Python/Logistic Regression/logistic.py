#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-02-22 13:57
# Last modified: 2017-02-23 11:07
# Filename: logistic.py
# Description:
import numpy as np
import matplotlib.pyplot as plt
import scipy.optimize as opt


def sigmoid(z):
    g = 1 / (1 + np.exp(-z))
    return g


def cost(theta, X, y):
    m = len(y)

    h = sigmoid(X.dot(theta))
    J = -(np.log(h).T.dot(y) + np.log(1-h).T.dot(1-y)) / m
    return J


def gradient(theta, X, y):
    theta = theta.reshape((-1, 1))
    m, n = X.shape

    h = sigmoid(X.dot(theta))
    errors = h - y
    grad = X.T.dot(errors) / m
    return grad.flatten()


def predict(theta, X):
    m = len(X)

    p = sigmoid(X.dot(theta))
    p[p >= 0.5] = 1
    p[p < 0.5] = 0
    return p.reshape((-1, 1))


plt.Figure(dpi=80)

data = np.loadtxt('ex2data1.txt', delimiter=',')
X = data[:, 0:2].reshape((-1, 2))
y = data[:, -1].reshape((-1, 1))

pos = np.where(y != 0)
neg = np.where(y == 0)
plt.scatter(X[pos, 0], X[pos, 1], marker='o', c='b')
plt.scatter(X[neg, 0], X[neg, 1], marker='x', c='r')

plt.xlabel('Exam1 score')
plt.ylabel('Exam2 score')
plt.legend(['Admitted', 'Not admitted'])

m, n = X.shape

X = np.append(np.ones((m, 1)), X, axis=1)

theta = np.zeros((n+1, 1))

iter_times = 400
alpha = 0.01

options = {'full_output': True, 'maxiter': 400}
theta, cost, *rest = opt.fmin_bfgs(cost, x0=theta, fprime=gradient,
                                   args=(X, y), **options)

plot_x = np.array([min(X[:, 1]) - 2, max(X[:, 1]) + 2])
plot_y = -1 / theta[2] * (theta[1]*plot_x + theta[0])
plt.plot(plot_x, plot_y, c='g')
plt.legend(['Decision boundry', 'Admitted', 'Not admitted'])


prob = sigmoid(theta.T.dot([1, 45, 85]))
print('For a student with scores 45 and 85, we predict an admission '
        'probability of {:.2%}'.format(prob))

p = predict(theta, X)
print('Train Accuarcy: {:.2%}'.format(np.sum(p == y)/m))

plt.show()
